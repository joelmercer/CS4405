
int SID
int MAX;
int counter;

void OS_InitSem(int s, int n)
{
	SID = s;
	MAX = n;
	counter = n;
}

void OS_Wait(int s)
{
	while (counter <= 0)
	{
		//Implement sleeper
	}
}

void OS_Signal(int s)
{
	if (counter < MAX)
		counter++;
}
