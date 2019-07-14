/*
 * IVTENTRY.H
 *
 *  Created on: Aug 4, 2017
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "KERNELEV.H"

typedef unsigned char IVTNo;

typedef void interrupt (*inter)(...);

class IVTEntry{
public:
	IVTEntry(IVTNo num, inter newIntr);
	~IVTEntry();
	static IVTEntry* ivt[256];
	KernelEv* kernelEvent;
	inter oldIntr;

private:
	IVTNo ivtno;
};



#endif /* IVTENTRY_H_ */
