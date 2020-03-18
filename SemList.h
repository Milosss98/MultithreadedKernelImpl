/*
 * SemList.h
 *
 *  Created on: May 15, 2019
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_
#include "KernelS.h"
#include "PCB.H"
class PCB;
class SemList {
private:
	struct Elem {
			PCB* pod;
			Elem* sled;
			Elem(PCB* p) {
				pod = p;
				sled = 0;
			}
		};
		Elem* prvi, *posl;
public:
		SemList();
		void dodaj(PCB* p);
		PCB* uzmi();
		~SemList();
	};


#endif /* SEMLIST_H_ */
