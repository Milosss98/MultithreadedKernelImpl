/*
 * BLOCKL.CPP
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#include "BLOCKL.H"

BlockL::BlockL(){
	prvi=posl=0;
}
void BlockL::dodaj(PCB* p){
	Elem* novi = new Elem(p);
	if (prvi==0){
		prvi=novi;
	}
	else posl->sled=novi;
	posl=novi;
}
PCB* BlockL::uzmi(){
	PCB* p=0;
	if (prvi!=0){
		 p=prvi->pod;
		prvi=prvi->sled;
		if (prvi==0) posl=0;
	}
	return p;
}
BlockL::~BlockL(){
	while (prvi){
		Elem* stari=prvi;
		prvi=prvi->sled;
		delete stari;
	}
}
