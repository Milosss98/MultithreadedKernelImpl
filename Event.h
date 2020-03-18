/*
 * Event.h
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "KernelEv.h"
typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
	Event(IVTNo);
	~Event();

	void wait();
protected:
	void signal();
private:
	KernelEv* myImpl;
};

#endif /* EVENT_H_ */
