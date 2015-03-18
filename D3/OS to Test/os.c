/* 1. Initialization
*  2. FIFO
*  3. Exception 
*  4. Scheduler 
*  5. Process scheduling 
*  6. Process management
*  7. Sys calls
*  8. Interrupt handler
*  9. Memory Manage
*  10. Main
*/
/****************************************************************************
********************** 1. Initialization	*****************************
*****************************************************************************/

#include <nios2.h>
#include <sys/alt_stack.h>
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

/**************************************************************************************
************************************ End Initialization *******************************
**************************************************************************************/
/**************************************************************************************
******************************* 2. FIFO	***********************************************
**************************************************************************************/
/*
//Initializes a new FIFO and returns a FIFO descriptor. returns INVALIDFIFO otherwise
FIFO OS_InitFiFO()
{       
        FIFO descriptor;
        int i, j, found;        

        for(i=0; i<MAXFIFO && found ==0; i++)
        {
                found = 1;
                for(j=0; j<FIFOSIZE + 1; j++)
                {       
                        if(fifos[i][j] != NULL)
                        {
                                found = 0;
                                break;
                        }
                }
        }
        descriptor.fifo = &fifos[i-1][0];
        return descriptor;      
}

void OS_Write (FIFO f, unsigned int val)
{
        int i;

}
*/
/*********************************************************************************
********************* END FIFO ***************************************************
*********************************************************************************/
/*****************************************************************
******************* 3. Semaphore primitives **********************
*****************************************************************/
void OS_InitSem(int s, int n){
  int i;
  if (s < 0 || s > MAXSEM || semaphores[s][0] != -1) {
    //Invalid semaphore choice, panic
    OS_Abort();
  }

  semaphores[s][0] = n;
  semaphores[s][1] = n;
  for (i = 0; i < n - 1; i++) {
    sleepQueue[s][i].pid = -1;
    sleepQueue[s][i].next = &sleepQueue[s][i + 1];
  }
  sleepQueue[s][n - 1].pid = -1;
  sleepQueue[s][n - 1].next = NULL;
}  


/**************************************************************************************
************************************End Semaphore Primitives  ************************
**************************************************************************************/
/**************************************************************************************
********************************** 4. Exception     ***********************************
***************************************************************************************/

