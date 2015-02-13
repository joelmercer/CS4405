#ifndef _globalvars_H_  
#define _globalvars_H_

//For Semaphores
extern struct sem {
    int s;
    int n;
    int sempid[n];
};
extern sem semarray[16];
extern int semcounter;

//For FIFOs







#endif /* _globalvars_H_ */  