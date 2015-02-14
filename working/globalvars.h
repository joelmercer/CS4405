#ifndef _globalvars_H_  
#define _globalvars_H_

#include "os.h"

//OS gloabls
//#define NULL 0

//For Semaphores
typedef struct semaphores {
    int s;
    int n;
    int sempid[];
} sem;

//For FIFOs
typedef struct fifonode {
	void* next;
	void* previous;
	int flag; // read == 0 // unread == 1 
	int data;
} node;

node fifoarray[MAXFIFO];
extern int fifocounter;
sem semarray[MAXSEM];
extern int semcounter;

//For FIFOs







#endif /* _globalvars_H_ */  
