/*
 * TimerList.h
 *
 *  Created on: May 15, 2019
 *      Author: OS1
 */

#ifndef TIMERLIST_H_
#define TIMERLIST_H_
#include "PCB.H"
#include "KernelS.h"

class PCB;
class KernelSem;

class TimerList {
private:
	struct Elem{
		PCB* pod;
		KernelSem* sem;
		Time time;
		Elem* sled;
		Elem(PCB* p, KernelSem* s, Time t){
			pod=p;
			sem=s;
			time=t;
			sled=0;
		}
	};
public:
	Elem* prvi;

	TimerList();
	void dodaj(PCB*,KernelSem*,Time);
	PCB* izbaci();//izbacivanje kod timer()
	PCB* _izbaci(KernelSem* );//izbacivanje kod signal()
	//int dohvati(KernelSem*);
	~TimerList();
};

#endif /* TIMERLIST_H_ */







