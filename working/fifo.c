#include "glabalvars.h"

FIFO OS_InitFiFo() {
	int i, fifocounter;
	
	//check that FIFO is not already used *******
	
	if(fifocounter<=MAXFIFO){
		return INVALIDFIFO; // too many FIFOs
	} else{
		node n;
		n.flag = 0; // This allows the value to be overwritten
		fifoarray[fifocounter]* = n; // First node, also the head node
		for(i =1; i<=FIFOSIZE){
			node m;
			m.flag = 0;
			fifoarray[fifocounter].next* = m;
			m.previous* = fifoarray[fifocounter];
			fifoarray[fifocounter]* = m;
			}
		}
	}
}

void OS_Write(FIFO f, int val) {

}

BOOL OS_Read(FIFO f, int *val) {

}
