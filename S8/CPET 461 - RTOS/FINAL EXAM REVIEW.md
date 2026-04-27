Wed. April 29th ; 1:30pm - 4:00pm ; GLE 2159
10 Short Answer Questions - cumulative of the semester

---

![[Pasted image 20260427150709.png]]

Exam is cumulative, but focus on L16 and beyond

**Things to review/do**
Comfortable drawing task description diagram, but also understanding task description diagrams.
Review Scheduling algorithms 

**Lab 8 Review - USING EVENTS**
when using semaphores the watchdog can get blocked, or block another task. This is what is wrong with mine, I use a semaphore which can BLOCK other tasks. I must change it to use events
```C
taskToCheck(void* argument) {
	
	mask = (1 << PHIL_NUM);
	
	//somewhere in this task
	osEventFlagsSet(Handle,
				 mask);
	// call this two or three times depending
	
}
```

```C
watchDogTask(void* argument) {
	
	while(1) {
		// call this
		set = osEventFlagsGet(Handle);
	
		if(set != ALL_TASKS_OKAY) { //ALL TASKS OKAY == 0xFF for our 8 tasks
			// reset here
		}
		else{
			osEventFlagsClear(Handle, 0xFF);
		}
		osDelay(watchingDelayTime);
	}
}
```