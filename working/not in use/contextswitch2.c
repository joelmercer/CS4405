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
asm ("movia		r2, main");				// Call the C language main program
asm ("jmp		r2"); 

}

void the_exception (void) __attribute__ ((section (".exceptions")));

void the_exception (void)  {

//printf("TIMER WENT OFF\n");
	
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

asm (	"mov	%0, r27":"=r"(processarray[workingpid].sp));

if(workingpid!=16) {
	
printf("The saved SP: 0x%x\n", processarray[0].sp);
	asm (	"mov	r27, %0" ::"r"(processarray[16].sp));
}
	
	//OS_Load_Scheduler();
	//printf("I don't think this should go back here\n");

workingpid = 0;
if(start == 0) {
	start = 2;
	printf("Starts the first time");
	OS_Start();
} else if (start == 1) {
	start = 2;
	OS_Load_Scheduler();
} else if(processarray[workingpid].state == 1) {
		//start = 1;
		printf("Call Program first time\n");
		processarray[workingpid].state = 2;
		OS_Interrupt_Handler();
	} else if (processarray[workingpid].state == 2) {
		//start = 1;
		printf("Call Program second time\n");
		OS_Load_Program();
	}

}

void OS_Save_Scheduler() {

	//Saves Schedule   
printf("Save Schedule\n");	
	
	//asm (	"mov	%0, r27":"=r"(startregs[27])); //sp
	asm ( ".set		noat" );						
	asm ( ".set		nobreak" );					
	//asm ( "subi		sp, sp, 128" );
	asm ( "mov		%0, et":"=r"(startregs[24]));
	asm ( "rdctl	et, ctl4" );
	//asm ( "beq		et, r0, SKIP_EA_DEC" );	        
	//asm ( "subi		ea, ea, 8" );				
	asm ( "addi		ea, ea, 4" );	
	//asm ( "SKIP_EA_DEC:" );
	asm (	"mov	%0, r1":"=r"(startregs[1]));
	asm (	"mov	%0, r2":"=r"(startregs[2]));	
	asm (	"mov	%0, r3":"=r"(startregs[3]));	
	asm (	"mov	%0, r4":"=r"(startregs[4]));
	asm (	"mov	%0, r5":"=r"(startregs[5]));	
	asm (	"mov	%0, r6":"=r"(startregs[6]));	
	asm (	"mov	%0, r7":"=r"(startregs[7]));	
	asm (	"mov	%0, r8":"=r"(startregs[8]));
	asm (	"mov	%0, r9":"=r"(startregs[9]));	
	asm (	"mov	%0, r10":"=r"(startregs[10]));	
	asm (	"mov	%0, r11":"=r"(startregs[11]));	
	asm (	"mov	%0, r12":"=r"(startregs[12]));	
	asm (	"mov	%0, r13":"=r"(startregs[13]));	
	asm (	"mov	%0, r14":"=r"(startregs[14]));	
	asm (	"mov	%0, r15":"=r"(startregs[15]));	
	asm (	"mov	%0, r16":"=r"(startregs[16]));		
	asm (	"mov	%0, r17":"=r"(startregs[17]));	
	asm (	"mov	%0, r18":"=r"(startregs[18]));	
	asm (	"mov	%0, r19":"=r"(startregs[19]));	
	asm (	"mov	%0, r20":"=r"(startregs[20]));
	asm (	"mov	%0, r21":"=r"(startregs[21]));
	asm (	"mov	%0, r22":"=r"(startregs[22]));
	asm (	"mov	%0, r23":"=r"(startregs[23]));	
	asm (	"mov	%0, r25":"=r"(startregs[25]));		
	asm (	"mov	%0, r26":"=r"(startregs[26]));	
	
	asm (	"mov	%0, r28":"=r"(startregs[28]));	
	asm (	"mov	%0, r29":"=r"(startregs[29]));	//ea
	asm (	"mov	%0, r30":"=r"(startregs[30]));	
	asm (	"mov	%0, r31":"=r"(startregs[31]));				
	//asm (	"addi	fp,  sp, 128" );	
	printf("Sch save ea: 0x%x\n", startregs[29]);
	printf("Sch save ra: 0x%x\n", startregs[31]);
	
	/*
printf("working pid %d\n", workingpid);
	printf("WHAT THE HECK IS THIS NUMBER WHY DOES IT KEEP GOING HERE: %d\n", processarray[workingpid].call);
	//Calls to check for next function to run
	if(processarray[workingpid].call == EMPTY) {
		printf("Call Program first time\n");
		processarray[workingpid].call = 1;
		OS_Interrupt_Handler();
	} else {
		printf("Call Program second time\n");
		OS_Load_Program();
	}
	printf("after call Program\n");
	*/
	OS_Timer(0x1);
	int i;
	for(i = 0; i < 100; i++) {}
	asm (	"eret" );
}

