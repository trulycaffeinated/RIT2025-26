# Lab 3 Important Points
Every **Hardware Device** is  accessed only within one task - a single task to output/input for a device
- LED should always be in an LED task, and referenced nowhere else, UART always accessed in one UART task and nowhere else

All **Local Variables** for tasks are *similar* to static variables
**Static** - variable retains value from previous function run
- These variables are allocated on the stack for the task
- Remember, each task has its own stack
- One characteristic of a static variable we must always do is give it an initial value
- Local variables that aren't initialized get whatever happens to be on the stack

when using ``osSemaphoreAcquire()`` use ``HAL_MAX_DELAY`` or ``osWaitForever`` - try to get it for as long as possible
```C
osSemaphoreAcquire(handle, HAL_MAX_DELAY);
/* AS LITTLE CODE AS POSSIBLE */
osSemaphoreRelease();
```

---
# Preemptive multitasking

An Operating System will go from Running to Ready when it's not waiting for anything, and the CPU is taken from it.
The task is still running/would like to be running, but no CPU for it.

**Preemptive** scheduling is so called because tasks are preempted while they're executing

The RTOS is entirely responsible for preempting the execution of a task, there is nothing that the task can do about it and the task doesn't even know it's happening

### Consider The following
**Task 1** - Executes for 2msec every 20msec
**Task 2** - Executes for 3msec every 10msec
**Task 3** - Executes for 6msec every 25msec

RTOS configured with a 1msec timescale

**Round Robin Scheduler** - The task that's been waiting the longest, is the task that goes next. 
"Fair" scheduler, and is the most common

***Priority* Round Robin Scheduling** - Round Robins through priority groups, Priority 1 round robins, once Group 1 is done, Priority 2 group goes until Group 1 needs it