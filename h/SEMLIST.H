/*
 * SEMLIST.H
 *
 *  Created on: Aug 1, 2017
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_

class KernelSem;
class PCB;

typedef unsigned int Time;

class SemList{
protected:
	struct Elem{
		PCB* pcb;
		Time time;
		KernelSem* sem;
		Elem* next;
	};
	Elem* head;

public:
	SemList() {
		head=0;
	}
	~SemList();
	void add(PCB* p,Time t, KernelSem* ks);
	void remove(PCB* p);
	void updateTimer();
	void letAll();
};



#endif /* SEMLIST_H_ */
