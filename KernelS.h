/*
 * KernelSem.h
 *
 *  Created on: May 15, 2019
 *      Author: OS1
 */

#ifndef KERNELSEM_H_
#define KERNELSEM_H_
#include "Semaph.h"
#include "SemList.h"
#include "TimerL.h"
#include "PCB.H"

class PCB;
class SemList;
class TimerList;

class KernelSem {
private:
	SemList* semHead;
	int val;
public:
	static TimerList* timerHead;

	KernelSem(int );
	~KernelSem();

	int wait(Time );
	int signal(int );

	int value() const;
	void increment();

};

#endif /* KERNELSEM_H_ */
