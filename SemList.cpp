/*
 * SemList.cpp
 *
 *  Created on: May 15, 2019
 *      Author: OS1
 */

#include "SemList.h"

SemList::SemList() {
	prvi=posl=0;
}

void SemList::dodaj(PCB* p){
	Elem* novi=new Elem(p);
	if (prvi==0){
		prvi=novi;
	}
	else posl->sled=novi;
	posl=novi;
}
PCB* SemList::uzmi(){
	PCB* p=0;
	if (prvi!=0){
		p=prvi->pod;
		prvi=prvi->sled;
		if (prvi==0) posl=0;
	}
	return p;
}
SemList::~SemList() {
	while (prvi){
		Elem* stari=prvi;
		prvi=prvi->sled;
		stari->pod=0;
		delete stari;
	}
	posl=0;
}

