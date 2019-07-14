/*
 * LIST.H
 *
 *  Created on: Jul 17, 2017
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

#include "pcb.h"
#include "thread.h"

class Thread;

struct Elem{
	PCB* pcb;
	Elem* next;
};

class List{
private:
	Elem* first;
	Elem* last;

protected:
	friend class PCB;

public:
	List();
	~List();
	void add(PCB* k);
	PCB* getFirst();
	Thread* getThread(ID iid);
	void remove (PCB* p);
};


#endif /* LIST_H_ */
