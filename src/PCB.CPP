/*
 * PCB.CPP
 *
 *  Created on: Jul 18, 2017
 *      Author: OS1
 */


#include "PCB.H"
#include "NAMES.H"
#include <dos.h>
#include "SYSTEM.H"
#include "THREAD.H"
#include "SCHEDULE.H"

ID PCB::lastID=0;
PCB* PCB::running=0;
List* PCB::threads=new List();


PCB::PCB(Thread* t, StackSize stackSize, Time num){
	id=++lastID;
	if(stackSize > maxStackSize) {
		size=maxStackSize/sizeof(unsigned);
	} else {
		size=stackSize/sizeof(unsigned);
	}
	timeSlice=num;
	thread=t;
	counter=timeSlice;
	flag=PREPARING;
	way=1;
	stack=new unsigned[size];
	bp=ss=sp=0;
	myList=new List();
	System::lockFlag++;
	threads->add(this);
	System::lockFlag--;
}

PCB::~PCB(){
	delete stack;
	if(myList!=0) delete myList;
}

void PCB::preparePCB(){
#ifndef BCC_BLOCK_IGNORE
		stack[size - 2] = 0x200;
		stack[size - 3] = FP_SEG(&wrapper);
		stack[size - 4] = FP_OFF(&wrapper);
		stack[size - 13] = FP_OFF(stack + size - 1);

		ss = FP_SEG(stack + size - 13);
		bp = sp = FP_OFF(stack + size - 13);
#endif
}


void PCB::wrapper(){
	running->thread->run();
	System::lockFlag++;
	running->flag=FINISHED;
	running->timeSlice=0;
	PCB* p=running->myList->getFirst();
	while(p!=0){
		p->flag=READY;
		Scheduler::put(p);
		p=running->myList->getFirst();
	}
	System::lockFlag--;
	dispatch();
}

void PCB::setFlag(int i){
	flag=i;
}

void PCB::setWay(int i){
	way=i;
}

int PCB::getWay(){
	return way;
}

int PCB::getFlag(){
	return flag;
}

void PCB::deleteThreads(){
	delete threads;
}
