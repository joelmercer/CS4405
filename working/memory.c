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
    

    //Setup to zero out memory
    volatile unsigned char * clearaddress = (unsigned char *) startmem;

	
    while(1){
	
        //zero out memory
        *clearaddress = 0;
        //move to next byte address
		clearaddress += 1;
		
        //stops zeroing memory here, this is more than enough
        if(clearaddress == 0x007FFE10) {
            break;
        }
	}


 
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
	
	//Set all bits as in use
	
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

    //sets next heap pointer to start from
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
		
		return TRUE;
	} else {
		return FALSE;
	}
	
	}

//KMalloc will only be used by the OS, it never has to be freed and it will just give the next memory space
MEMORY OS_KMalloc( int val ) {
    volatile unsigned char * hp1 = (unsigned char *) oshp;
    volatile unsigned char * hp2 = (unsigned char *) hp1;
	
	hp2+=val;
	
	oshp = hp2;
	
return (MEMORY)hp1;
}

