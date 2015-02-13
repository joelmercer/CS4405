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

sem semarray[MAXSEM];
extern int semcounter;

//For FIFOs







#endif /* _globalvars_H_ */  
