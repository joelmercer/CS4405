README FOR THE ATHENA OS

	These are the setup instructions for the Athena OS, henceforth referred to solely as 'Athena'. To start, ensure the Altera DE2 board is plugged in to a computer running the Altera Monitor Program, and turned on.

	In order to run the OS on the board you will need the help of the monitor program. Simply create a new project, including all the files in the ~/src/ directory, excluding FIFO and semaphore, and it should compile and run with no issues. 

	**[BE SURE THE OFFSET FOR THE DATA AND TEXT SECTIONS ARE SET TO 400 OR THEY WILL OVERLAP THE EXCEPTION HANDLER]

	Here, you may hit 'run'. This is where you should see Athena up and running. The kernal can be considered a working demo and below are the steps our "demo" takes.



1. Main is called and does OS_Init to start our currently lone process.

2. OS_Start is called and starts to schedule the processes that are currently sitting in the process doubly linked list known as the process table.

3. The scheduler will context switch into the process with the help of context_switch.c and the assembly written in it. Once the exception handler in context_switch.c is called, the function pointer in the current process is referenced.

4. The "Program" the process runs is the first function in os.c, 'processFunction()'. This program is a simple toy loop to demonstrate that allocating and freeing memory is functional at this stage.

5. Since only one program is running, it will instantly jump right back into executing the "Context Switch" program.

6. The OS uses puts to display info of the context switch taking place on the Monitor Program console display.


	The memory component that was added in this deliverable has two main components.
	
	Firstly, as the maximum number of processes are already defined, we statically allocate an array of 16 process structs; this allows the compiler to lay out the memory for us. This can be found referenced in process.h.
	
	Thus, OS_Create no longer calls malloc as it did initially. It now simply looks through the array for an available process control block and assigns it to the calling process.
	
	Secondly, the only time a program will call OS_Malloc is when it is trying to extend its heap space. Keeping this in mind, we allocate a 4096 slot; a static array of MEMORY types. Each bucket acts as one lump the program can extend by. In mainMemory, every element is set to 0, indicating that each slot is available, otherwise it is occupied.
	
	As an example:
		'OS_Malloc(4)' will grab one of the 30 memory containers. This is another static array of structs, similar to that of the arracy of PCBs mentioned earlier.
		
		These containers keeps track of the memory for a given process. Each PCB will have a linked list of these memory block structs that hold the address of where their contiguous memory begins, the flags associated with it, and the other various fields.
		
		Once a free struct is found, the function then looks through the mainMemory array, attempting to find a contiguous segment for size 4 to satisfy the request. If found, the process is updated and the address is returned, otherwise we return -1 notifying the program that the request could not be serviced.
		

	If you wish to make your own program, simply create a new function that is your "program" and enqueue a process struct onto the list of processes. Be sure to point your function pointer to the function you made for your "program".

	As for the other system calls such as FIFO and Semaphore, they are all currently implemented and have been lightly tested.

	As well, there is a call to OS_Abort() in os.c that may be placed in OS_Start(), around line 105. To do so, simply uncomment the call 'NIOS2_RESET()' in OS_Abort(). Once done, recompile and reload Athena to your Altera DE2 board, and rerun the program. You will be able to note the complete reset of the Altera DE2 board, completely aborting Athena. To restart Athena from this state, simply re-run the program in the Altera Monitor Program.
	
	NOTED ISSUES:
		Currently, the device and periodic processes are a simple skeleton framework. This has not been forgotten, and will be changed in the near future. Unfortunately, the timing for this deliverable was unforgiving and sacrifices needed to be made.
		
		OS_Yield and the associated timers associated with these processes are also, as such, yet to be fully implemented.

Athena will continue to be developed and will grow with time.
