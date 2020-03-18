/*
 * BLOCKL.H
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#ifndef BLOCKL_H_
#define BLOCKL_H_
#include "PCB.H"
class PCB;
class BlockL {
private:
	struct Elem{
		PCB* pod;
		Elem* sled;
		Elem(PCB* p){
			pod=p;
			sled=0;
		}
	};
	Elem* prvi, *posl;
public:
     BlockL();
     void dodaj(PCB* p);
     PCB* uzmi();
     ~BlockL();
};

#endif /* BLOCKL_H_ */
