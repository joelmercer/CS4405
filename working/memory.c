#include "globalvars.h"

void   OS_InitMemory() {

/*
create memory space for os and 16 processes, with starting sp and ending hp

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
    
stackheap[2][16] = { 
    
    {0x007FFC00, 0x007FFA00, 0x007FF800, 0x007FF600, 0x007FF400, 0x007FF200, 0x007FF000, 0x007FEE00, 0x007FEC00, 0x007FEA00, 0x007FE800, 0x007FE600, 0x007FE400, 0x007FE200, 0x007FE100, 0x007FDE00}, 
    
    {0x007FFA00, 0x007FF800, 0x007FF600, 0x007FF400, 0x007FF200, 0x007FF000, 0x007FEE00, 0x007FEC00, 0x007FEA00, 0x007FE800, 0x007FE600, 0x007FE400, 0x007FE200, 0x007FE100, 0x007FDE00, 0x007FDC00} 
    
};

MEMORY OS_Malloc( int val ) {


    
}

BOOL   OS_Free( MEMORY m ) {
    

    
}
