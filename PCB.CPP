/*
 * PCB.cpp
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#include "PCB.H"

PCB::PCB(StackSize stackSize = defaultStackSize, Time time =
		defaultTimeSlice, Thread* t=0) {
	unsigned* st=new unsigned[stackSize];
	stack=st;
	stack[stackSize-1]=0x200;
#ifndef BCC_BLOCK_IGNORE_
	stack[stackSize-2]=FP_SEG(wrapper);
	stack[stackSize-3]=FP_OFF(wrapper);
	sp=FP_OFF(stack+stackSize-12);
	ss=FP_SEG(stack+stackSize-12);
	bp=FP_OFF(stack+stackSize-12);
#endif
	timeSlice=counter=time;

	blockList=new BlockL();
	myThread=t;
	parent=0;
	isOver=0;
	id=++posID;
	threadList->dodaj(myThread,id);
	blockList=new BlockL();
	cout<<id<<endl;
     this->niz[0]=new Elem(&brisanje);
	if (running){
		parent=((PCB*)running)->myThread;
		for (int i=1;i<MAX1;i++){
			if (running->niz[i]){
				Elem* p=running->niz[i], *prvi=niz[i],*posl=0;
				while (p){
					Elem* novi=new Elem(p->hand);
					if (prvi==0) prvi=novi;
					else posl->sled=novi;
					posl=novi;
					p=p->sled;
				}
			}
			else niz[i]=0;
		}
	}
	else {
		for (int i=0;i<MAX1;i++){
			niz[i]=0;
		}
	}
    broj=0;
}
SignalId PCB::globalBlocked[MAX1]={0};
ID PCB::posID=0;
TLista* PCB::threadList=new TLista();
volatile PCB* PCB::running=new PCB();
void PCB::wrapper(){
	running->myThread->run();
	((PCB*)running)->signali[((PCB*)running)->broj++];
	if (running->parent!=0) running->parent->myPCB->signali[running->parent->myPCB->broj++];
	lock();
	PCB* p=running->blockList->uzmi();
	while (p!=0){
		Scheduler::put(p);
		p=running->blockList->uzmi();
	}
	running->isOver=1;
	unlock();
	dispatch();
}
void PCB::waitToComplete(){
	lock();
	if (isOver==0){
		lock();
		blockList->dodaj((PCB*)running);
		blockFlag=1;
		unlock();
		dispatch();
	}
	else unlock();

}
ID PCB::getId(){
	return id;
}
ID PCB::getRunningId(){
	return running->id;
}
Thread* PCB::getThreadById(ID id){
	return threadList->dohvati(id);
}
PCB::~PCB() {
	lock();
	//cout<<"destruktor pozvan"<<endl;
	waitToComplete();
	//cout<<"zavrsen wait"<<endl;
	threadList->izbaci(this->id);
	delete this->stack;
	this->myThread=0;
	//cout<<"Destruktor zavrsen"<<endl;
	unlock();
}
void PCB::brisanje(){
	lock();
	PCB* p=running->blockList->uzmi();
		while (p!=0){
			cout<<"Vracanje blokiranih u scheduler"<<endl;
			Scheduler::put(p);
			p=running->blockList->uzmi();
		}
		running->isOver=1;
		threadList->izbaci(((PCB*)running)->id);
		((PCB*)running)->myThread=0;
		obrisi=((PCB*)running)->stack;
		blockFlag=1;
		runFlag=0;
		lockFlag=0;
		unlock();
        dispatch();
}
void lock(){
	asm cli;
}
void unlock(){
	asm sti;
}

void PCB::signal(SignalId signal){
	if (signal!=1 && signal!=2)
     signali[broj++].sent=(int)signal;
}

void PCB::registerHandler(SignalId signal, SignalHandler handler){
	if (signal<MAX1){
	Elem* novi=new Elem(handler);
	if (niz[signal]==0){
		niz[signal]=novi;
	}
	else {
		Elem* p=niz[signal];
		while (p->sled){
			p=p->sled;
		}
		p->sled=novi;
	}
	}
}

void PCB::unregisterAllHandlers(SignalId id){
	Elem* p=niz[id];
	while (p){
		Elem* stari=p;
		p=p->sled;
		delete stari;
	}
	niz[id]=0;
}

void PCB::swap(SignalId id, SignalHandler hand1, SignalHandler hand2){
	int ind1=0, ind2=0;
	Elem* p=niz[id], *t1, *t2;
	while (p && (ind1==0 || ind2==0)){
		if (ind1==0 && p->hand==hand1){
			ind1=1;
			t1=p;
		}
		if (ind2==0 && p->hand==hand2){
			ind2=1;
			t2=p;
		}
		p=p->sled;
	}
	if (ind1==1 && ind2==1){
		t1->hand=hand2;
		t2->hand=hand1;
	}
}

void PCB::blockSignal(SignalId signal){
	signali[signal].blocked=1;
}

void PCB::blockSignalGlobally(SignalId signal){
	globalBlocked[signal]=1;
}

void PCB::unblockSignal(SignalId signal){
    signali[signal].blocked=0;
}

void PCB::unblockSignalGlobally(SignalId signal){
	globalBlocked[signal]=0;
}












