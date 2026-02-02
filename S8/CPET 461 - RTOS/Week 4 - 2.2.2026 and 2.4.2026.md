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
		osDelay(PERIODIC_TASK_PERIOD_MSEC);
	}while(1);
}
```