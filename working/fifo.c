#include "globalvars.h"


FIFO OS_InitFiFo() {
	int i, j, k;
	int fifocounter=0;
    int pid = OS_GetPID();
	FIFO retval;
	int overwrite=0;//0==yes, unused fifo; 1==no, fifo in use
	for(j=0;j<MAXFIFO;j++){//rows
		for(k=0;k<MAXFIFO;k++){//columns
			if(fifopidarray[j][k]!=0){//check that fifo is not in use, if not, overwrite it
				overwrite=1;
				k=MAXFIFO;//force break in for loop
			}
		}
		if(fifoarray[j].data == EMPTY){
			if(fifocounter>=MAXFIFO){ //should never be greater than, this is a precaution
				return INVALIDFIFO; // too many FIFOs
			} else {
				node n;//first node in FIFO
				n.flag = 0; // This allows the value to be overwritten, 0==read
				fifoarray[fifocounter] = n; // First node, also the "head" node
				for(i =1; i<FIFOSIZE; i++){
					if(fifoarray[fifocounter].data==EMPTY){//check for empty space, fifo's data should be made "EMPTY" when deallocated
						node m;
						m.flag = 0;
						fifoarray[fifocounter].next = &m;
						m.previous = &fifoarray[fifocounter];
						fifoarray[fifocounter] = m;
						if(i==7){//last node, tying head and tail nodes to make a circle
							n.previous=&m;
							m.next=&n;
						}
					}else{
						fifocounter++;
					}
				}
				n.next=&fifoarray[fifocounter];//ties first node to other nodes
			}
			fifocounter=j;
			j=MAXFIFO;//force break in for loop
		}
	}//add pid to fifo's list of pids
	for(j=0;j<MAXFIFO;j++){//columns // looking for empty space to write pid
		if(fifopidarray[fifocounter][j]==0){//row belongs to current fifo
			fifopidarray[fifocounter][j]=pid;//add pid to array list
			j=MAXFIFO;//force break in for loop
		}
	}
	retval = fifocounter; // return value is reference to FIFO (place in array where FIFO exists)
	return retval;
}

void OS_Write(FIFO f, int val) {
	int i=0;
	node *temp=&fifoarray[f];
	while(i<=FIFOSIZE){ //check for free space
		if((fifoarray[f].flag==1)&&(i==FIFOSIZE)){ //FIFO full
			fifoarray[f].data=val;
			fifoarray[f].flag=1;
			fifoarray[f]=*fifoarray[f].next;
			i=FIFOSIZE;
		}
		else if(fifoarray[f].flag==1){//look for next empty spot
			temp=fifoarray[f].next;
			i++;
		}else{ //write
			temp->data=val;
			temp->flag=1; //mark as unread
			i=FIFOSIZE;
		}
	}
	return;
}

BOOL OS_Read(FIFO f, int *val) {
	if(fifoarray[f].flag==0){ // fifo is empty
		return FALSE;
	} else{//read
		*val = fifoarray[f].data;
		fifoarray[f].flag=0;// mark as read
		fifoarray[f]=*fifoarray[f].next;//change first node in FIFO by changing pointer
		return TRUE;
	}
}
