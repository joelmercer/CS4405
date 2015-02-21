#ifndef _globalvars_H_  
#define _globalvars_H_

#include "os.h"


//Function declare
void Interrupt_Handler(void);
void Context_Switch();
void OS_Set_Timer(int timer);

//OS gloabls
#define EMPTY -1
extern int crash;

//For Timer
extern volatile int *timebase; //interval timer base address
extern int timeq; // 1/(50 MHz) × (0x260000) = ~50 msec

//For Schedule
extern int pppcounter;
extern int sporadic[MAXPROCESS];
extern int sporadiccounter;
extern int MAXDEVICE;

//For Semaphores
typedef struct semaphores {
    int s;
    int n;
    int sempid[MAXSEM];
} sem;

sem semarray[MAXSEM];

//OS_Create
typedef struct createprocess {
    int pid;
    void * function;
    int arg;
    unsigned int level;
    unsigned int n;
} process;

process processarray[MAXPROCESS];

//For FIFOs
typedef struct fifonode {
	struct fifonode* next;
	struct fifonode* previous;
	int flag; // read == 0 // unread == 1 
	int data;
} node;

node fifoarray[MAXFIFO];




//Memory Locations

//System Macro
#define NIOS2_WRITE_STATUS(src) do { __builtin_wrctl(0, src); } while (0)
#define NIOS2_READ_IPENDING(dest) do { dest = __builtin_rdctl(4); } while (0)



#endif /* _globalvars_H_ */  
