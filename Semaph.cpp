/*
 * Semaphore.cpp
 *
 *  Created on: May 15, 2019
 *      Author: OS1
 */

#include "Semaph.h"

Semaphore::Semaphore(int init) {
	lock();
	myImpl=new KernelSem(init);
	unlock();
}


Semaphore::~Semaphore() {
	lock();
	delete myImpl;
	unlock();
}

int Semaphore::val() const{
	return myImpl->value();

}
int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}
int Semaphore::signal(int n ){

	return myImpl->signal(n);

}
