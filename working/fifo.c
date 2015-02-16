#include "glabalvars.h"

FIFO OS_InitFiFo() {
	int i, fifocounter;
	FIFO retval;
	
	//check that FIFO is not already used *******
	
	if(fifocounter>=MAXFIFO){ //should never be greater than, this is a precaution
		return INVALIDFIFO; // too many FIFOs
	} else{
		node n;
		n.flag = 0; // This allows the value to be overwritten, 0==read
		fifoarray[fifocounter]* = n; // First node, also the "head" node
		for(i =1; i<=FIFOSIZE){
			node m;
			m.flag = 0;
			fifoarray[fifocounter].next* = m;
			m.previous* = fifoarray[fifocounter];
			fifoarray[fifocounter]* = m;
		}
	}
	retval = fifocounter; // place in fifo array where fifo begins?
	return retval;
}

void OS_Write(FIFO f, int val) {
	int i=0;
	node* pointer=fifoarray[f]; // find proper fifo
	while(i<FIFOSIZE){ //check for free space
		if(pointer.flag==1){
			*pointer=pointer.next;
			i++;
		}else if((pointer.flag==1)&&(i==FIFOSIZE)){
			//error, no space *********************
		}else{ //write
			pointer.data=val;
			pointer.flag=0; //mark as unread
			return;
		}
	}
}

BOOL OS_Read(FIFO f, int *val) {
	int i=0;
	node* pointer=fifoarray[f]; // find proper fifo
	if(pointer.flag==1){ // fifo is empty
		return FALSE;
	} else{
		val=pointer.data;
		pointer.flag=1;// mark as read
		*fifoarray[f]=pointer.next;
		return TRUE;
	}
	
}
