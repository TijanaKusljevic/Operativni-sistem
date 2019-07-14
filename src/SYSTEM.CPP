/*
 * SYSTEM.CPP
 *
 *  Created on: Jul 22, 2017
 *      Author: OS1
 */

#include <DOS.H>
#include <NAMES.H>
#include "SCHEDULE.H"
#include <PCB.H>
#include <THREAD.H>
#include <SYSTEM.H>
#include <IDLE.H>
#include "KERNSEM.H"


volatile int System::ddispatch=0;
volatile unsigned oldTimerSEG, oldTimerOFF, newTimerSEG, newTimerOFF;
volatile unsigned tss, tsp, tbp;


Idle* System::idleThread=0;
Thread* System::firstThread=0;
volatile int System::lockFlag=0;


  void interrupt System::timer(...){

	if(!System::ddispatch) {
		if(PCB::running->timeSlice!=0){
			PCB::running->counter--;
		}
	  #ifndef BCC_BLOCK_IGNORE
	  		asm int 60h
	  #endif
	  	KernelSem::update();
	  	tick();
	 }

	if(lockFlag==0){

	if(PCB::running->timeSlice==0 && !System::ddispatch) return;

	if((PCB::running->counter==0 ) || System::ddispatch){
			System::ddispatch=0;
			PCB::running->counter=PCB::running->timeSlice;
#ifndef BCC_BLOCK_IGNORE
			asm{
				mov tsp,sp
				mov tss, ss
				mov tbp, bp
			}
#endif
			PCB::running->sp=tsp;
			PCB::running->ss=tss;
			PCB::running->bp=tbp;

			if(PCB::running->flag==RUNNING && PCB::running!=idleThread->getPCB()){
				PCB::running->setFlag(READY);
				Scheduler::put((PCB*)PCB::running);
			}

			PCB::running=Scheduler::get();

			if(PCB::running==0) {
				PCB::running=idleThread->getPCB();
			}

						tsp=PCB::running->sp;
						tss=PCB::running->ss;
						tbp=PCB::running->bp;
						PCB::running->flag=RUNNING;
#ifndef BCC_BLOCK_IGNORE
						asm{
									mov bp, tbp
									mov ss, tss
									mov sp, tsp
								}
#endif
		}
	}
}

  void System::inic(){

#ifndef BCC_BLOCK_IGNORE
	  newTimerSEG = FP_SEG(System::timer);
	  newTimerOFF = FP_OFF(System::timer);
	  	asm{
	  		cli
	          push es
	          push ax

	          mov ax,0
	          mov es,ax

	          mov ax, word ptr es:0022h
	          mov word ptr oldTimerSEG,ax
	          mov ax, word ptr es:0020h
	          mov word ptr oldTimerOFF, ax
	  	}
	  	asm{
	  		mov ax, newTimerSEG
	          mov word ptr es:0022h, ax
	  		mov ax, newTimerOFF
	          mov word ptr es:0020h, ax

	          mov ax, oldTimerSEG
	          mov word ptr es:0182h, ax
	          mov ax, oldTimerOFF
	          mov word ptr es:0180h, ax

	          pop ax
	          pop es
	          sti
	  	}
#endif

  }

  void System::restore(){
#ifndef BCC_BLOCK_IGNORE
	  asm {
	  		cli
	  		push es
	  		push ax

	  		mov ax,0
	  		mov es,ax


	  		mov ax, word ptr oldTimerSEG
	  		mov word ptr es:0022h, ax
	  		mov ax, word ptr oldTimerOFF
	  		mov word ptr es:0020h, ax

	  		pop ax
	  		pop es
	  		sti
	  	}
#endif
  }


void System::makeFirst(){

	System::firstThread=new Thread(256);

	System::firstThread->myPCB->setFlag(RUNNING);
	PCB::running=System::firstThread->myPCB;

	idleThread=new Idle();
	idleThread->start();

}

void System::ddelete(){
	delete System::firstThread;
	delete System::idleThread;
	KernelSem::deleteSl();
	PCB::deleteThreads();
}


