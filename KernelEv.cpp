/*
 * KernelEv.cpp
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */

#include "KernelEv.h"

KernelEv::KernelEv(IVTNo numEntry){
	holder=(PCB*)(PCB::running);
	ivtNo=numEntry;
	val=0;
	IVTEntry::dodaj(numEntry,this);
}

void KernelEv::wait(){
	 lock();
     if ((PCB*)(PCB::running)==holder){
    	 lock();
         val=0;
    	 blockFlag=1;
    	 unlock();
    	 dispatch();
    	 }
     unlock();
}

void KernelEv::signal(){
	lock();
	if (val==0){
		lock();
	Scheduler::put(holder);
	val=1;
	}
	unlock();
	dispatch();
}

KernelEv::~KernelEv(){
	holder=0;
	IVTEntry::niz[ivtNo]->izbaci();
}
















