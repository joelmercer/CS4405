void OS_Interrupt_Handler(void) {
    
	int ipending;
	NIOS2_READ_IPENDING(ipending);
	if ( ipending & 0x1 )				// time q is interrupt level 0
	{
        OS_Start();
		//Call something I think maybe OS_Start() **********
	}
	if ( ipending & 0x2 )				// pushbuttons are interrupt level 1
	{
		//nothing I'm guessing we won't enable push buttons, I don't think we need buttons.
	} else { 
    OS_Start(); //Task yielded CPU
    }
}