/*
 * LIST.CPP
 *
 *  Created on: Jul 17, 2017
 *      Author: OS1
 */

#include "names.h"
#include "list.h"

List::List(){
	first=0;
	last=0;
}

List::~List(){

	Elem *t=0;
	t=first;
	while(t!=0){
		first=t;
		t=t->next;
		delete first;
	}

}

void List::add(PCB* k){

	if(first==0) {
		Elem *p=new Elem();
		p->pcb=k;
		p->next=0;
		first=last=p;
		return;
	}
	else {
		Elem *temp=first;
		Elem *prev=0;
		while(temp!=0 && temp->pcb!=k){
		prev=temp;
		temp=temp->next;
		}
		if(temp!=0) {return;}
		Elem *n=new Elem();
		n->pcb=k;
		n->next=0;
		last->next=n;
		last=n;
		return;
	}

}

PCB* List::getFirst(){
	Elem* ret=first;
	if(first==0) return 0;
	first=first->next;
	if(first==0) last=first;
	PCB* r=ret->pcb;
	ret->next=0;
	delete ret;
	return r;
}

Thread* List::getThread(ID iid){
	Elem* temp=first;
	while(temp){
		if(temp->pcb->id==iid) return temp->pcb->thread;
		temp=temp->next;
	}
	return 0;
}

void List::remove(PCB* p){
	Elem* temp=first;
	Elem* prev=0;
	while(temp!=0 && temp->pcb!=p){
		prev=temp;
		temp=temp->next;
	}
	if(temp==0) return;
	if(temp==first){
		first=first->next;
		if(first==0) last=0;
	} else{
		prev->next=temp->next;
		if(prev->next==0) last=prev;
	}
	temp->next=0;
	delete temp;
	return;


}
