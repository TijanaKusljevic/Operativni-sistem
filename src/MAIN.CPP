/*
 * PROBA.CPP
 *
 *  Created on: Jul 19, 2017
 *      Author: OS1
 */

#include "SYSTEM.H"

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]){
	System::makeFirst();
	System::inic();
	userMain(argc, argv);
	System::restore();
	System::ddelete();
}



