/*
 * IVTEntry.h
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#define MAX 256
#include "KernelEv.h"

class KernelEv;
typedef unsigned char IVTNo;
typedef void interrupt (*pInterrupt)(...);
#define PREPAREENTRY(numEntry, call)\
	void interrupt 	rutina##numEntry(...); \
    IVTEntry newEntry##numEntry(numEntry, rutina##numEntry); \
    void interrupt rutina##numEntry(...) {\
    	newEntry##numEntry.signal();\
    	if (call == 1) \
		{ newEntry##numEntry.callOld(); }\
		}
class IVTEntry {
private:
	static IVTEntry* niz[MAX];
	IVTNo ivtNo;
	KernelEv* event;
	pInterrupt oldRut;
	friend class KernelEv;
public:
	IVTEntry(IVTNo,pInterrupt);
	void callOld();
	void signal();
	static void dodaj(IVTNo, KernelEv*);
	void izbaci();
	~IVTEntry();
};
#endif /* IVTENTRY_H_ */