void the_exception () __attribute__ ((section (".exceptions")));
void the_exception () {
  asm ( ".set		noat" );						// Magic, for the C compiler
  asm ( ".set		nobreak" );					// Magic, for the C compiler
  asm ( "subi		sp, sp, 128" );
  asm ( "stw		et, %0" : "=m" (schedule->registers[23])); 
  asm ( "wrctl          ctl0, r0"); // Disable Interrupts
  asm ( "rdctl	        et, ctl4" );
  asm ( "beq		et, r0, SKIP_EA_DEC" );	 // Interrupt is not external
  asm ( "subi		ea, ea, 4" );				/* Must decrement ea by one instruction
								 * for external interupts, so that the
								 * interrupted instruction will be run */ 
  asm ( "SKIP_EA_DEC:" );
  asm (	"stw	r1,  %0" : "=m" (schedule->registers[0]));					// Save all registers
  asm (	"stw	r2,  %0" : "=m" (schedule->registers[1]));
  asm (	"stw	r3,  %0" : "=m" (schedule->registers[2]));
  asm (	"stw	r4,  %0" : "=m" (schedule->registers[3]));
  asm (	"stw	r5,  %0" : "=m" (schedule->registers[4]));
  asm (	"stw	r6,  %0" : "=m" (schedule->registers[5]));
  asm (	"stw	r7,  %0" : "=m" (schedule->registers[6]));
  asm (	"stw	r8,  %0" : "=m" (schedule->registers[7]));
  asm (	"stw	r9,  %0" : "=m" (schedule->registers[8]));
  asm (	"stw	r10, %0" : "=m" (schedule->registers[9]));
  asm (	"stw	r11, %0" : "=m" (schedule->registers[10]));
  asm (	"stw	r12, %0" : "=m" (schedule->registers[11]));
  asm (	"stw	r13, %0" : "=m" (schedule->registers[12]));
  asm (	"stw	r14, %0" : "=m" (schedule->registers[13]));
  asm (	"stw	r15, %0" : "=m" (schedule->registers[14]));
  asm (	"stw	r16, %0" : "=m" (schedule->registers[15]));
  asm (	"stw	r17, %0" : "=m" (schedule->registers[16]));
  asm (	"stw	r18, %0" : "=m" (schedule->registers[17]));
  asm (	"stw	r19, %0" : "=m" (schedule->registers[18]));
  asm (	"stw	r20, %0" : "=m" (schedule->registers[19]));
  asm (	"stw	r21, %0" : "=m" (schedule->registers[20]));
  asm (	"stw	r22, %0" : "=m" (schedule->registers[21]));
  asm (	"stw	r23, %0" : "=m" (schedule->registers[22]));
  asm (	"stw	r25, %0" : "=m" (schedule->registers[24]));		// r25 = bt (skip r24 = et, because it is saved above)
  asm (	"stw	r26, %0" : "=m" (schedule->registers[25]));		// r26 = gp
  asm (	"stw	r28, %0" : "=m" (schedule->registers[27]));		// r28 = fp
  asm (	"stw	r29, %0" : "=m" (schedule->registers[28]));				// r29 = ea 
  asm (	"stw	r31, %0" : "=m" (schedule->registers[30]));				// r31 = ra
  asm (	"addi	fp,  sp, 128" );
  asm ("call	interrupt_handler");  
  asm (	"ldw	r1,  %0" : : "m"  (schedule->registers[0]));					// Restore all registers
  asm (	"ldw	r2,  %0" : : "m"  (schedule->registers[1]));
  asm (	"ldw	r3,  %0" : : "m"  (schedule->registers[2]));
  asm (	"ldw	r4,  %0" : : "m"  (schedule->registers[3]));
  asm (	"ldw	r5,  %0" : : "m"  (schedule->registers[4]));
  asm (	"ldw	r6,  %0" : : "m"  (schedule->registers[5]));
  asm (	"ldw	r7,  %0" : : "m"  (schedule->registers[6]));
  asm (	"ldw	r8,  %0" : : "m"  (schedule->registers[7]));
  asm (	"ldw	r9,  %0" : : "m"  (schedule->registers[8]));
  asm (	"ldw	r10, %0" : : "m"  (schedule->registers[9]));
  asm (	"ldw	r11, %0" : : "m"  (schedule->registers[10]));
  asm (	"ldw	r12, %0" : : "m"  (schedule->registers[11]));
  asm (	"ldw	r13, %0" : : "m"  (schedule->registers[12]));
  asm (	"ldw	r14, %0" : : "m"  (schedule->registers[13]));
  asm(	"ldw	r15, %0" : : "m"  (schedule->registers[14]));
  asm (	"ldw	r16, %0" : : "m"  (schedule->registers[15]));
  asm (	"ldw	r17, %0" : : "m"  (schedule->registers[16]));
  asm (	"ldw	r18, %0" : : "m"  (schedule->registers[17]));
  asm (	"ldw	r19, %0" : : "m"  (schedule->registers[18]));
  asm (	"ldw	r20, %0" : : "m"  (schedule->registers[19]));
  asm (	"ldw	r21, %0" : : "m"  (schedule->registers[20]));
  asm (	"ldw	r22, %0" : : "m"  (schedule->registers[21]));
  asm (	"ldw	r23, %0" : : "m"  (schedule->registers[22]));
  asm (	"ldw	r24, %0" : : "m"  (schedule->registers[23]));             //r24 = et
  asm (	"ldw	r25, %0" : : "m"  (schedule->registers[24]));		// r25 = bt
  asm (	"ldw	r26, %0" : : "m"  (schedule->registers[25]));		// r26 = gp
  asm (	"ldw	r28, %0" : : "m"  (schedule->registers[27]));		// r28 = fp
  asm (	"ldw	r29, %0" : : "m"  (schedule->registers[28]));				// r29 = ea
  asm (	"ldw	r31, %0" : : "m"  (schedule->registers[30]));				// r31 = ra 
  asm (	"addi	sp,  sp, 128" );
  asm ( "movi           r1, 1"); //
  asm ( "wrctl          ctl0, r1"); // Enable Interrupts
  asm (	"eret" );
}
/************************************************************************
*******************End Exception ****************************************
************************************************************************/
/************************************************************************
********************* 5. Scheduler **************************************
************************************************************************/

