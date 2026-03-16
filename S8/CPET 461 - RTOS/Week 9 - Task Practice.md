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
static void ConsumerTask_X(){

	do{
		if(dataEvent)
	}while(1)
}
```