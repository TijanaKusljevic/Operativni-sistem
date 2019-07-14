/*
 * IVTENTRY.CPP
 *
 *  Created on: Aug 4, 2017
 *      Author: OS1
 */

#include "IVTENTRY.H"
#include <DOS.H>
#include "NAMES.H"
#include "SYSTEM.H"


IVTEntry* IVTEntry::ivt[256];

IVTEntry::IVTEntry(IVTNo num, inter newIntr){
	System::lockFlag++;
	ivtno=num;
	kernelEvent=0;
#ifndef BCC_BLOCK_IGNORE
	oldIntr=getvect(ivtno);
	setvect(ivtno, newIntr);
#endif
	ivt[ivtno]=this;
	System::lockFlag--;
}


IVTEntry::~IVTEntry(){
	System::lockFlag++;
	kernelEvent=0;
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtno, oldIntr);
#endif
	oldIntr=0;
	System::lockFlag--;
}

