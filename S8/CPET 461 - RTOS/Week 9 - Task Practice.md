```C
static void PeriodicControlTask(void* argument){
	int currentTick = osKernelGetTick();
	int delayTime = 500;
	do{
		// trigger event
		dataEvent = 1;
		
		osDelayUntil(currentTick + delayTime);
	}while(1);
}
```

```C
static void ConsumerTask_X(){

	void localData = null;

	do{
		if(dataEvent){
			// do stuff
			osSemaphoreAcquire(); // on the result sem
			localData = globalData;
			osSemaphoreRelease();
			
			
			
		}
	}while(1)
}
```