void process_start() {
	 if (schedule->state != START){
		OS_Abort(); // What did you even do to get here
  	}
	schedule->state = RUNNING;
 	NIOS2_WRITE_STATUS(0);
	schedule->f();
	OS_Terminate();
	return;
}
//Comments to ensuse
int cur_tqs = 0;
void do_scheduling() {  
	//Round Robin
	PROCESS *current = schedule, *head = schedule, *tail = schedule;
	char msg[32];
	cur_tqs = 0; 

        for(;tail->next!=NULL;tail=tail->next);

	/* Copying workspace to next processes
	 * Pointing the SP at the next processes workspace with the same relatively distance from the start */
	if (tail != head) {
		int length = 0, i, spNew, *workspacePointer;
		workspacePointer = &schedule->workspace[0];
		asm("ldw r10, %0" : : "m" (workspacePointer));        //r10 pointer to workspace
		asm("mov r14, sp");				            //r14 pointer to sp
		asm("sub r12, r14, r10");			            //r12 length between workspace and sp
		asm("stw r12, %0" : "=m" (length));		  	    //r12 into length	
		//asm("ldw r10, %0" : : "m" (length));		     	    //length into r10
                workspacePointer = &schedule->next->workspace[0];
		asm("ldw r11, %0" : : "m" (workspacePointer));  //next->workspace into r11		
	        asm("sub r14, r11, r12");				    //r12 + r11 into r14
		asm("mov sp, r14");					    //r14 into sp

		for(i=0; i<length; i++)
			schedule->next->workspace[i] = schedule->workspace[i];
		
		tail->next = head;   
		schedule = current->next;
		head->state=READY;
		head->next=NULL;
  	} 
	else 
		schedule = head;
 	

	for (head=schedule; head != NULL; head = head->next)
		if (head->state == READY || head->state == START)
      			break;

	toggle_led(schedule->state);

/*
	if (schedule->state == START) {
		toggle_led(14);
		process_start();
  	}
*/

	schedule->state = RUNNING;	
	toggle_led(schedule->level);
	return;
}

void scheduler_timer() {
	cur_tqs++;
        int *stackPointer, *reg31;
	if (cur_tqs == TIME_QUANTUM) {
		do_scheduling();
	}
return;
}
void scheduler_term() {}

/********************************************************************
********************* End Scheduler *********************************
********************************************************************/
/********************************************************************
********************* 6. Led Toggle *********************************
********************************************************************/
void led_toggle_program() {
	int i;
	for(i=0; i<10; i++)
		toggle_led(i);
	return;
}

void toggle_led(int led_num) {
  (*LEDR_ptr) ^= (1 << led_num); 
}

void toggle_ledg(int led_num) {
  (*LEDG_ptr) ^= (1 << led_num); 
}

/**********************************************************************
*********************** End Led Toggle*********************************
**********************************************************************/
/**********************************************************************
************************ 7. Process Management ************************
**********************************************************************/
PID OS_GetPID() {
  return schedule->pid;
}

PID OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n) {
  int i;
  PROCESS *process;
  for (process = &processes[0]; process != NULL; process = process->next) {
    if (process->state == EMPTY) {
      break;
    }
  }

  if (process == NULL) {
    //Could not find a slot for the process 
	return INVALIDPID;
  }

  for (i = 0; i < MAXPROCESS; i++) {
    if (process == &processes[i]){
      process->pid = i;
      break;
    }
  }
  process->f = f;
  process->arg = arg;
  process->level = level;
  process->n = n;
  process->state=START;
	 return i;
}

void OS_Terminate(void) {
  OS_SysCall(SYS_CALL_TERMINATE);
}

void _OS_Terminate(void) {
  PROCESS *current = schedule;
  PROCESS *tmp;
  
  schedule = current->next;

  current->pid = IDLE;
  current->f;
  current->state = EMPTY;
  for (tmp = current; tmp->next != NULL; tmp = tmp->next){
  }

  tmp->next = current;
  current->next = NULL;
  
}

void OS_Yield(void) {
  OS_SysCall(SYS_CALL_YIELD);
}

void _OS_Yield() {
  PROCESS *current = schedule;
  PROCESS *tmp;
  schedule = current->next;

  current->f;
  for (tmp = current; tmp->next->pid != IDLE; tmp = tmp->next){
  }
  current->next = tmp->next;
  tmp->next = current;
}

