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

**Button Task** - Will check for button press, and display UART output accordingly, while updating the buttonState global variable protected by semaphore
something like...
```C
void StartButtonTask(void *argument)
{
	for(;;)
	{
		x = HAL_GPIO_ReadPin(B1);
		Down();
		buttonState = x;
		localRuntime = globalRuntime;
		localFlash = flashCount;
		Up();
		
		if(button pressed) {
			HAL_UART_Transmit("Uptime : x s | Flashes : y");
		}
	}
}
```

**LED Task** - Will update LED behavior based on buttonstate
something like...
```C
void StartLEDTask(void *argument)
{
	for(;;)
	{
		if(Button is not pressed)
		{
			HAL_GPIO_WritePin(LD2, blink);
			Delay(a corrected 500);
			
			Down();
			flashCount++;
			Up();
		}
		else
		{
			HAL_GPIO_WritePin(LD2, Off);
		}
	}
}
```

```mermaid
Flowchart LR
	A[UART Display Lab \#] ---> B(Default Task)
```
