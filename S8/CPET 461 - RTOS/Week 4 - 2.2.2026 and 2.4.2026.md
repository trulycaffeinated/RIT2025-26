# Periodic Tasks
We will often need to create tasks that execute periodically, we have seen that in Labs 2 & 3, and we will see it going forward

Some RTOS's provide a mechanism to easily create a periodic task where the RTOS periodically signals a semaphore
- The body of the task waits on the semaphore at the top of an infinite loop
- The RTOS is responsible for ensuring that the semaphore is signaled precisely at the periodic rate
Free RTOS does not have this capability

Fortunately there is a design pattern that we can use to ensure that the task executes at precisely the periodic rate that we desire

### Problem Statement
``PeriodicTask()`` must execute ever 100ms
The body of ``PeriodicTask()`` takes between 5msec and 12msec to complete

### Analysis
The task must execute every 100ms or the RT application is said to fail
We have no way of knowing or predicting how long the ``PeriodicTask()`` will take to execute

### Solution
Must eliminate the time it takes for the body to execute

```C
void PeriodicTask(void *argument)
{
	#define PERIOIC_TASK_PERIOD_MSEC (100)
	
	do{
		/*body*/
		
		/* Delay the task until the next time to change the LED state*/
		osDelay(PERIODIC_TASK_PERIOD_MSEC); //RELATIVE DELAY
	}while(1);
}
```
This structure creates *time drift*

```C
void PeriodicTask(void *argument)
{
	#define PERIODIC_TASK_PERIOD_MSEC (100)
	uin32_t nextTime = osKernelGetTickCount();
	
	do{
		nextTime += PERIODIC_TASK_PERIOD_MSEC;
		
		/* Delay until next time */
		osDelayUntil(nextTime); // ABSOLUTE DELAY
	}while(1);
}
```
This structure does not create time drift - as long as this task is not longer than 100msec i.e. it does not go beyond ``nextTime``

If the function runs longer than ``osDelayUntil(nextTime)`` it has consumed all of the CPU time... *this is a problem...*

Fundamental constraint of the RTOS - the time slice it uses is 1 ms. Smaller time slice, OS uses more CPU.
# Controls
The physical device (plant) is the entity being controlled
- inputs must be set which effect the plants outside
- Outputs are measured by the sensors

The ``SensorManagerTask`` is responsible for initiating measurements at a periodic rate
- Must execute periodically
- Communicates with the ``SensingTask`` using an **inter-process communication** resource to cause sensor data to be aacquired
	- All that is needed in the body of the ``SensorManagerTask`` is to signal a semaphore, the sensing task waits on this semaphore
- Notice that this is a new use for a semaphore
```C
void SensorManagerTask(void *argument)
{
	#define PERIODIC_TASK_PERIOD_MSEC (100)
	uin32_t nextTime = osKernelGetTickCount();
	
	do{
		nextTime += PERIODIC_TASK_PERIOD_MSEC;
		
		/* Delay until next time */
		osDelayUntil(nextTime); // ABSOLUTE DELAY
	}while(1);
}
```
The ``SensingTask`` is responsible for reading the sensors connected to the plant outputs and collecting measurement data


