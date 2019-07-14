/*
 * KERNELEV.CPP
 *
 *  Created on: Aug 4, 2017
 *      Author: OS1
 */

#include "KERNELEV.h"
#include "NAMES.H"
#include "SCHEDULE.H"
#include "PCB.H"
#include "IVTENTRY.H"


KernelEv::KernelEv(IVTNo num){
	System::lockFlag++;
	entry=num;
	pcb=PCB::running;
	blocked=0;
	value=0;
	if(IVTEntry::ivt[entry]!=0)
		IVTEntry::ivt[entry]->kernelEvent=this;
	System::lockFlag--;
}

KernelEv::~KernelEv(){
	System::lockFlag++;
	delete IVTEntry::ivt[entry];
	blocked=0;
	pcb=0;
	System::lockFlag--;
}

void KernelEv::wait(){
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	if (PCB::running==pcb) {
		if (value==0){
			PCB::running->setFlag(SUSPENDED);
			blocked=1;
			dispatch();
		}
		else value=0;
	}
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

void KernelEv::signal(){
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	if (blocked!=0){
		pcb->setFlag(READY);
		Scheduler::put(pcb);
		blocked=0;
		value=0;
	}
	else value=1;

#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}
