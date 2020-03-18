/*
 * Thread.cpp
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#include "THREAD.H"
#include <iostream.h>

volatile int blockFlag = 0;
volatile int lockFlag = 0;
volatile int zahtevana_promena_konteksta=0;
Thread::Thread(StackSize stackSize , Time timeSlice )
{
	lock();
	myPCB=new PCB(stackSize,timeSlice,this);
	unlock();
}
void Thread::start(){
	lock();
	Scheduler::put(myPCB);
	//cout<<"stavili u scheduler"<<endl;
	unlock();
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

Thread::~Thread(){
	delete myPCB;
}

ID Thread::getId(){
	return myPCB->getId();
}
ID Thread::getRunningId(){
	return PCB::getRunningId();
}

Thread * Thread::getThreadById(ID id){
	return PCB::getThreadById(id);
}
void dispatch() { // sinhrona promena konteksta
	asm cli;
	zahtevana_promena_konteksta = 1;
	timer();
	asm sti;
}
void Thread::signal(SignalId signal){
	lock();
	myPCB->signal(signal);
	unlock();
}
void Thread::registerHandler(SignalId signal, SignalHandler handler){
	lock();
	myPCB->registerHandler(signal,handler);
	unlock();
}
void Thread::unregisterAllHandlers(SignalId id){
	lock();
	myPCB->unregisterAllHandlers(id);
	unlock();
}
void Thread::swap(SignalId id, SignalHandler hand1, SignalHandler hand2){
	lock();
	myPCB->swap(id,hand1,hand2);
    unlock();
}

void Thread::blockSignal(SignalId signal){
	lock();
	myPCB->blockSignal(signal);
	unlock();
}
void Thread::blockSignalGlobally(SignalId signal){
	lock();
	PCB::blockSignalGlobally(signal);
	unlock();
}

void Thread::unblockSignal(SignalId signal){
	lock();
	myPCB->unblockSignal(signal);
	unlock();
}

void Thread::unblockSignalGlobally(SignalId signal){
	lock();
	PCB::unblockSignalGlobally(signal);
	unlock();
}







