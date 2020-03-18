/*
 * Semaphore.h
 *
 *  Created on: May 15, 2019
 *      Author: OS1
 */

#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_
#include "KernelS.h"
typedef unsigned int Time;
class KernelSem;

class Semaphore
{
public:
	Semaphore(int init=1);
	virtual ~Semaphore();
	virtual int wait(Time );
	virtual int signal(int n=0);

	int val() const;

private:
	KernelSem *myImpl;

};
#endif
