/*
 * SYSTEM.H
 *
 *  Created on: Jul 22, 2017
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "PCB.H"
#include "THREAD.H"

class PCB;
class Thread;
class Idle;


void tick();

class System{

public:
	volatile static int ddispatch;
	static void interrupt timer(...);
	static void inic();
	static void restore();
	static void makeFirst();
	static void ddelete();
	static Thread* firstThread;
	static Idle* idleThread;
	volatile static int lockFlag;

};


#endif /* SYSTEM_H_ */
