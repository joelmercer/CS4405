#include "globalvars.h"

/* function prototypes */
void main(void);
void interrupt_handler(void);
void interval_timer_isr(void);
void pushbutton_ISR(void);




/* global variables */
extern int	key_pressed;

/* The assembly language code below handles CPU reset processing */
void the_reset (void) __attribute__ ((section (".reset")));

void the_reset (void) {
asm (".set		noat");					// Magic, for the C compiler
asm (".set		nobreak");				// Magic, for the C compiler
asm ("movia		r2, main");				// Call the C language main program
asm ("jmp		r2"); 
}

void the_exception (void) __attribute__ ((section (".exceptions")));

void the_exception (void) {
	NIOS2_WRITE_STATUS( 0 ); //disable interrupts
	printf("THE TIMER WENT OFF\n");

	int pid = workingpid;
	
	asm ( "mov		%0, et":"=r"(processarray[pid].regs[24]));
	asm ( "rdctl	et, ctl4" );
	asm ( "beq		et, r0, SKIP_EA_DEC" );	        
	asm ( "subi		ea, ea, 4" );				
	
	asm ( "SKIP_EA_DEC:" );
	asm (	"mov	%0, r1":"=r"(processarray[pid].regs[1]));
	asm (	"mov	%0, r2":"=r"(processarray[pid].regs[2]));	
	asm (	"mov	%0, r3":"=r"(processarray[pid].regs[3]));	
	asm (	"mov	%0, r4":"=r"(processarray[pid].regs[4]));
	asm (	"mov	%0, r5":"=r"(processarray[pid].regs[5]));	
	asm (	"mov	%0, r6":"=r"(processarray[pid].regs[6]));	
	asm (	"mov	%0, r7":"=r"(processarray[pid].regs[7]));	
	asm (	"mov	%0, r8":"=r"(processarray[pid].regs[8]));
	asm (	"mov	%0, r9":"=r"(processarray[pid].regs[9]));	
	asm (	"mov	%0, r10":"=r"(processarray[pid].regs[10]));	
	asm (	"mov	%0, r11":"=r"(processarray[pid].regs[11]));	
	asm (	"mov	%0, r12":"=r"(processarray[pid].regs[12]));	
	asm (	"mov	%0, r13":"=r"(processarray[pid].regs[13]));	
	asm (	"mov	%0, r14":"=r"(processarray[pid].regs[14]));	
	asm (	"mov	%0, r15":"=r"(processarray[pid].regs[15]));	
	asm (	"mov	%0, r16":"=r"(processarray[pid].regs[16]));		
	asm (	"mov	%0, r17":"=r"(processarray[pid].regs[17]));	
	asm (	"mov	%0, r18":"=r"(processarray[pid].regs[18]));	
	asm (	"mov	%0, r19":"=r"(processarray[pid].regs[19]));	
	asm (	"mov	%0, r20":"=r"(processarray[pid].regs[20]));
	asm (	"mov	%0, r21":"=r"(processarray[pid].regs[21]));
	asm (	"mov	%0, r22":"=r"(processarray[pid].regs[22]));
	asm (	"mov	%0, r23":"=r"(processarray[pid].regs[23]));	
	asm (	"mov	%0, r25":"=r"(processarray[pid].regs[25]));		
	asm (	"mov	%0, r26":"=r"(processarray[pid].regs[26]));
	asm (	"mov	%0, r28":"=r"(processarray[pid].regs[28]));	
	asm (	"mov	%0, r29":"=r"(processarray[pid].regs[29]));	
	asm (	"mov	%0, r30":"=r"(processarray[pid].regs[30]));	
	asm (	"mov	%0, r31":"=r"(processarray[pid].regs[31]));				
	asm (	"addi	fp,  sp, 128" );	


	OS_Load_Scheduler();

}

