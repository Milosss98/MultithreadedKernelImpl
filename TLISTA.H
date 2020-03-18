/*
 * TLISTA.H
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#ifndef TLISTA_H_
#define TLISTA_H_
#include "PCB.H"

class Thread;
typedef int ID;
class TLista {
private:
	struct Elem{
	public:
		Thread* pod;
		ID id;
		Elem* sled;
		Elem(Thread* t,ID id1){
			pod=t;
			id=id1;
			sled=0;
		}
	};
	Elem* prvi, *posl;
public:
	TLista();
	void dodaj(Thread* t,ID id1);
	void izbaci(ID id);
	Thread* dohvati(ID id);
	virtual ~TLista();
};

#endif /* TLISTA_H_ */
