/*
 * TimerList.cpp
 *
 *  Created on: May 15, 2019
 *      Author: OS1
 */

#include "TimerL.h"

TimerList::TimerList(){
	prvi=0;
}

void TimerList::dodaj(PCB* p, KernelSem* s,Time t){
	Elem* novi=new Elem(p,s,t);
	Elem* tek = prvi, *pret = 0;
	Time t1=0;
	while (tek) {
		t1 += tek->time;
		if (t1 > t) {
			break;
	    }
		pret = tek;
		tek = tek->sled;
	}
	if (pret == 0) {
			prvi = novi;
		}
	else {
		pret->sled = novi;
		Time t2=0;
		if (tek) t2 = tek->time;
		novi->time -= t1-t2;
	}
	novi->sled = tek;
	if (tek) {
		tek->time -= novi->time;
	}
}

PCB* TimerList::izbaci(){
	PCB* p=0;
	if (prvi && prvi->time==0){
		p=prvi->pod;
		prvi->pod=0;
		Elem* stari=prvi;
		stari->sem->increment();
		stari->sem=0;
		prvi=prvi->sled;
		delete stari;
	}
	return p;
}

PCB* TimerList:: _izbaci(KernelSem* s){
	Elem* tek=prvi, *pret=0;
	while (tek){
		if (tek->sem==s){
			PCB* p=tek->pod;
			Time t=tek->time;
			if (tek->sled) tek->sled->time+=t;
			if (pret==0) prvi=prvi->sled;
			pret->sled=tek->sled;
			tek->pod=0;
			tek->sem=0;
			delete tek;
			return p;
		}
		pret=tek;
		tek=tek->sled;
	}
	return 0;
}
/*int TimerList::dohvati(KernelSem* s){
	int b=-1;
	Elem* tek=prvi;
	while(tek){
		if (tek->sem==s){
			b=tek->blocked;
			return b;
		}
	}
	return b;
}*/
TimerList::~TimerList(){
	while (prvi){
		Elem* stari=prvi;
		stari->sem=0;
		stari->pod=0;
		prvi=prvi->sled;
		delete stari;
	}
}











