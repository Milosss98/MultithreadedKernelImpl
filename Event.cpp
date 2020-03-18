/*
 * Event.cpp
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */

#include "Event.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo){
	lock();
	myImpl=new KernelEv(ivtNo);
	unlock();
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}

Event::~Event(){
	delete myImpl;
}
