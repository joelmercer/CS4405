#include "globalvars.h"

//schedule saves
//calls function k
//k checks if the process has been called before
//if it hasn't straight calls it (changes bit)
//if is has been called sets timer to 0
//timer goes off and call excpection
//sets timer to what it should be
//Checks if the flip bit is 0-load program 1-load schedule
//if 0 - loads regs of the working pid
//if 1 - loads regs of start
//runs that program
//timer goes off, goes to the excepection

//Save Schedule
//Load program
//run program
//save program
//load schedule

void the_reset (void) __attribute__ ((section (".reset")));

void the_reset (void) {

asm (".set		noat");					// Magic, for the C compiler
asm (".set		nobreak");				// Magic, for the C compiler
//asm ("movia		r2, main");				// Call the C language main program
//asm ("jmp		r2"); 

}

void the_exception (void) __attribute__ ((section (".exceptions")));

void the_exception (void)  {
*(interval_timer_ptr) = 0; 

asm ( ".set		noat" );						// Magic, for the C compiler
asm ( ".set		nobreak" );					// Magic, for the C compiler
asm ( "subi		sp, sp, 128" );
asm ( "stw		et, 96(sp)" );
asm ( "rdctl	et, ctl4" );

asm (	"stw	r1,  4(sp)" );					// Save all registers 
asm (	"stw	r2,  8(sp)" );
asm (	"stw	r3,  12(sp)" );
asm (	"stw	r4,  16(sp)" );
asm (	"stw	r5,  20(sp)" );
asm (	"stw	r6,  24(sp)" );
asm (	"stw	r7,  28(sp)" );
asm (	"stw	r8,  32(sp)" );
asm (	"stw	r9,  36(sp)" );
asm (	"stw	r10, 40(sp)" );
asm (	"stw	r11, 44(sp)" );
asm (	"stw	r12, 48(sp)" );
asm (	"stw	r13, 52(sp)" );
asm (	"stw	r14, 56(sp)" );
asm (	"stw	r15, 60(sp)" );
asm (	"stw	r16, 64(sp)" );
asm (	"stw	r17, 68(sp)" );
asm (	"stw	r18, 72(sp)" );
asm (	"stw	r19, 76(sp)" );
asm (	"stw	r20, 80(sp)" );
asm (	"stw	r21, 84(sp)" );
asm (	"stw	r22, 88(sp)" );
asm (	"stw	r23, 92(sp)" );
asm (	"stw	r25, 100(sp)" );				// r25 = bt (skip r24 = et, because it is saved above)
asm (	"stw	r26, 104(sp)" );				// r26 = gp
// skip r27 because it is sp, and there is no point in saving this
asm (	"stw	r28, 112(sp)" );				// r28 = fp
asm (	"stw	r29, 116(sp)" );				// r29 = ea
asm (	"stw	r30, 120(sp)" );				// r30 = ba
asm (	"stw	r31, 124(sp)" );				// r31 = ra
asm (	"addi	fp,  sp, 128" );

asm (	"mov	%0, r27":"=r"(processarray[savepid].sp));
//int ea, ra;
//asm (	"mov	%0, r29":"=r"(ea));
//asm (	"mov	%0, r31":"=r"(ra));

printf("TIMER WENT OFF, savepid: %d\n", savepid);

if(savepid!=16) {
printf("The saved SP: 0x%x\n", processarray[savepid].sp);
//printf("The saved ea: 0x%x\n", ea);
//printf("The saved ra: 0x%x\n", ra);
	asm (	"mov	r27, %0" ::"r"(processarray[16].sp));
	workingpid = 16;
}

printf("Workingpid: %d\n", workingpid);
printf("State: %d\n", processarray[workingpid].state);

yeild:

if(processarray[workingpid].state == 1 && workingpid == 16) {
	processarray[workingpid].state = 2;
	printf("OS_Start first time\n");
	OS_Start();
} else if (processarray[workingpid].state == 2 && workingpid == 16) {
	printf("Load schedule\n");
	OS_Load_Scheduler();
} else if(processarray[workingpid].state == 1) {
		printf("Call Program first time\n");
		savepid = workingpid;
		processarray[workingpid].state = 2;
		OS_First_Call();
	} else if (processarray[workingpid].state == 2) {
		printf("Call Program second time\n");
		savepid = workingpid;
		OS_Load_Program();
	} else  {
		
		workingpid = 16;
		goto yeild;
	}

}

