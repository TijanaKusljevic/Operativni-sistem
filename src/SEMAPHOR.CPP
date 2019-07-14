/*
 * SEMAPHOR.CPP
 *
 *  Created on: Jul 30, 2017
 *      Author: OS1
 */

#include "SEMAPHOR.H"
#include "NAMES.H"
#include "KERNSEM.H"

Semaphore::Semaphore(int init){
	if(init<0) init=1;
	myImpl=new KernelSem(init);
}

Semaphore::~Semaphore(){
	if(myImpl!=0) delete myImpl;
}

int Semaphore::wait(Time maxTimeToWait){
	int ret=myImpl->wait(maxTimeToWait);
	return ret;
}

void Semaphore::signal(){
	myImpl->signal();
}

int Semaphore::val()const{
	int ret=myImpl->val();
	return ret;
}


