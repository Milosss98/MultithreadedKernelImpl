/*
 * FUN.CPP
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#include "FUN.H"
#include "Idle.h"
#include "user.h"
#define MAX1 16
extern volatile int zahtevana_promena_konteksta;
extern volatile int blockFlag;
extern volatile int lockFlag;
extern void tick();
int runFlag=0;
volatile unsigned* obrisi=0;
unsigned tsp,tss,tbp;
int broj,ind,k;
unsigned pomocni[MAX1];
unsigned oldTimerOFF, oldTimerSEG;
extern Idle* idle;
void inic(){
	asm{
				cli
				push es
				push ax

				mov ax,0   //  ; inicijalizuje rutinu za tajmer
				mov es,ax

				mov ax, word ptr es : 0022h //; pamti staru rutinu
				mov word ptr oldTimerSEG, ax
				mov ax, word ptr es : 0020h
				mov word ptr oldTimerOFF, ax

				mov word ptr es : 0022h, seg timer	 //postavlja
				mov word ptr es : 0020h, offset timer //novu rutinu

				mov ax, oldTimerSEG	 //	postavlja staru rutinu
				mov word ptr es : 0182h, ax //; na int 60h
				mov ax, oldTimerOFF
				mov word ptr es : 0180h, ax

				pop ax
				pop es
				sti
			}
}
void interrupt timer(...){
	tick();
	if (!zahtevana_promena_konteksta) {
		if (runFlag==0){
		PCB::running->counter--;
		}
		if (KernelSem::timerHead->prvi){
		   KernelSem::timerHead->prvi->time--;
	       PCB* p = KernelSem::timerHead->izbaci();
	       while (p){
	    	   Scheduler::put(p);
	    	   p=KernelSem::timerHead->izbaci();
		   }
		}

		//cout<<"smanjili counter"<<endl;
	}
			if ((PCB::running->counter == 0) || zahtevana_promena_konteksta) {
				if (lockFlag == 0) {
					asm{
						// cuva sp
						mov tsp, sp
						mov tss, ss
						mov tbp, bp
					}

					PCB::running->sp = tsp;
					PCB::running->ss = tss;
					PCB::running->bp = tbp;
					PCB::running->counter = PCB::running->timeSlice;
					//cout<<"Sacuvali kontekst"<<endl;
					if (PCB::running->isOver == 0 && blockFlag==0) {
						Scheduler::put((PCB*)PCB::running);// Scheduler
					}
					else blockFlag=0;
					PCB::running = Scheduler::get();
					if (PCB::running==0) PCB::running=(volatile PCB*)(idle->myPCB);
					tsp = PCB::running->sp;
					tss = PCB::running->ss;
					tbp= PCB::running->bp;


				    asm{
						mov sp, tsp   // restore sp
				        mov ss, tss
				    	mov bp, tbp
				       }
					//cout<<"promenili kontekst"<<endl;
					 zahtevana_promena_konteksta = 0;
                      if (obrisi!=0){
                    	  delete (unsigned*)obrisi;
                    	  obrisi=0;
                      }


				}

			}


			// poziv stare prekidne rutine koja se
			 // nalazila na 08h, a sad je na 60h
			 // poziva se samo kada nije zahtevana promena
			 // konteksta – tako se da se stara
			  //rutina poziva samo kada je stvarno doslo do prekida
			if (!zahtevana_promena_konteksta) asm int 60h;
			if (runFlag==0){
			runFlag=1;
			lockFlag=1;
				ind=0; broj=0;
			    while(1){
			    	k=PCB::running->signali[ind].sent;
			    	if (k==-1) break;
			    	asm sti;
			    	if (PCB::globalBlocked[k] || PCB::running->signali[k].blocked ){
			    		pomocni[broj++]=k;
			    	}
			    	 else {
				          PCB::Elem* tek=PCB::running->niz[k];
				          while (tek){
			      			 (*(tek->hand))();
				               tek=tek->sled;
				      		 }
				        }
				          PCB::running->signali[ind].sent=-1;
				          ind++;
				          if (ind==MAX1) break;
				   }
				     for (ind=0;ind<broj;ind++){
				       PCB::running->signali[ind].sent=pomocni[ind];
				        }
				       PCB::running->broj=broj;
                       lockFlag=0;
                       runFlag=0;
			}

}



/*void obrada(){
	lockFlag=1;
	asm sti;
	ind=0; broj=0;
    while(1){
    	k=PCB::running->signali[ind].sent;
    	if (k==-1) break;
    	if (PCB::globalBlocked[k] || PCB::running->signali[k].blocked ){
    		pomocni[broj++]=k;
    	}
    	 else {
	          PCB::Elem* tek=PCB::running->niz[k];
	          while (tek){
	        	  cout<<"unutrasnji while"<<endl;
      			 (*(tek->hand))();
	               tek=tek->sled;
	      		 }
	        }
	          PCB::running->signali[ind].sent=-1;
	          ind++;
	          if (ind==MAX1) break;
	   }
	     for (ind=0;ind<broj;ind++){
	       PCB::running->signali[ind].sent=pomocni[ind];
	        }
	       PCB::running->broj=broj;
	       lockFlag=0;

}*/

void restore() {
		asm{
			cli
			push es
			push ax

			mov ax,0
			mov es,ax


			mov ax, word ptr oldTimerSEG
			mov word ptr es : 0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es : 0020h, ax

			pop ax
			pop es
			sti
		}
}
