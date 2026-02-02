# Lab 3 Plan
## Semaphore
I will be using a single semaphore i've dubbed `sharedStateSemaphore` - as this semaphore will handle all things related to this operation of pressing the button, and toggling what the LED does as well as UART output. 

## Tasks
Two additional tasks on top of default task, but I will give default task a purpose this time.
**Default Task** - update the runtime global variable (protected by the semaphore). Something like...
```C
void StartDefaultTask(void *argument)
{
	for(;;)
	{
		Down(); 
		runtimeGlobal = osKernelGetTick(); // Since 1 Tick = 1 ms, we will keep runtimeGlobal in ms and avoid and loss of ticks for now
		Up();
	}
}
```

**Button Task** - 