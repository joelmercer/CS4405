#include "globalvars.h"

void OS_InitMemory() {

   
		
/*
create memory space for os and 16 processes, with starting sp and ending hp
512 = 0x00000200


os sp =     0x00800000 or 8388608
os hp =     0x007FFE00 or 8387584

sp1 =       0x007FFC00 or 8387584 
hp1 =       0x007FFA00 or 8387072

sp2 =       0x007FFA00 or 8387072
hp2 =       0x007FF800 or 8386560 

sp3 =       0x007FF800 or 8386560 
hp3 =       0x007FF600 or 8386048 

sp4 =       0x007FF600 or 8386048 
hp4 =       0x007FF400 or 8385536  

sp5 =       0x007FF400 or 8385536  
hp5 =       0x007FF200 or 8385024 

sp6 =       0x007FF200 or 8385024 
hp6 =       0x007FF000 or 8384512 

sp7 =       0x007FF000 or 8384512 
hp7 =       0x007FEE00 or 8384000 

sp8 =       0x007FEE00 or 8384000 
hp8 =       0x007FEC00 or 8383488 

sp9 =       0x007FEC00 or 8383488 
hp9 =       0x007FEA00 or 8382976 

sp10 =      0x007FEA00 or 8382976 
hp10 =      0x007FE800 or 8382464 

sp11 =      0x007FE800 or 8382464 
hp11 =      0x007FE600 or 8381952 

sp12 =      0x007FE600 or 8381952 
hp12 =      0x007FE400 or 8381440 

sp13 =      0x007FE400 or 8381440 
hp13 =      0x007FE200 or 8380928 

sp14 =      0x007FE200 or 8380928 
hp14 =      0x007FE100 or 8380416 

sp15 =      0x007FE100 or 8380416 
hp15 =      0x007FDE00 or 8379904 

sp16 =      0x007FDE00 or 8379904 
hp16 =      0x007FDC00 or 8379392   

*/
    

    
    volatile unsigned char * clearaddress = (unsigned char *) startmem;

	printf("add: 0x00%x \n", clearaddress);
	
    while(1){
	
	
        *clearaddress = 0;
		clearaddress += 1;
		
        if(clearaddress == 0x007FFE10) {
            break;
        }
	}

printf("Done Clear \n");
 
return;
}

MEMORY OS_Malloc( int val ) {
	int i;
    int pid = 0;
    int testloc = 0;
    int testloc1 = 0;
    int testloc2 = 0;
	int nextloc = 0;
    int malval = val/2;
  //  int size = processarray[pid].hsize;
    volatile unsigned char * hp1 = (unsigned char *) processarray[pid].hp;
    volatile unsigned char * hp2 = (unsigned char *) processarray[pid].hp;
    
    hp2 += 1;
	
	//printf("Hp1: 0x00%x \n", hp1);
	//printf("Hp2: 0x00%x \n", hp2);

    while(1) {
		//printf("in while loop\n");
    testloc1 = *hp1;
    testloc2 = *hp2;
    testloc = testloc1 + testloc2;
        
		//printf("testloc: %d\n", testloc);
	int count = 0;
	
	//Check to see if there is enough space
    if(testloc == 0) {
    volatile unsigned char * testnext = hp2;
        testnext += 1;
        
		count = 0;
		nextloc = 0;
       
		
        for(i=0;i<val;i++) {
            
            nextloc = *testnext;
			
			//printf("testnext: 0x00%x \n", testnext);
           // printf("nextloc: %d\n", *testnext);
			
            if(nextloc == 0) {
                count++;
                testnext += 1;
            } else {
				//printf("Break1\n");
                break;
        }   
            
        }
        
        if(count>=val) {

			*hp1 = malval;
			*hp2 = malval;
			hp1 += 2;
		//	printf("Break2\n");
			break;
        }
        
    } 
	
        //Goes to next block
        if(testloc > 0 || count < val) {
    
        hp1 += 4;
        hp2 += 4;
		//printf("hp1: 0x00%x\n", hp1);
        //printf("hp2: 0x00%x\n", hp2);    
    }
        
    }
	
	//Set all bits as in use
	
	volatile unsigned char * assignaddress = hp1;
	
	    while(1){
	
        *assignaddress = 0xFF;
		assignaddress += 1;
		
        if(assignaddress == (hp1 + val)) {
            break;
        }
	}
	
	

    processarray[pid].hp = (hp1 + val);
    
    return (MEMORY)hp1;

}

BOOL OS_Free( MEMORY m ) {
    int i;
    int pid = 0;
	int testloc = 0;
    int testloc1 = 0;
    int testloc2 = 0;

	volatile unsigned char * hp = (unsigned char *)m;
	
	printf("hp1: 0x00%x \n", hp);
	hp--;
	printf("hp2: 0x00%x \n", hp);
	testloc1 = *hp;
	hp--;
	testloc2 = *hp;
	printf("hp3: 0x00%x \n", hp);
	testloc = testloc1 + testloc2;
	
	
	
	volatile unsigned char * clearaddress = hp;
	
	    for(i=0;i<testloc;i++) {
	
        *clearaddress = 0;
		clearaddress += 1;

        }
		
		processarray[pid].hp = hp;
		
		return TRUE;
		
	}
    

