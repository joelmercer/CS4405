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

void the_exception (void) {
		asm ( 	".set		noat" );						
	asm ( 	".set		nobreak" );
	//NIOS2_WRITE_STATUS( 0 ); //disable interrupts
	printf("THE TIMER WENT OFF\n");
	//*(interval_timer_ptr + 1) = 0x5;
	//*(interval_timer_ptr) = 0; 
	
	//if(start==1)
		//workingpid = 16;

	printf("Save Program: %d\n", workingpid);
	
	int pid = 0;

	//asm ( 	"mov	%0, et":"=r"(processarray[pid].regs[24]));
	//asm (	"rdctl	et, ctl4" );
	//asm ( "beq		et, r0, SKIP_EA_DEC" );	        
	//asm ( "subi		ea, ea, 8" );	
//asm ( "addi		ea, ea, 8" );	
	//asm ( "SKIP_EA_DEC:" );
	asm (	"mov	%0, r1":"=r"(processarray[pid].regs[1]));
	printf("r1: 0x%x\n", processarray[pid].regs[1]);
	asm (	"mov	%0, r2":"=r"(processarray[pid].regs[2]));	
	printf("r2: 0x%x\n", processarray[pid].regs[2]);
	asm (	"mov	%0, r3":"=r"(processarray[pid].regs[3]));
	printf("r3: 0x%x\n", processarray[pid].regs[3]);	
	asm (	"mov	%0, r4":"=r"(processarray[pid].regs[4]));
	printf("r4: 0x%x\n", processarray[pid].regs[4]);
	asm (	"mov	%0, r5":"=r"(processarray[pid].regs[5]));
	printf("r5: 0x%x\n", processarray[pid].regs[5]);	
	asm (	"mov	%0, r6":"=r"(processarray[pid].regs[6]));
	printf("r6: 0x%x\n", processarray[pid].regs[6]);	
	asm (	"mov	%0, r7":"=r"(processarray[pid].regs[7]));
	printf("r7: 0x%x\n", processarray[pid].regs[7]);	
	asm (	"mov	%0, r8":"=r"(processarray[pid].regs[8]));
	printf("r8: 0x%x\n", processarray[pid].regs[8]);
	asm (	"mov	%0, r9":"=r"(processarray[pid].regs[9]));	
	printf("r9: 0x%x\n", processarray[pid].regs[9]);
	asm (	"mov	%0, r10":"=r"(processarray[pid].regs[10]));	
	printf("r10: 0x%x\n", processarray[pid].regs[10]);
	asm (	"mov	%0, r11":"=r"(processarray[pid].regs[11]));	
	printf("r11: 0x%x\n", processarray[pid].regs[11]);
	asm (	"mov	%0, r12":"=r"(processarray[pid].regs[12]));	
	printf("r12: 0x%x\n", processarray[pid].regs[12]);
	asm (	"mov	%0, r13":"=r"(processarray[pid].regs[13]));	
	printf("r13: 0x%x\n", processarray[pid].regs[13]);
	asm (	"mov	%0, r14":"=r"(processarray[pid].regs[14]));	
	printf("r14: 0x%x\n", processarray[pid].regs[14]);
	asm (	"mov	%0, r15":"=r"(processarray[pid].regs[15]));	
	printf("r15: 0x%x\n", processarray[pid].regs[15]);
	asm (	"mov	%0, r16":"=r"(processarray[pid].regs[16]));		
	printf("r16: 0x%x\n", processarray[pid].regs[16]);
	asm (	"mov	%0, r17":"=r"(processarray[pid].regs[17]));	
	printf("r17: 0x%x\n", processarray[pid].regs[17]);
	asm (	"mov	%0, r18":"=r"(processarray[pid].regs[18]));	
	printf("r18: 0x%x\n", processarray[pid].regs[18]);
	asm (	"mov	%0, r19":"=r"(processarray[pid].regs[19]));	
	printf("r19: 0x%x\n", processarray[pid].regs[19]);
	asm (	"mov	%0, r20":"=r"(processarray[pid].regs[20]));
	printf("r20: 0x%x\n", processarray[pid].regs[20]);
	asm (	"mov	%0, r21":"=r"(processarray[pid].regs[21]));
	printf("r21: 0x%x\n", processarray[pid].regs[21]);
	asm (	"mov	%0, r22":"=r"(processarray[pid].regs[22]));
	printf("r22: 0x%x\n", processarray[pid].regs[22]);
	asm (	"mov	%0, r23":"=r"(processarray[pid].regs[23]));	
	printf("r23: 0x%x\n", processarray[pid].regs[23]);
	asm (	"mov	%0, r24":"=r"(processarray[pid].regs[24]));	
	printf("r24: 0x%x\n", processarray[pid].regs[24]);
	asm (	"mov	%0, r25":"=r"(processarray[pid].regs[25]));		
	printf("r25: 0x%x\n", processarray[pid].regs[25]);
	asm (	"mov	%0, r26":"=r"(processarray[pid].regs[26]));
	printf("r26: 0x%x\n", processarray[pid].regs[26]);
	
	asm (	"mov	%0, r28":"=r"(processarray[pid].regs[28]));	
	printf("r28: 0x%x\n", processarray[pid].regs[28]);
	asm (	"mov	%0, r29":"=r"(processarray[pid].regs[29]));	//ea
	printf("r29: 0x%x\n", processarray[pid].regs[29]);
	asm (	"mov	%0, r30":"=r"(processarray[pid].regs[30]));	
	printf("r30: 0x%x\n", processarray[pid].regs[30]);
	asm (	"mov	%0, r31":"=r"(processarray[pid].regs[31]));		
	printf("r31: 0x%x\n", processarray[pid].regs[31]);		
	//asm (	"addi	fp,  sp, 128" );	
	
	printf("program save ea: 0x%x\n", processarray[pid].regs[29]);
	printf("program save ra: 0x%x\n", processarray[pid].regs[31]);

	if(workingpid!=16) {
	asm (	"mov	%0, r27":"=r"(processarray[0].regs[27]));
	printf("The saved SP: 0x%x\n", processarray[0].regs[27]);
	asm (	"mov	r27, %0" ::"r"(processarray[0].rsp));
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
} else if(processarray[workingpid].call == EMPTY) {
		//start = 1;
		printf("Call Program first time\n");
		processarray[workingpid].call = 1;
		OS_Interrupt_Handler();
	} else {
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
	int pid = workingpid;
printf("LOAD PROGRAM: %d\n", pid);
	asm (	"mov	r27, %0" ::"r"(processarray[pid].regs[27]));
	//asm (	"mov	4(sp), r29" );
	//asm (	"stw	r29,  4(sp)" );	

	//asm (	"mov	r27, %0" ::"r"(processarray[pid].regs[27]));
	asm (	"mov	r1, %0" ::"r"(processarray[pid].regs[1]));	
	asm (	"mov	r2, %0" ::"r"(processarray[pid].regs[2]));
	asm (	"mov	r3, %0" ::"r"(processarray[pid].regs[3]));
	asm (	"mov	r4, %0" ::"r"(processarray[pid].regs[4]));
	asm (	"mov	r5, %0" ::"r"(processarray[pid].regs[5]));
	asm (	"mov	r6, %0" ::"r"(processarray[pid].regs[6]));
	asm (	"mov	r7, %0" ::"r"(processarray[pid].regs[7]));
	asm (	"mov	r8, %0" ::"r"(processarray[pid].regs[8]));
	asm (	"mov	r9, %0" ::"r"(processarray[pid].regs[9]));
	asm (	"mov	r10, %0" ::"r"(processarray[pid].regs[10]));
	asm (	"mov	r11, %0" ::"r"(processarray[pid].regs[11]));
	asm (	"mov	r12, %0" ::"r"(processarray[pid].regs[12]));
	asm (	"mov	r13, %0" ::"r"(processarray[pid].regs[13]));
	asm (	"mov	r14, %0" ::"r"(processarray[pid].regs[14]));
	asm (	"mov	r15, %0" ::"r"(processarray[pid].regs[15]));
	//asm (	"mov	r16, %0" ::"r"(processarray[pid].regs[16]));
	//asm (	"mov	r17, %0" ::"r"(processarray[pid].regs[17]));
	//asm (	"mov	r18, %0" ::"r"(processarray[pid].regs[18]));
	//asm (	"mov	r19, %0" ::"r"(processarray[pid].regs[19]));
	//asm (	"mov	r20, %0" ::"r"(processarray[pid].regs[20]));
	//asm (	"mov	r21, %0" ::"r"(processarray[pid].regs[21]));
	//asm (	"mov	r22, %0" ::"r"(processarray[pid].regs[22]));
	//asm (	"mov	r23, %0" ::"r"(processarray[pid].regs[23]));
	asm (	"mov	r24, %0" ::"r"(processarray[pid].regs[24]));
	printf("l r24: 0x%x\n", processarray[pid].regs[24]);		
	
	asm (	"mov	r25, %0" ::"r"(processarray[pid].regs[25]));
	
	printf("l r25: 0x%x\n", processarray[pid].regs[25]);		
	
	asm (	"mov	r26, %0" ::"r"(processarray[pid].regs[26]));
	
	printf("l r26: 0x%x\n", processarray[pid].regs[26]);		
	asm (	"mov	r28, %0" ::"r"(processarray[pid].regs[28]));
	
	printf("l r28: 0x%x\n", processarray[pid].regs[28]);		

	asm (	"mov	r29, %0" ::"r"(processarray[pid].regs[29])); //ea
	
	printf("l r29: 0x%x\n", processarray[pid].regs[29]);		
	asm (	"mov	r30, %0" ::"r"(processarray[pid].regs[30]));
	
	printf("l r30: 0x%x\n", processarray[pid].regs[30]);		
	asm (	"mov	r31, %0" ::"r"(processarray[pid].regs[31]));
	
	printf("l r31: 0x%x\n", processarray[pid].regs[31]);		
	//printf("program load ea: 0x%x\n", processarray[pid].regs[29]);
	//printf("program load ra: 0x%x\n", processarray[pid].regs[31]);
	OS_Timer(0x190000);
	//*(interval_timer_ptr) = 0; 
	//	*(interval_timer_ptr + 1) = 0x5;
	
	asm (	"eret" );
	
}

void OS_Interrupt_Handler() {
 
	int pid = workingpid;
    //loads SP for this process
	//asm (	"ldw	r27, "processarray[pid].sp );	
	//Calls the next process to run
	printf("This should only go here once, pid: %d\n", pid);
	
    //NIOS2_WRITE_STATUS( 1 );			// enable Nios II interrupts
	OS_Timer(0x190000);
	asm (	"mov	%0, r27":"=r"(processarray[pid].rsp));
	asm (	"mov	r27, %0" ::"r"(processarray[pid].sp));
	 //NIOS2_WRITE_STATUS( 0 );            // disable Nios II interrupts
	(*(processarray[pid].function))();
   
	asm (	"mov	r27, %0" ::"r"(processarray[pid].rsp));
	printf("TERMINATE************************************************\n");
	//terminate = 0;
	//printf("TERMINATE************************************************\n");
	
    asm (	"eret" );
}

void OS_Timer(int counter) {
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
	*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
*(interval_timer_ptr + 1) = 0x9;	// STOP = 0, START = 1, CONT = 1, ITO = 1 
NIOS2_WRITE_IENABLE( 0x3 );
	
		*(interval_timer_ptr + 1) = 0x5;
	NIOS2_WRITE_STATUS( 1 );			// enable Nios II interrupts
	
	return;
}

