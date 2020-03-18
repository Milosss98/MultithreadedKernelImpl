/*
 * TLISTA.CPP
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#include "TLISTA.H"

TLista::TLista() {
	prvi=posl=0;
}
void TLista::dodaj(Thread* t, ID id1){
	Elem* novi=new Elem(t,id1);
	if (prvi==0){
		prvi=novi;
	}
	else posl->sled=novi;
	posl=novi;
	//cout<<"dodata "<<endl;
}
void TLista::izbaci(ID id){
	//cout<<"TLista izbacivanje pocelo"<<endl;
	Elem* tek=prvi, *pret=0;
	while (tek){
		if (tek->id==id) break;
		pret=tek;
		tek=tek->sled;
	}
	if (pret==0){
		prvi=prvi->sled;
		if (prvi==0) posl=0;
	}
	else pret->sled=tek->sled;
	delete tek;

	//cout<<"Izbacivanje zavrseno"<<endl;

}
Thread* TLista::dohvati(ID id){
	Elem* tek=prvi;
	while(tek){
		if (tek->id==id)
			return tek->pod;
	}
	return 0;
}

TLista::~TLista() {
	while (prvi){
		Elem* stari=prvi;
		prvi=prvi->sled;
		delete stari;
	}
	posl=0;
}