int  OS_GetParam(void) {
  return schedule->arg;
}  


void OS_Wait(int s) {
  int i, j;
  SEM_SLEEPQUEUE *tmp;
  while (semaphores[s][0] != semaphores[s][1]) {
    //Wait
    for (i = 0; i < semaphores[s][0]; i++){
      if (sleepQueue[s][i].pid == OS_GetPID()){
	break;
      }
    }
    if (sleepQueue[s][i].pid != OS_GetPID()) {
      for (i = 0; i < semaphores[s][0]; i++){
	if (sleepQueue[s][i].pid == -1){
	  sleepQueue[s][i].pid = OS_GetPID();
	  OS_Yield();
	  break;
	}
      }      
    }
    if (sleepQueue[s][i].pid != OS_GetPID()) {
      //Too many processes trying to access semaphore, panic
      OS_Abort();
    }
  }

  sleepQueue[s][i].pid = -1;
  for (j = 0; j < semaphores[s][0]; j++) {
    if (&sleepQueue[s][i] == sleepQueue[s][j].next) {
      sleepQueue[s][j].next = sleepQueue[s][i].next;
      for (tmp = &sleepQueue[s][i]; tmp->next != NULL; tmp = tmp->next );
      tmp->next = &sleepQueue[s][i];
      sleepQueue[s][i].next = NULL;
    }
  }  
  semaphores[s][1]--;
}

void OS_Signal(int s) {
}

/*********************************************************************************************
*******************************End Process Management ****************************************
*********************************************************************************************/
/****************************************************************************************
*************************** 8. Sys Calls ***************************************************
****************************************************************************************/
void timer_isr() {
	*(CLK_ptr) = 0;
	if(processes[MAXPROCESS - 1].next == NULL)
		scheduler_timer();
	return;
}

int sys_call;
void OS_SysCall(int call) {
  sys_call = call;
   the_exception();
}

void OS_Start() {
  while (!is_halting);
}

void OS_Abort() {
  is_halting = 1;
}

void handle_sys_call() {
  switch(sys_call) {
  case SYS_CALL_YIELD:
    _OS_Yield();
    break;
  case SYS_CALL_TERMINATE:
    break;
  case SYS_CALL_START:
    break;
  case SYS_CALL_HALT:
    break;
  }
  return;
}

void intToStr(int n, char *str) {
  int tmp = n, i=0;
  if (tmp < 0) {
    str[i++] = '-';
    tmp *= -1;
  }
  for (; tmp != 0; tmp /= 10) {
    str[i++] = '0' + tmp % 10;
  }
  str[i++] = '\n';
  str[i] = '\0';
  return;
}
/***************************************************************************
***********************End Sys Calls ***************************************
***************************************************************************/
/****************************************************************************
**********************8. Interrupt handler**************************************
****************************************************************************/
void interrupt_handler() {
  //TODO pre-empt (Change the value of schedule)
  //TODO Handle interrupts
  int ipending;
 NIOS2_READ_IPENDING(ipending);
  if (ipending == 0) {  
	handle_sys_call();
  } else if (ipending & 1) { //Timer
    timer_isr(); 	
  } 
  return;
}
/*****************************************************************************
**********************End Interrupt Handler **********************************
*****************************************************************************/
/*****************************************************************************
********************** 9. Memory Manage **************************************
*****************************************************************************/
/*MEMORY OS_Malloc (int val)
{
        MEMORY *currentBlock = BLOCKHEAD;
        int allocated = 0;
        while(allocated == 0)
        {
                if (currentBlock.free == 1 && currentBlock.size < val)
                {
                        currentBlock.size = val + 2048 - val % 2048;
                        currentBlock.CRITICAL_SECTION;
                        currentBlock.free = 0;
                        allocated = 1;
                }

                else   
                        currentBlock = currentBlock.next;
        }
        return currentBlock;
} */     
/****************************************************************************
*********************** END MEMORY MANAGE ************************************
****************************************************************************/
/**************************************************************************************
************************************ 10. Main *****************************************
**************************************************************************************/
int main() {
  OS_Init();
  OS_Create(&led_toggle_program, 0, SPORADIC, 0);

  //OS_Create(&led_toggle_program, 1, SPORADIC, 0);
  OS_Start();
}
/**************************************************************************************
************************************ End Main *****************************************
**************************************************************************************/
