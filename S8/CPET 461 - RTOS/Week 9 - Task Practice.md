```C
static void PeriodicControlTask(void* argument){
	int currentTick = osKernelGetTick();
	int delayTime = 500;
	do{
		// trigger event
		
		osDelayUntil(currentTick + delayTime);
	}while(1);
}
```

```C
static void HwSetupTask(void* argument){
	do{
		if(dataEvent){
			registersIO = 
		}
		
		osDelay(50); // delay some period of time after registers
	}while(1)
}
```

```C
static void ConsumerTask_X(void* argument){

	void localData = null;

	do{
		if(resultEvent){
			// do stuff
			osSemaphoreAcquire(); // on the result sem
			localData = globalData;
			osSemaphoreRelease();
			
			// data processing
			
		}
	}while(1)
}
```