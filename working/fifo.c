#include "globalvars.h"

FIFO OS_InitFiFo() {
	int i;
	int fifocounter=0;
	FIFO retval;
	if(fifocounter>=MAXFIFO){ //should never be greater than, this is a precaution
		return INVALIDFIFO; // too many FIFOs
	} else {
		node n;
		n.flag = 0; // This allows the value to be overwritten, 0==read
		fifoarray[fifocounter] = n; // First node, also the "head" node
		node first = n;
		
		for(i =1; i<=FIFOSIZE; i++){
			if(fifoarray[fifocounter].data==EMPTY){//check for empty space, fifo's data should be made "EMPTY" when deallocated
				node m;
				m.flag = 0;
				fifoarray[fifocounter].next = &m;
				m.previous = &fifoarray[fifocounter];
				fifoarray[fifocounter] = m;
			}else{
				fifocounter++;
			}
		}
		fifoarray[fifocounter].next = &first;
		first.previous = &fifoarray[fifocounter];
	}
	fifocounter++;
	retval = fifocounter; // place in fifo array where fifo begins?
	return retval;
}

void OS_Write(FIFO f, int val) {
	int i=0;
	node pointer=fifoarray[f]; // find proper fifo
	while(i<FIFOSIZE){ //check for free space
		if((pointer.flag==1)&&(i==FIFOSIZE)){ //FIFO full
			fifoarray[f].data=val;
			fifoarray[f].flag=1;
			fifoarray[f]=*fifoarray[f].next;
			i=FIFOSIZE;
		}
		else if(pointer.flag==1){
			pointer=*pointer.next;
			i++;
		}else{ //write
			pointer.data=val;
			pointer.flag=1; //mark as unread
			i=FIFOSIZE;
		}
	}
	return;
}

BOOL OS_Read(FIFO f, int *val) {
	node pointer=fifoarray[f]; // find proper fifo
	if(pointer.flag==0){ // fifo is empty
		return FALSE;
	} else{
		val=&pointer.data;
		pointer.flag=0;// mark as read
		fifoarray[f]=*pointer.next;
		return TRUE;
	}
}