void OS_Load_Scheduler() {
	asm (	"mov	sp, %0" ::"r"(startregs[27])); //sp
printf("load Schedule\n");
	//Loads Schedule    
	
	
	asm (	"mov	r1, %0" ::"r"(startregs[1]));	
	asm (	"mov	r2, %0" ::"r"(startregs[2]));
	asm (	"mov	r3, %0" ::"r"(startregs[3]));
	asm (	"mov	r4, %0" ::"r"(startregs[4]));
	asm (	"mov	r5, %0" ::"r"(startregs[5]));
	asm (	"mov	r6, %0" ::"r"(startregs[6]));
	asm (	"mov	r7, %0" ::"r"(startregs[7]));
	asm (	"mov	r8, %0" ::"r"(startregs[8]));
	asm (	"mov	r9, %0" ::"r"(startregs[9]));
	asm (	"mov	r10, %0" ::"r"(startregs[10]));
	asm (	"mov	r11, %0" ::"r"(startregs[11]));
	asm (	"mov	r12, %0" ::"r"(startregs[12]));
	asm (	"mov	r13, %0" ::"r"(startregs[13]));
	asm (	"mov	r14, %0" ::"r"(startregs[14]));
	asm (	"mov	r15, %0" ::"r"(startregs[15]));
	asm (	"mov	r16, %0" ::"r"(startregs[16]));
	asm (	"mov	r17, %0" ::"r"(startregs[17]));
	asm (	"mov	r18, %0" ::"r"(startregs[18]));
	asm (	"mov	r19, %0" ::"r"(startregs[19]));
	asm (	"mov	r20, %0" ::"r"(startregs[20]));
	asm (	"mov	r21, %0" ::"r"(startregs[21]));
	asm (	"mov	r22, %0" ::"r"(startregs[22]));
	asm (	"mov	r23, %0" ::"r"(startregs[23]));
	asm (	"mov	r24, %0" ::"r"(startregs[24]));
	asm (	"mov	r25, %0" ::"r"(startregs[25]));
	asm (	"mov	r26, %0" ::"r"(startregs[26]));
	
	asm (	"mov	r28, %0" ::"r"(startregs[28]));
	asm (	"mov	r29, %0" ::"r"(startregs[29])); //ea
	asm (	"mov	r30, %0" ::"r"(startregs[30]));
	asm (	"mov	r31, %0" ::"r"(startregs[31]));
	printf("Sch load ea: 0x%x\n", startregs[29]);
	printf("Sch load ra: 0x%x\n", startregs[31]);
	

	
	asm (	"eret" );
}

void OS_Load_Program() {
	
	
printf("LOAD PROGRAM: %d\n", workingpid);
OS_Timer(0xFFFFFFFF);
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


	
	asm (	"eret" );
	
}

void OS_Interrupt_Handler() {
 
	int pid = workingpid;
    
	asm ( ".set		noat" );						// Magic, for the C compiler
asm ( ".set		nobreak" );					// Magic, for the C compiler
asm ( "subi		sp, sp, 128" );
asm ( "stw		et, 96(sp)" );
asm ( "rdctl	et, ctl4" );
asm (	"stw	r31, 124(sp)" );				// r31 = ra
	
asm (	"stw	r28, 112(sp)" );				// r28 = fp

asm (	"stw	r29, 116(sp)" );				// r29 = ea
asm (	"addi	fp,  sp, 128" );
asm (	"mov	%0, r27":"=r"(processarray[pid].rsp));


	//Calls the next process to run
	printf("This should only go here once, pid: %d\n", pid);
	
    //NIOS2_WRITE_STATUS( 1 );			// enable Nios II interrupts
	OS_Timer(0x190000);
	
	asm (	"mov	r27, %0" ::"r"(processarray[pid].sp));
	 //NIOS2_WRITE_STATUS( 0 );            // disable Nios II interrupts
	(*(processarray[pid].function))();
	NIOS2_WRITE_STATUS( 0 );
	printf("TERMINATE************************************************\n");
	processarray[workingpid].state = 0;
	
	asm (	"mov	r27, %0" ::"r"(processarray[pid].rsp));
	
		asm (	"ldw	r28, 112(sp)" );
	asm (	"ldw	r24, 96(sp)" );				// r28 = fp
		asm (	"ldw	r29, 116(sp)" );
	asm (	"ldw	r31, 116(sp)" );				// r29 = ea
	
asm (	"addi	sp,  sp, 128" );

	
  asm (	"ret" );
}

void OS_Timer(int counter) {
	volatile int * KEY_ptr = (int *) 0x10000050;					// pushbutton KEY address
	printf("start the timer\n");
	*(interval_timer_ptr) = 0; 
	*(interval_timer_ptr + 1) = 0; 
		//int counter = 0x090000;				// 1/(50 MHz) x (0x190000) = 33 msec
	//	int counter = 0xF90000;				// 1/(50 MHz) x (0x190000) = 33 msec
	//*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
//	*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;

	/* start interval timer, enable its interrupts */
	//*(interval_timer_ptr + 1) = 0x5;	// STOP = 0, START = 1, CONT = 1, ITO = 1 
	//NIOS2_WRITE_IENABLE( 0x3 );
	counter = 0xFFFFFF;
	*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
//*(interval_timer_ptr + 1) = 0x9;	// STOP = 0, START = 1, CONT = 1, ITO = 1 

	
		*(interval_timer_ptr + 1) = 0x5;
		
		*(KEY_ptr + 2) = 0xE; 
		NIOS2_WRITE_IENABLE( 0x3 );
	NIOS2_WRITE_STATUS( 1 );			// enable Nios II interrupts
	
	return;
}

