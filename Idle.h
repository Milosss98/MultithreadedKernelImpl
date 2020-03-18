/*
 * Idle.h
 *
 *  Created on: May 27, 2019
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_
#include "THREAD.H"

class Idle : public Thread{
	public:
	Idle();
	~Idle();
	void run();
};

#endif /* IDLE_H_ */
