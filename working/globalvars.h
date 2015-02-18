#ifndef _globalvars_H_  
#define _globalvars_H_

#include "os.h"

//OS gloabls
#define EMPTY -1
//int abort = 1; *********

//For Semaphores
typedef struct semaphores {
    int s;
    int n;
    int sempid[];
} sem;

sem semarray[MAXSEM];
extern int semcounter;

//For FIFOs
typedef struct fifonode {
	struct fifonode* next;
	struct fifonode* previous;
	int flag; // read == 0 // unread == 1 
	int data;
} node;

node fifoarray[MAXFIFO];
extern int fifocounter;







#endif /* _globalvars_H_ */  
