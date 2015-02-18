#ifndef _globalvars_H_  
#define _globalvars_H_

#include "os.h"

//Function declare
void OS_Interrupt_Init();
void Interrupt_Handler(void);
void Context_Switch();
void void OS_Set_Timer(int timer);

//OS gloabls
#define EMPTY -1
extern int abort = 1;

//
extern int SPORADIC[MAXPROCESS];
extern int semcounter;

//For Semaphores
typedef struct semaphores {
    int s;
    int n;
    int sempid[];
} sem;

sem semarray[MAXSEM];
extern int semcounter;

//OS_Create
typedef struct createprocess {
    int pid;
    void * function;
    int arg;
    unsigned int level;
    unsigned int n;
} process;

process processarray[MAXPROCESS];
extern int processcounter;

//For FIFOs
typedef struct fifonode {
	struct fifonode* next;
	struct fifonode* previous;
	int flag; // read == 0 // unread == 1 
	int data;
} node;

node fifoarray[MAXFIFO];
extern int fifocounter;


//Memory Locations
#define INTERVAL_TIMER_BASE 0x10002000

//Interrupts
#define NIOS2_WRITE_STATUS(src) do { __builtin_wrctl(0, src); } while (0)
#define NIOS2_READ_IPENDING(dest) do { dest = __builtin_rdctl(4); } while (0)



#endif /* _globalvars_H_ */  
