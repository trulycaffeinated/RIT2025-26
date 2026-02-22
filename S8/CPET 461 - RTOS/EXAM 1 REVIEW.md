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

Tasks can enter a state called **deadlock** in which they are waiting for a resource that will never be available.

If there are no tasks that are ready to run when the RTOS starts it will crash (i.e. when no tasks are created)

Tasks will never end, all tasks should be infinite loops with the exception of default task which should terminate itself asap

Most operating systems don't allow arguments to be passed to the RTOS tasks
![[Pasted image 20260222121103.png]]
Each task is represented by a parallelogram 
Interactions between tasks are represented by arrows which connect to "sockets"
- Connections to hardware are simple arrows without socks
- Complex diagrams, where tasks interact, the socket characteristics become critical to design and to understanding the task interaction

# H4
Memorize this chart

| Step | **Task A**                                                                                                                              | **Task B**                                                                                                                                               |
| ---: | --------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
|    1 | Performs a `down()` operation, decrementing the semaphore to **0**                                                                      | —                                                                                                                                                        |
|    2 | —                                                                                                                                       | Executes and performs a `down()` operation (after Task A’s `down()` and before Task A’s `up()`). Because the semaphore is **0**, Task B is **suspended** |
|    3 | Begins **sole access** to the shared resource                                                                                           | —                                                                                                                                                        |
|    4 | Completes sole access to the shared resource                                                                                            | —                                                                                                                                                        |
|    5 | Performs an `up()` operation. Because a task is waiting, the semaphore is **not incremented**; instead, Task B is made **ready to run** | The `up()` performed by Task A completes Task B’s pending `down()` and **transfers sole access** of the shared resource to Task B                        |
|    6 | —                                                                                                                                       | Executes and begins sole access to the shared resource                                                                                                   |
|    7 | —                                                                                                                                       | Completes sole access to the shared resource                                                                                                             |
|    8 | —                                                                                                                                       | Performs an `up()` operation, incrementing the semaphore to **1**, allowing another task to acces                                                        |
Real Time applications are all about timeliness 
there are three types of applications
- Non-Real-Time
- Soft Real-Time
- Hard Real-Time

A temporal requirement is considered a deadline when the terminal event of the requirement is something that the software must perform
A temporal requirement is considered a constraint when the software must interact with the hardware within timing limitations defined by the hardware
![[Pasted image 20260222121950.png]]

Basic functions of an RTOS are no different than a traditional operating system
- Manage access to (scarce) hardware resources
- Establish and enforce fairness regarding how resources are shared
- Provide primitive functions which cannot be provided by application code
- Provide these services with minimal performance overhead

**An RTOS guarantees performance where a traditional OS does not**

Idea is to guarantee performance by identifying the "worst case" performance scenario which is then used as the performance guarantee

There is no guarantee in an RTOS to be fast - there is only the guarantee on performance
- Even if an application is "fast" it does not mean that it is real-time - real-time is only guaranteed by proving the temporal timing
