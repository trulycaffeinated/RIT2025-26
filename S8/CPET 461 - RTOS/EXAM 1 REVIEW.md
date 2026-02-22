# H1
Why do we need an operating system? 
- Provides a virtual machine for applications
	- Each application can be written without regard to the existence of any other application
		- i.e. each application does not care about other applications - it just does what it's designed to do
- Provides a means for applications to easily migrate across platforms
	- as new hardware becomes available, the application can still work seamlessly
		- As updates in hardware arrive, the application should still work the same on the new hardware across different operating systems. NO functionality should be changed
- Manage hardware resources across applications
	- Allow one application exclusive use of a hardware device
	- Coordinate / manage multiple applications use of a hardware device

**TLDR;**
Operating Systems are used to provide a "virtual machine" for applications, and allow applications to exist and run without concern for other applications.
Because an application is run on this "virtual machine" - changes in hardware should not cause any issue for the application, and no update should be required. 
Lastly, the operating system allows one application exclusive use of a hardware device (like the STM32 GPIO). And manages the applications when multiple require the use of a hardware device.

# H2
![[Pasted image 20260222115241.png]]
RTOS Contains only **one** kernel function - which are functions that involve interactions between tasks or between tasks and the RTOS itself

Generally the RTOS does not contain device drivers. However, it is not uncommon that an RTOS will be packaged with a collection of device drivers.

**We need an RTOS for *Guaranteed Temporal Performance***
Which is when something needs to be happening in real time, it is.

We give up 2 things to achieve this GTP
- Support for a wide variety of hardware devices, as RTOS are usually designed with specific hardware device(s) in mind
- Common API

# H3
There are four (typical) task states
1. Ready
2. Running
3. Blocked
4. Delayed
*A fifth*
*5. Suspend*
is available

5. Running -> Ready
	1. **Running state can only have one task per CPU Core**
	2. Preempted by scheduler
	3. Wait on signaled resource
	4. signal a resource
	5. Call osThreadYield()
6. Ready -> Running
	1. Selected by schedule
	2. **There always has to be something running on the CPU**
		1. There is such a thing as a *null* task that runs when nothing else is happening -- typically nothing can be written for the null task, but some OS's allow it
7. Running -> Blocked
	1. Wait on unsigned resource
	2. Something the task wants is not present
	3. Blocked task does not automatically become the next task in queue
8. Running -> Delayed
	1. Call osDelay()
	2. Call osDelayUntil()
9. Blocked -> Ready
	1. Resource is signaled
10. Delayed -> Ready
	1. Time Delay Expires
						 **THE FOLLOW STATES ARE BAD DESIGN**
11. Delayed <-> Suspended
	1. osKernelSuspend() is called
	2. osKernelResume() is called
12. Blocked <-> Suspended
	1. osKernelSuspend() is called
	2. osKernelResume() is called
13. Ready <-> Suspended
	1. osKernelSuspend() is called
	2. osKernelResume() is called

Scheduler can pick **ANY** task that it wants to perform next, it is undefined. 
This is the ***Scheduling Policy***

Generally tasks never terminate - a task can be terminated but its not frequently used.

When a task is GIVING something - its signaling a resource
When a task is DELAYED - its waiting for a resource