===================
CS4405 OSII Project
===================

----------------------------------
Part I: OS File Contents
----------------------------------
Header (.h) Files:
	os.h
		This is the header file that Professor Kent provided us with as a skeleton for our operating system.  This file has remained unchanged.
	globalvars.h
		This is the file that contains the global variables, structure definitions, and function declarations for the other .c files, excluding any that were predefined by the instructor in os.h.
.c Files:
	contextswitch.c
		This allows our operating system to switch prom one program to another.  It is utilized by the scheduler and it functions by first saving the registers of the current process into memory and then, after the calling process has returned, it loads the data back into registers from memory.  The assemby code for the context switching functionality came from the Altera DE2 Board tutorial documentation which was provided by the instructor on Desire2Learn.  The rest of the code in this file belongs to the project team.  This file also contains the OS_Interrupt_Handler function which tells the Context_Switch function where to find the new function which should be executed.
	fifo.c
		This file contains the functionality for FIFO structures.  The structures are written as cyclical doubly-linked lists with each element being a node (structure defined in globalvars.h).  The nodes contain data, pointers to the previous and next nodes in the linked list, and a flag which indicates the read status of the data (0=read; 1=unread).  There exists an array for each FIFO that tracks a list of process IDs belonging to any processes that utilize a particular FIFO.  These process IDs are removed when a process terminates by calling the OS_Terminate function.  A previously used FIFO becomes available for use again when its corresponding array becomes empty.  FIFOs are initialized to empty by the OS_Init function and then reinitialized when a process needs a FIFO which allows then to clear any unused structures.  
	init.c
		Any functions required to initialize and start the operating system is contained here.  
		The OS_Init function is responsible for setting up and initializing empty structures in the schedule, semaphore, process, and FIFO arrays.  It also sets up and initializes the process ID array for FIFOs to empty values.  The OS_Start function is responsible for starting execution of processes through the scheduler.  This only includes sporadic functions for the first deliverable.  This is also where the OS_Abort function returns to in the event of a catastrophic error.  The OS_Abort function simply stops the operating system without performing any graceful shut down routines.  This file also contains the custom OS_AddToSchedule function which is used in order to add a process to the scheduler, currently only working for sporadic as periodic and device level processes are not included in the first deliverable.  This function only requires the device level (0=device; 1=periodic; 2=sporadic) and process ID of the calling process.
	processman.c
		This file contains all functions related to the life cycle of a process.  It is responsible for the creation of a function, retrieval of parameters, its termination, and yielding, which allows other processes to execute.  When a process is created, a structure is created and added to the array of processes and the it is added to the scheduler.  This file contains the custom function OS_GetPID which is utilized FIFO in order to tell which FIFOs a process is using.  The OS_Terminate function is called when a process ends its execution.  It removes the process's ID from the semaphore and FIFO PID arrays as well as the scheduler.
	semaphores.c
		This file contains the functions responsible for initializing and using a semaphore.  The OS_InitSem function creates a new semaphore structure and adds it to the semaphore array.  The OS_Wait function is called when a process wishes to lock a section of code from being executed by other processes.  It disables interrupts when called and adds the calling process's ID to the semaphore's corresponding process ID array.  The OS_Signal function enables interrupts and removes the calling process's ID from the semaphore's corresponding process ID array.
	main.c
		This is a custom file that is responsible for running the operating system.  It is responsible for calling OS_Init and calling OS_Start.  It declares variables contained in the globalvars.h header file.  For the time being, it is being used to create a semaphore, a FIFO, and run a test processes in order to test the operating system.
		
----------------------------------
Part II:  Operation
----------------------------------
In order to run the operating system, all of the above .c and header files must be compiled in a new project using the Altera Monitor Program.  Use this program to compile, load to the board, and run the operating system.

----------------------------------
Part III: Testing
----------------------------------
In order to test the operating system, a test.c file has been included with the operating system files.  The main.c file utilizes this file when running the operating system automatically, so place it in the project along with the other files when using the monitor program.

----------------------------------
Part IV: Special instructions
----------------------------------
When setting up the project in the Altera Monitor Program, change the system settings for .text and .data to have an offset of 400.  This is to allow context switching as lower memory is used by the Context_Switch function in contextswitch.c.