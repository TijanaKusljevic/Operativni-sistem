/*
 * IDLE.H
 *
 *  Created on: Aug 2, 2017
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "THREAD.H"

class Thread;
class PCB;

class Idle: public Thread{
public:
	Idle();
	void start();
	virtual void run();
	PCB* getPCB();
};



#endif /* IDLE_H_ */
