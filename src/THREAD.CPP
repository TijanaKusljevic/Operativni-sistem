/*
 * THREAD.CPP
 *
 *  Created on: Jul 21, 2017
 *      Author: OS1
 */

#include "SYSTEM.H"
#include "NAMES.H"
#include "PCB.H"
#include "THREAD.H"
#include "schedule.h"


Thread::Thread(StackSize stackSize, Time timeSlice){
	myPCB=new PCB(this,stackSize, timeSlice);
}

void Thread::start(){
	System::lockFlag++;
	if(myPCB->flag==PREPARING){
	myPCB->preparePCB();
	myPCB->flag=READY;
	Scheduler::put(myPCB);
	System::lockFlag--;
	}
}

Thread::~Thread(){
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
		waitToComplete();
		PCB::threads->remove(myPCB);
		myPCB->thread = 0;
		delete myPCB;
#ifndef BCC_BLOCK_IGNORE
		unlock;
#endif
}

void dispatch(){
	System::ddispatch=1;
#ifndef BCC_BLOCK_IGNORE
	//System::timer();
	asm int 08h
#endif
}

ID Thread::getId(){
	return myPCB->id;
}

ID Thread::getRunningId(){
	System::lockFlag++;
	ID ret=PCB::running->id;
	System::lockFlag--;
	return ret;
}

void Thread::waitToComplete(){
	System::lockFlag++;
	if(myPCB->flag==RUNNING || myPCB->flag==FINISHED || myPCB->flag==PREPARING || PCB::running==System::idleThread || PCB::running==System::firstThread)
	{
		System::lockFlag--; return;
	}
	PCB::running->flag=SUSPENDED;
	myPCB->myList->add(PCB::running);
	System::lockFlag--;
	dispatch();
}

Thread* Thread::getThreadById(ID id){
	System::lockFlag++;
	Thread* t=PCB::threads->getThread(id);
	System::lockFlag--;
	return t;
}
