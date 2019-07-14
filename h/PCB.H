/*
 * PCB.H
 *
 *  Created on: Jul 17, 2017
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "THREAD.H"
#include "SYSTEM.H"
#include "LIST.H"

class System;
class List;

#define maxStackSize 65536 //32767

class PCB{

protected:
	friend class Thread;
	friend class System;
	friend class List;

private:
	static ID lastID;
	ID id;
	unsigned *stack;
	unsigned ss, sp, bp;
	volatile int flag;  //stanje niti
	volatile Time counter;
	Time timeSlice;
	StackSize size;
	Thread* thread;
	List* myList;
	volatile int way; //nacin na koji se zavrsava wait

	static void wrapper();

public:
	static PCB* running;
	static List* threads;

	PCB(Thread* t,StackSize stackSize=defaultStackSize, Time num=defaultTimeSlice);
	~PCB();
	void preparePCB();
	void setFlag(int i);
	void setWay(int i);
	int getWay();
	int getFlag();
	static void deleteThreads();
};

#endif /* PCB_H_ */
