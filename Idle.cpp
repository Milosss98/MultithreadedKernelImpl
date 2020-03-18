/*
 * Idle.cpp
 *
 *  Created on: May 27, 2019
 *      Author: OS1
 */

#include "Idle.h"
#include <iostream.h>

Idle::Idle():Thread(){ }
Idle::~Idle() {
	myPCB->isOver=1;
}
void Idle::run(){
	while(1){
		lock();
		blockFlag=1;
		unlock();
		dispatch();
	}
}
