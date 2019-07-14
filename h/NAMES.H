/*
 * NAMES.H
 *
 *  Created on: Jul 17, 2017
 *      Author: OS1
 */

#ifndef NAMES_H_
#define NAMES_H_

#define lock {asm{pushf; cli;}}
#define unlock {asm {popf}}

#define PREPARING 0
#define  READY 1
#define  SUSPENDED 2
#define  RUNNING 3
#define FINISHED 4




#endif /* NAMES_H_ */
