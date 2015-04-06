#ifndef _globalvars_H_  
#define _globalvars_H_

//We include os.h so it doesn't have to be done everytime.
#include "os.h"

//Function declare
void Context_Switch(int pid);
void OS_Interrupt_Handler(int pid);
void OS_AddTo_Schedule(int pid, int level, int n);
int OS_GetPID(void);
MEMORY OS_KMalloc(int val);


//OS gloabls
#define EMPTY -1
#define startmem 0x005FDC00

extern volatile int * interval_timer_ptr;
extern int crash;
extern int processcounter; 
extern int sporadic[MAXPROCESS];
extern int terminate;
extern int semcounter;
extern int fifocounter;
extern int fifopidarray[MAXFIFO];
extern int sporadiccounter;
extern int workingpid;
extern int stackheap[2][16];
extern int oshp;
extern int once;
extern int device[];
extern int devicelen;
extern int devicemax[];
extern int devicetimer;
extern int currentdevicetimer;

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
	void (*function)(void);
    //void * function;
    int arg;
    unsigned int level;
    unsigned int n;
    int sp;
    int hp;
} process;

extern process processarray[MAXPROCESS];

//For FIFOs
typedef struct fifonode {
	int head; // head == 1; not head == 0
	int tail; //tail == 1; not tail == 0
	int flag; // read == 0; unread == 1 
	int data;
	int next;
	int previous;
} node;

extern node fifoarray[MAXFIFO][FIFOSIZE];


//Memory Locations

//System Macro
#define NIOS2_READ_STATUS(dest) \
	do { dest = __builtin_rdctl(0); } while (0)

#define NIOS2_WRITE_STATUS(src) \
	do { __builtin_wrctl(0, src); } while (0)

#define NIOS2_READ_ESTATUS(dest) \
	do { dest = __builtin_rdctl(1); } while (0)

#define NIOS2_READ_BSTATUS(dest) \
	do { dest = __builtin_rdctl(2); } while (0)

#define NIOS2_READ_IENABLE(dest) \
	do { dest = __builtin_rdctl(3); } while (0)

#define NIOS2_WRITE_IENABLE(src) \
	do { __builtin_wrctl(3, src); } while (0)

#define NIOS2_READ_IPENDING(dest) \
	do { dest = __builtin_rdctl(4); } while (0)

#define NIOS2_READ_CPUID(dest) \
	do { dest = __builtin_rdctl(5); } while (0)


#endif /* _globalvars_H_ */  
