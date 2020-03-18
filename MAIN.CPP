/*
 * MAIN.CPP
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */
#include "FUN.H"
#include <iostream.h>
#include <dos.h>
#include "PCB.H"
#include "Semaph.h"
#include "IVTEntry.h"
#include "Idle.h"
#include "user.h"
Idle* idle=0;
extern int userMain(int argc,char* argv[]);
int main(int argc, char* argv[]){
	inic();
	idle=new Idle();

    int val=userMain(argc,argv);
    delete idle;
	restore();
	return val;
}



