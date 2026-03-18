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
			registersIO = 0xFF; // write to registers
		}
		
		osDelay(50); // delay some period of time after registers
	}while(1)
}
```

```C
static void AcquisitionTask(void* argument){
	do{
		ADCValues = registersIO;
		
		// calculate results
		// math
		// more math
		// wow more math
		finalResult = /*math*/;
		osSemaphoreAcquire();
		result = finalResult;
		osSemaphoreRelease();
		
		// trigger result event
	
	}while(1);
}
```

```C
static void ConsumerTask_X(void* argument){

	void localData = null;

	do{
		
		
		
	}while(1)
}
```

# Task Practice #2
```C
static void ControlTask(void* argument){
	nextCandidate = 2;
	while(nextCandidate < 4096){
		for(int i = 0; i < WorkerQueue.size(); i++) {
			if(WorkerQueue[i]){
				AvailableEvents (1 << i);
			}
		}
		for(int i )
	}
}
```

```C
static void WorkerTask(void* argument){
	do{
		// this is wrong v
		while(osMessageQueueGet() == 0);
		// this is wrong ^
		myCandidate = nextCandidate;
		availableEvents[myCandidate] = 0;
		if(isPrime(MyCandidate)) {
			osSemaphoreAcquire();
			Primes[NumPrimes] <= MyCandidate;
			NumPrime++;
			osSemaphoreRelease();
		}
		worker[myCandidate] = 1;
	}while(1);
}
```