void OS_Load_Scheduler() {
	
		*(interval_timer_ptr) = 0; 
	*(interval_timer_ptr + 1) = 0; 
	
	asm (	"mov	r27, %0" ::"r"(processarray[16].sp));
	//printf("The loaded SP: 0x%x\n", processarray[workingpid].regs[27]);
	asm (	"ldw	r28, 112(sp)" );				// r28 = fp
	
asm (	"ldw	r24, 96(sp)" );

	asm (	"ldw	r1,  4(sp)" );					// Restore all registers
asm (	"ldw	r2,  8(sp)" );
asm (	"ldw	r3,  12(sp)" );
asm (	"ldw	r4,  16(sp)" );
asm (	"ldw	r5,  20(sp)" );
asm (	"ldw	r6,  24(sp)" );
asm (	"ldw	r7,  28(sp)" );
asm (	"ldw	r8,  32(sp)" );
asm (	"ldw	r9,  36(sp)" );
asm (	"ldw	r10, 40(sp)" );
asm (	"ldw	r11, 44(sp)" );
asm (	"ldw	r12, 48(sp)" );
asm (	"ldw	r13, 52(sp)" );
asm (	"ldw	r14, 56(sp)" );
asm (	"ldw	r15, 60(sp)" );
asm (	"ldw	r16, 64(sp)" );
asm (	"ldw	r17, 68(sp)" );
asm (	"ldw	r18, 72(sp)" );
asm (	"ldw	r19, 76(sp)" );
asm (	"ldw	r20, 80(sp)" );
asm (	"ldw	r21, 84(sp)" );
asm (	"ldw	r22, 88(sp)" );
asm (	"ldw	r23, 92(sp)" );
asm (	"ldw	r25, 100(sp)" );				// r25 = bt
asm (	"ldw	r26, 104(sp)" );				// r26 = gp
// skip r27 because it is sp, and we did not save this on the stack

asm (	"ldw	r29, 116(sp)" );
//asm (	"ldw	r31, 116(sp)" );				// r29 = ea
asm (	"ldw	r30, 120(sp)" );				// r30 = ba
asm (	"ldw	r31, 124(sp)" );				// r31 = ra

asm (	"addi	sp,  sp, 128" );


	
	asm (	"ret" );
	
}

void OS_Load_Program() {
	
printf("LOAD PROGRAM: %d\n", workingpid);

OS_StartTimer(0xFFFFFF);

	asm (	"mov	r27, %0" ::"r"(processarray[workingpid].sp));
	//printf("The loaded SP: 0x%x\n", processarray[workingpid].regs[27]);
	asm (	"ldw	r28, 112(sp)" );				// r28 = fp
	
asm (	"ldw	r24, 96(sp)" );

	asm (	"ldw	r1,  4(sp)" );					// Restore all registers
asm (	"ldw	r2,  8(sp)" );
asm (	"ldw	r3,  12(sp)" );
asm (	"ldw	r4,  16(sp)" );
asm (	"ldw	r5,  20(sp)" );
asm (	"ldw	r6,  24(sp)" );
asm (	"ldw	r7,  28(sp)" );
asm (	"ldw	r8,  32(sp)" );
asm (	"ldw	r9,  36(sp)" );
asm (	"ldw	r10, 40(sp)" );
asm (	"ldw	r11, 44(sp)" );
asm (	"ldw	r12, 48(sp)" );
asm (	"ldw	r13, 52(sp)" );
asm (	"ldw	r14, 56(sp)" );
asm (	"ldw	r15, 60(sp)" );
asm (	"ldw	r16, 64(sp)" );
asm (	"ldw	r17, 68(sp)" );
asm (	"ldw	r18, 72(sp)" );
asm (	"ldw	r19, 76(sp)" );
asm (	"ldw	r20, 80(sp)" );
asm (	"ldw	r21, 84(sp)" );
asm (	"ldw	r22, 88(sp)" );
asm (	"ldw	r23, 92(sp)" );
asm (	"ldw	r25, 100(sp)" );				// r25 = bt
asm (	"ldw	r26, 104(sp)" );				// r26 = gp
// skip r27 because it is sp, and we did not save this on the stack

asm (	"ldw	r29, 116(sp)" );
//asm (	"ldw	r31, 116(sp)" );				// r29 = ea
asm (	"ldw	r30, 120(sp)" );				// r30 = ba
asm (	"ldw	r31, 124(sp)" );				// r31 = ra

asm (	"addi	sp,  sp, 128" );

//int ea, ra;
//asm (	"mov	%0, r29":"=r"(ea));
//asm (	"mov	%0, r31":"=r"(ra));

//printf("The loaded ea: 0x%x\n", ea);
//printf("The loaded ra: 0x%x\n", ra);

	
	
	asm (	"eret" );
	
}

void OS_First_Call() {
 
	
    
	asm ( ".set		noat" );						// Magic, for the C compiler
asm ( ".set		nobreak" );					// Magic, for the C compiler
asm ( "subi		sp, sp, 128" );
asm ( "stw		et, 96(sp)" );
asm ( "rdctl	et, ctl4" );
asm (	"stw	r31, 124(sp)" );				// r31 = ra
	
asm (	"stw	r28, 112(sp)" );				// r28 = fp

asm (	"stw	r29, 116(sp)" );				// r29 = ea
asm (	"addi	fp,  sp, 128" );
asm (	"mov	%0, r27":"=r"(processarray[workingpid].rsp));


	//Calls the next process to run
	printf("This should only go here once, pid: %d\n", workingpid);
	
    //NIOS2_WRITE_STATUS( 1 );			// enable Nios II interrupts
	
	OS_StartTimer(0xFFFFFF);
	
	asm (	"mov	r27, %0" ::"r"(processarray[workingpid].sp));
	
	(*(processarray[workingpid].function))();
	NIOS2_WRITE_STATUS( 0 );
	printf("TERMINATE************************************************\n");
	processarray[workingpid].state = 0;
	
	asm (	"mov	r27, %0" ::"r"(processarray[workingpid].rsp));
	
		asm (	"ldw	r28, 112(sp)" );
	asm (	"ldw	r24, 96(sp)" );				// r28 = fp
		asm (	"ldw	r29, 116(sp)" );
	asm (	"ldw	r31, 116(sp)" );				// r29 = ea
	
asm (	"addi	sp,  sp, 128" );

	printf("TERMINATE************************************************\n");
  asm (	"ret" );
}

