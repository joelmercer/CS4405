#ifndef _globalvars_H_  
#define _globalvars_H_

#include "os.h"


//Function declare
void Context_Switch(int pid);
void OS_Interrupt_Handler(int pid);
void OS_Start();
void OS_AddTo_Schedule(int pid, int level);
void OS_Init();
void OS_Abort();
PID OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n);
void OS_Terminate(void);
void OS_Yield(void);
int OS_GetParam(void);
int OS_GetPID(void);
void OS_InitSem(int s, int n);
void OS_Wait(int s);
void OS_Signal(int s);
FIFO OS_InitFiFo();
void OS_Write(FIFO f, int val);
BOOL OS_Read(FIFO f, int *val);
int main();


//OS gloabls
#define EMPTY -1
extern int crash;
extern int processcounter; 
extern int sporadic[MAXPROCESS];
extern int terminate;
extern int crash;
extern int semcounter;
extern int fifopidarray[MAXFIFO][MAXFIFO];


//For future Timer
//extern volatile int *timebase; //interval timer base address
//extern int timeq; // 1/(50 MHz) × (0x260000) = ~50 msec

//For Schedule
//extern int pppcounter;
//extern int MAXDEVICE;


//For Semaphores
typedef struct semaphores {
    int s;
    int n;
    int sempid[MAXSEM];
} sem;

extern sem semarray[MAXSEM];

//OS_Create
typedef struct createprocess {
    int pid;
    void * function;
    int arg;
    unsigned int level;
    unsigned int n;
} process;

extern process processarray[MAXPROCESS];

//For FIFOs
typedef struct fifonode {
	struct fifonode* next;
	struct fifonode* previous;
	int flag; // read == 0 // unread == 1 
	int data;
} node;

extern node fifoarray[MAXFIFO];




//Memory Locations

//System Macro
#define NIOS2_WRITE_STATUS(src) do { __builtin_wrctl(0, src); } while (0)
#define NIOS2_READ_IPENDING(dest) do { dest = __builtin_rdctl(4); } while (0)



#endif /* _globalvars_H_ */  
