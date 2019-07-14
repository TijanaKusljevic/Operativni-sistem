/*
 * KERNSEM.CPP
 *
 *  Created on: Jul 30, 2017
 *      Author: OS1
 */

#include "KERNSEM.H"
#include "LIST.H"
#include "SYSTEM.H"
#include "NAMES.H"
#include "SCHEDULE.H"
#include "SEMLIST.H"
#include "PCB.H"

SemList* sl=new SemList();


KernelSem::KernelSem(int init){
	value=init;
	myList=new List();
}

KernelSem::~KernelSem(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	if(myList!=0){
	PCB* temp=myList->getFirst();
	while(temp){
		temp->setFlag(READY);
		Scheduler::put(temp);
		temp=myList->getFirst();
		sl->remove(temp);
	}
	}
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

int KernelSem::wait(int maxTimeToWait){

#ifndef BCC_BLOCK_IGNORE
	lock;
#endif

	PCB::running->setWay(1);
	if(--value<0){
		if(maxTimeToWait==0) {
			myList->add(PCB::running);
		} else {
			sl->add(PCB::running,maxTimeToWait,this);
			myList->add(PCB::running);
		}//else

	PCB::running->setFlag(SUSPENDED);
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
	dispatch();
	}

	else {
#ifndef BCC_BLOCK_IGNORE
		unlock;
#endif
	}

	int ret= PCB::running->getWay();
	return ret;
}

void KernelSem::signal(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	if(value++<0){
		PCB* p=myList->getFirst();
		sl->remove(p);
		p->setFlag(READY);
		Scheduler::put(p);
	}
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

int KernelSem::val()const{
	return value;
}

void KernelSem::update(){
	sl->updateTimer();
}


void KernelSem::deleteSl(){
	delete sl;
}





