
#include "os.h"

#ifndef NULL
#define NULL 0
#endif

#define TIME_QUANTUM 10 
#define SYS_CALL_YIELD 1
#define SYS_CALL_TERMINATE 2
#define SYS_CALL_START 3
#define SYS_CALL_HALT 0
volatile int *LEDR_ptr = (int*) 0x10000000;
volatile int *LEDG_ptr = (int*) 0x10000010;
volatile int *CLK_ptr = (int*) 0x10002000;
volatile int *JTAG_UART_ptr = (int *) 0x10001000;
#define START   0
#define RUNNING 1
#define READY   2
#define WAITING 3
#define TERM    4
#define ZOMBIE  5
#define EMPTY   6

/*
typedef struct fifo_t{
	unsigned int fifo[FIFOSIZE+1];
}FIFO;
*/

typedef struct process_t {
  PID pid;
  unsigned int level;
  unsigned int n;
  unsigned int state;
  int workspace[WORKSPACE];
  int arg;
  void (*f)(void);
  int registers[29]; // r1 - r26, r28 - r31
  struct process_t *next;
} PROCESS;

int tester1, tester2;

typedef struct sem_sleepQueue_t {
  PID pid;
  struct sem_sleepQueue_t *next;
} SEM_SLEEPQUEUE;

int fifos[MAXFIFO][FIFOSIZE + 1];
int PPP[MAXPROCESS];
int PPPMax[MAXPROCESS];
int PPPLen = MAXPROCESS;
PROCESS processes[MAXPROCESS];
PROCESS *schedule = &processes[0];
BOOL is_halting = 0;
int semaphores[MAXSEM][2];
SEM_SLEEPQUEUE sleepQueue[MAXSEM][MAXPROCESS - 1];


typedef struct HEAP_TYPE
{	
        int free[200]; //200 useable bytes 
} HEAP;

HEAP *BLOCKHEAD;


void jtag_debug(char *msg) {
  int i, control;
  for (i = 0; msg[i] != 0; i++) {
    control = *(JTAG_UART_ptr + 1);                 // read the JTAG_UART control register
    if (control & 0xFFFF0000)                                       // if space, then echo character, else ignore
      *(JTAG_UART_ptr) = msg[i];
  }
}

void OS_Init() {
  int i;
    //Setup clock
  // 1 sec
  int counter = 0x02FAF080;
  // 1/100 sec (jiffy)
  //int counter = 0x0007A120;
  // 33 msec
  //int counter = 0x190000;
  *(CLK_ptr + 0x2) = (counter & 0xFFFF);
  *(CLK_ptr + 0x3) = (counter >> 16) & 0xFFFF;
  *(CLK_ptr + 1)   = 0x7;

  for(i = 0; i < MAXPROCESS - 1; i++){
    processes[i].pid = IDLE;
    processes[i].state = EMPTY;
    processes[i].next = &processes[i + 1];
    processes[i].level = i; 
    processes[i].registers[30] = (int)&OS_Start;
    }

  processes[MAXPROCESS - 1].pid = IDLE;
  processes[MAXPROCESS - 1].next = NULL;
  int* workspacePointer = &schedule->workspace[0];
  asm ("ldw sp, %0" : : "m" ((workspacePointer)));
  schedule->state=RUNNING;
  //Enable timer interrupts
 NIOS2_WRITE_IENABLE(1);
  //Enable interrupts
  NIOS2_WRITE_STATUS(1);


}

int main() {
  OS_Init();
 // OS_Create(&led_toggle_program, 0, SPORADIC, 0);

  //OS_Create(&led_toggle_program, 1, SPORADIC, 0);
  //OS_Start();
}
