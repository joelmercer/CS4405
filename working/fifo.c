#include "globalvars.h"


FIFO OS_InitFiFo() {
<<<<<<< HEAD
	int i, j;
	FIFO temp;
	//find unused fifo
	for(i=0; i<MAXFIFO; i++){
		if(fifopidarray[i]==EMPTY){
			temp=i;
			fifopidarray[i]=OS_GetPID();
			break;
		}
		if(i==(MAXFIFO-1) && (fifopidarray[i]!=EMPTY)){ // no empty fifos
			return INVALIDFIFO;
=======
	NIOS2_WRITE_STATUS( 0 );
	int i, j, k;
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
			NIOS2_WRITE_STATUS( 1 );
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
>>>>>>> origin/master
		}
	}
	//clear fifo
	for(i=0; i<MAXFIFO; i++){
		fifoarray[temp][i].head=0;
		fifoarray[temp][i].tail=0;
		fifoarray[temp][i].data=EMPTY;
		fifoarray[temp][i].flag=0;
	}
<<<<<<< HEAD
	fifoarray[temp][0].head=1;
	fifoarray[temp][0].tail=1;
	
	return temp;
}

void OS_Write(FIFO f, int val) {
	int i, k;
	for(i=0; i<FIFOSIZE; i++){
		if(fifoarray[f][i].tail==1){
			if((fifoarray[f][i].head==1) && (fifoarray[f][i].data==EMPTY)){ // empty fifo
				printf("FIFO Empty \n");
				fifoarray[f][i].tail=0;
				fifoarray[f][fifoarray[f][i].next].tail=1;
				k=i;
				break;
			}
			else if((fifoarray[f][i].head==1) && (fifoarray[f][i].data!=EMPTY)){ // fifo full
				printf("FIFO Full \n");
				fifoarray[f][i].head=0;
				fifoarray[f][fifoarray[f][i].next].head=1;
				fifoarray[f][i].tail=0;
				fifoarray[f][fifoarray[f][i].next].tail=1;
				k=i;
				break;
			}
			else{
				fifoarray[f][i].tail=0;
				fifoarray[f][fifoarray[f][i].next].tail=1;
				k=i;
				break;
			}
		}
	}
	fifoarray[f][k].data=val;
=======
	NIOS2_WRITE_STATUS( 1 );
	return retval;
}

void OS_Write(FIFO f, int val) {
	NIOS2_WRITE_STATUS( 0 );
	int i=0;
	node *temp=&fifoarray[f];
	while(i<=FIFOSIZE){ //check for free space
		if((temp->flag==1)&&(i==FIFOSIZE)){ //FIFO full
			temp->data=val;
			temp->flag=1;
			temp=temp->next;
			i=FIFOSIZE;
		}
		else if(fifoarray[f].flag==1){//look for next empty spot
			temp=temp->next;
			i++;
		}else{ //write
			temp->data=val;
			temp->flag=1; //mark as unread
			i=FIFOSIZE;
		}
	}
	NIOS2_WRITE_STATUS( 1 );
>>>>>>> origin/master
	return;
}

BOOL OS_Read(FIFO f, int *val) {
<<<<<<< HEAD
	int i;
	for(i=0; i<FIFOSIZE; i++){
		if(fifoarray[f][i].head==1){
			if(fifoarray[f][i].data!=EMPTY){
				fifoarray[f][i].flag=0;
				*val=fifoarray[f][i].data;
				fifoarray[f][i].data=EMPTY;
				fifoarray[f][i].head=0;
				fifoarray[f][fifoarray[f][i].next].head=1;
					if(fifoarray[f][fifoarray[f][i].next].tail==1){
						if(fifoarray[f][fifoarray[f][i].next].data!=EMPTY){
							fifoarray[f][fifoarray[f][i].next].tail=0;
							fifoarray[f][fifoarray[f][fifoarray[f][i].next].next].tail=1;
						}
					}
				return TRUE;
			}else{
				printf("Empty FIFO \n");
				return FALSE;
			}
		}
=======
	NIOS2_WRITE_STATUS( 0 );
	if(fifoarray[f].flag==0){ // fifo is empty
		NIOS2_WRITE_STATUS( 1 );
		return FALSE;
	} else{//read
		*val = fifoarray[f].data;
		fifoarray[f].flag=0;// mark as read
		fifoarray[f]=*fifoarray[f].next;//change first node in FIFO by changing pointer
		NIOS2_WRITE_STATUS( 1 );
		return TRUE;
>>>>>>> origin/master
	}
}
