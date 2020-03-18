/*
 * KernelSem.cpp
 *
 *  Created on: May 15, 2019
 *      Author: OS1
 */

#include "KernelS.h"


TimerList* KernelSem::timerHead=new TimerList();

KernelSem::KernelSem(int init=1){
	val=init;
	semHead=new SemList();
}

int KernelSem::wait(Time maxTimeToWait){
	int ret=1;
	lock();
	if (--val<0){
		blockFlag=1;
		if (maxTimeToWait==0){
			semHead->dodaj((PCB*)(PCB::running));
			dispatch();
		}
		else {
			timerHead->dodaj((PCB*)(PCB::running),this, maxTimeToWait);
			dispatch();
			ret=0;
		}
	}
	unlock();
	return ret;
}

int KernelSem::signal(int n=0){
	if (n<0) return n;
	lock();
	if (n==0){
	   if (++val<=0){
		PCB* p=semHead->uzmi();
		if (p==0) {
			p=timerHead->_izbaci(this);
		}
		   Scheduler::put(p);
		}
		unlock();
		return 0;
	}
	if (val>=0){
		val+=n;
		unlock();
		return 0;
     }
	int val1=-val,m=n,ret;
		if (val1<n) m=val1;
		val+=n;
		ret=m;
		PCB* p=semHead->uzmi();
		while (m>0 && p){
			Scheduler::put(p);
			p=semHead->uzmi();
			m--;}
		while (m>0){
		 p=timerHead->_izbaci(this);
		 Scheduler::put(p);
		 m--;
	}
		unlock();
		return ret;

}
int KernelSem::value() const{
	return val;
}
void KernelSem::increment(){
	val++;
}

KernelSem::~KernelSem(){
	delete semHead;
}












