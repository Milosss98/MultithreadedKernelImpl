/*
 * IVTEntry.cpp
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */

#include "IVTEntry.h"
#include <dos.h>

IVTEntry* IVTEntry::niz[MAX]={0};

IVTEntry::IVTEntry(IVTNo numEntry, pInterrupt inter){
      ivtNo=numEntry;
#ifndef BCC_BLOCK_IGNORE_
      oldRut=getvect(numEntry);
      setvect(numEntry,inter);
#endif
      event=0;
      niz[ivtNo]=this;
}

void IVTEntry::callOld(){
     (*oldRut)();
}
void IVTEntry::signal(){
	if (event!=0){
		event->signal();
	}
}

void IVTEntry::dodaj(IVTNo num, KernelEv* ev){
	niz[num]->event=ev;
}
void IVTEntry::izbaci(){
	this->event=0;
}
IVTEntry::~IVTEntry(){
#ifndef _BCC_BLOCK_IGNORE_
	setvect(ivtNo,oldRut);
#endif
	//cout<<"ovde"<<endl;
	event=0;
	niz[ivtNo]=0;
}











