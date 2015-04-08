#include "globalvars.h"

void OS_InitMemory() {
NIOS2_WRITE_STATUS( 0 );
   
		
/*
create memory space for os and 16 processes, with starting sp and ending hp
512 = 0x00000200

heap =     0x005FFE00

os sp =     0x00800000 

sp1 =       0x005FFC00 
sp2 =       0x005FFA00  
sp3 =       0x005FF800  
sp4 =       0x005FF600  
sp5 =       0x005FF400  
sp6 =       0x005FF200   
sp7 =       0x005FF000  
sp8 =       0x005FEE00 
sp9 =       0x005FEC00 
sp10 =      0x005FEA00  
sp11 =      0x005FE800  
sp12 =      0x005FE600 
sp13 =      0x005FE400 
sp14 =      0x005FE200  
sp15 =      0x005FE100 
sp16 =      0x005FDE00   

*/
    

    //Setup to zero out memory
    volatile unsigned char * clearaddress = (unsigned char *) startmem;

	
    while(1){
	
        //zero out memory
        *clearaddress = 0;
        //move to next byte address
		clearaddress += 1;
		
        //stops zeroing memory here, this is more than enough
        if(clearaddress == 0x00780000) {
            break;
        }
	}


 NIOS2_WRITE_STATUS( 1 );
return;
}

MEMORY OS_Malloc( int val ) {
	NIOS2_WRITE_STATUS( 0 );
	int i;
    int pid = workingpid;
    int testloc = 0;
    int testloc1 = 0;
    int testloc2 = 0;
	int nextloc = 0;
    int malval = val/2;
 
    //hp1 is the heap pointer to the first flag byte
    volatile unsigned char * hp1 = (unsigned char *) processarray[pid].hp;
    //hp2 is the heap pointer to the second flag byte
    volatile unsigned char * hp2 = (unsigned char *) processarray[pid].hp;
    hp2 += 1;

    //looks for free memory
    while(1) {
    
    //tests the locations of hp1 and hp2 to look to see if it's free
    testloc1 = *hp1;
    testloc2 = *hp2;
    testloc = testloc1 + testloc2;
        
		
	int count = 0;
	
	//It's free, but check to see if there is enough space
    if(testloc == 0) {
    volatile unsigned char * testnext = hp2;
        testnext += 1;
        
		count = 0;
		nextloc = 0;
       
		//checking for enough free bytes
        for(i=0;i<val;i++) {
            //Looks at byte to see if it's free
            nextloc = *testnext;
			
            //if it is free add to count to see if there are enough free bytes
            if(nextloc == 0) {
                count++;
                //go to next byte address
                testnext += 1;
            } else {
                break;
        }   
            
        }
        
        //If there was enough
        if(count>=val) {

			*hp1 = malval;
			*hp2 = malval;
			hp1 += 2;
			break;
        }
        
    } 
	
        //Goes to next block if the first block wasn't free or the weren't enough free bytes
        if(testloc > 0 || count < val) {
    
        hp1 += 4;
        hp2 += 4;
    }
        
    }
	
	//Checks if out of memory before return
	MEMORY ofm = ((MEMORY)hp1) + val;
	
	if(ofm <= heapend) {
	
	volatile unsigned char * assignaddress = hp1;
	
	    while(1){
	//sets bytes to 1, so show they are used, this will help when looking for free zero blocks later
    //this will be over written anyway when a value is write to the memory space
        *assignaddress = 0xFF;
		assignaddress += 1;
		
        if(assignaddress == (hp1 + val)) {
            break;
        }
	}


    NIOS2_WRITE_STATUS( 1 );
    return (MEMORY)hp1;
	
	} else {
	NIOS2_WRITE_STATUS( 1 );
	return 0;
	}

}

BOOL OS_Free( MEMORY m ) {
	NIOS2_WRITE_STATUS( 0 );
    int i;
    int pid = 0;
	int testloc = 0;
    int testloc1 = 0;
    int testloc2 = 0;

	volatile unsigned char * hp = (unsigned char *)m;
	
    //Looks at the two bytes before the address to check for flag bytes
	hp--;
	testloc1 = *hp;
	hp--;
	testloc2 = *hp;
	testloc = testloc1 + testloc2;
	
    //We will know that they are flag bytes because they will be same number
	if(testloc1==testloc2) {
	
	volatile unsigned char * clearaddress = hp;
	
	    for(i=0;i<testloc;i++) {
	//Clear the memory by setting it to zero to help with fragmenation
        *clearaddress = 0;
		clearaddress += 1;

        }
		
        //sets the heap pointer to start looking from here
		processarray[pid].hp = hp;
		NIOS2_WRITE_STATUS( 1 );
		return TRUE;
	} else {
		NIOS2_WRITE_STATUS( 1 );
		return FALSE;
	}
	
	}
	
/* No longer in use
//KMalloc will only be used by the OS, it never has to be freed and it will just give the next memory space
MEMORY OS_KMalloc( int val ) {
	NIOS2_WRITE_STATUS( 0 );
    volatile unsigned char * hp1 = (unsigned char *) oshp;
    volatile unsigned char * hp2 = (unsigned char *) hp1;
	
	hp2+=val;
	
	oshp = hp2;
	NIOS2_WRITE_STATUS( 1 );
return (MEMORY)hp1;
}
*/

