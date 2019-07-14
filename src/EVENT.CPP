/*
 * EVENT.CPP
 *
 *  Created on: Aug 3, 2017
 *      Author: OS1
 */

#include "EVENT.H"
#include "NAMES.H"

Event::Event(IVTNo ivtNo){
	myImpl=new KernelEv(ivtNo);
}

Event::~Event(){
	delete myImpl;
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}




