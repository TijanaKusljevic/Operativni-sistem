/*
 * KERNELEV.H
 *
 *  Created on: Aug 3, 2017
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "SYSTEM.H"

typedef unsigned char IVTNo;

#define PREPAREENTRY(number,old)\
	void interrupt interr##number(...);\
	IVTEntry *newEntry##number = new IVTEntry(number, interr##number);\
	void interrupt interr##number(...){\
		if(newEntry##number->kernelEvent!=0)\
		newEntry##number->kernelEvent->signal();\
		if (old==1 && newEntry##number->oldIntr!=0)\
		newEntry##number->oldIntr();\
		if(System::lockFlag==0)\
		dispatch();\
	}

class KernelEv{
public:
	KernelEv(IVTNo num);
	~KernelEv();
	void wait();
	void signal();

private:
	PCB* pcb;
	IVTNo entry;
	volatile int blocked;
	volatile int value;
};


#endif /* KERNELEV_H_ */
