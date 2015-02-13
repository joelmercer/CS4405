#include "globalvars.h"

int main() {

    OS_Start();
    OS_InitSem(1, 5);
    OS_Wait(1);
    OS_Signal(1);
    return 0;
}
