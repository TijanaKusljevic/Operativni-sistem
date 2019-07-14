/*
 * KERNSEM.H
 *
 *  Created on: Jul 30, 2017
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_


class SemList;
class List;

class KernelSem{

private:
	volatile int value;
	List* myList;

public:
	KernelSem(int init=1);
	~KernelSem();
	int wait(int maxTimeToWait);
	void signal();
	int val() const;
	static void update();
	static void deleteSl();

protected:
	friend class SemList;
};




#endif /* KERNSEM_H_ */
