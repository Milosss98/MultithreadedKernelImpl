/*
 * PCB.h

 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "THREAD.H"
#include "BLOCKL.H"
#include "TLISTA.H"
#include <dos.h>
#define MAX1 16
typedef int ID;
typedef unsigned int Time;
typedef unsigned long StackSize;
typedef void (*SignalHandler)();
typedef unsigned SignalId;
class Thread;
class BlockL;
class TLista;
extern volatile int blockFlag;
extern volatile  unsigned* obrisi;
extern int runFlag;
extern volatile int lockFlag;
class PCB {
	unsigned sp,ss,bp;
	unsigned *stack;
	Time timeSlice;
	Time counter;
	ID id;
	BlockL* blockList;
	Thread* myThread;
	Thread* parent;
    int isOver;
    static ID posID;

    struct Elem{
    	SignalHandler hand;
    	Elem* sled;
    	Elem(SignalHandler s){
    		hand=s;
    		sled=0;
    	}
    };
    struct Signal{
    	SignalId blocked;
    	int sent;
    	Signal(){
    		blocked=0;
    		sent=-1;
    	}
    };
    static SignalId globalBlocked[MAX1];
    Signal signali[MAX1];
    Elem* niz[MAX1];
    int broj;
public:
    volatile static PCB* running;
    static TLista* threadList;
   	PCB(StackSize , Time , Thread* );
	static void wrapper();
	void waitToComplete();
	ID getId();
	static ID getRunningId();
	static Thread* getThreadById(ID id);
	virtual ~PCB();
	void signal(SignalId signal);
	void registerHandler(SignalId signal, SignalHandler handler);
	void unregisterAllHandlers(SignalId id);
	void swap(SignalId id, SignalHandler hand1, SignalHandler hand2);

    static void brisanje();

	void blockSignal(SignalId signal);
	static void blockSignalGlobally(SignalId signal);
	void unblockSignal(SignalId signal);
	static void unblockSignalGlobally(SignalId signal);
	friend void interrupt timer(...);
	friend class Idle;
};
void lock();
void unlock();

#endif /* PCB_H_ */
