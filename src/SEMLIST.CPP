/*
 * SEMLIST.CPP
 *
 *  Created on: Aug 1, 2017
 *      Author: OS1
 */

#include "SEMLIST.H"
#include "NAMES.H"
#include "SCHEDULE.H"
#include "PCB.H"
#include "KERNSEM.H"


void SemList::add(PCB* p,Time t, KernelSem* ks){
	Elem* e=new Elem();
	e->next=0;
	e->pcb=p;
	e->sem=ks;
	e->time=t;
	if(head==0) {
		head=e;
	} else{
		if(head==0) {head=e; return;}
		Time sum1=0;
		Time sum=head->time;
		Elem* temp=head;
		Elem* prev=0;
		while(temp!=0 && sum<=e->time){
			sum1=sum;
			prev=temp;
			temp=temp->next;
			if(temp!=0) {sum+=temp->time;}
		}
		if(sum<e->time) {
			e->time-=sum;
		}else{
			e->time-=sum1;
		}
		if(prev!=0){
			prev->next=e;
		} else{
			head=e;
		}
		if(temp!=0) {
			e->next=temp;
			temp->time-=e->time;
		}
	}
}

void SemList::remove(PCB* p){
	Elem* temp=head;
	Elem* prev=0;
	while(temp!=0 && temp->pcb!=p){
		prev=temp;
		temp=temp->next;
	}
	if(temp!=0){
		if(temp->next!=0){
			temp->next->time+=temp->time;
		}
		if(prev!=0){
			prev->next=temp->next;
		} else {
			head=temp->next;
		}

		delete temp;
	}
}


void SemList::updateTimer(){
	if(head==0) {
		return;
	}
	Elem* temp=head;
	Elem* prev=0;
	temp->time--;
	while( temp!=0 &&  temp->time==0){
		prev=temp;
		temp=temp->next;
		head=temp;
		prev->pcb->setFlag(READY);
		prev->pcb->setWay(0);
		prev->sem->myList->remove(prev->pcb);
		prev->sem->value++;
		Scheduler::put(prev->pcb);
		prev->next=0;
		delete prev;
	}
}



void SemList::letAll(){
	Elem* temp=head;
	Elem* rem=0;
	while(temp!=0){
		temp->pcb->setFlag(READY);
		Scheduler::put(temp->pcb);
		rem=temp;
		temp=temp->next;
		remove(rem->pcb);
	}
	head=0;
}

SemList::~SemList(){
	letAll();
}



