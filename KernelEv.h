/*
 * KernelEv.h
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "IVTEntry.h"
#include "PCB.h"

typedef unsigned char IVTNo;
class PCB;
class KernelEv {
private:
	IVTNo ivtNo;
	int val;
	PCB* holder;
public:
	KernelEv(IVTNo);
	~KernelEv();

	void wait();
	void signal();
};

#endif /* KERNELEV_H_ */
