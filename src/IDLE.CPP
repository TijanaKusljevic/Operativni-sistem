/*
 * IDLE.CPP
 *
 *  Created on: Aug 2, 2017
 *      Author: OS1
 */

#include "IDLE.H"
#include "PCB.H"
#include "NAMES.H"


Idle::Idle():Thread(){}

void Idle::run(){
	for(int i=0; i<15; i++){
		if(i==10){
			i=0;
		}
	}
}

void Idle::start(){
	myPCB->setFlag(READY);
	myPCB->preparePCB();
}

PCB* Idle::getPCB(){
	return myPCB;
}



