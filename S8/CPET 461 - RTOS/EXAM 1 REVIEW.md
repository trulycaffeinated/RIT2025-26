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
5. Suspend is available - but is considered poor design. As suspended states break determinism, external control interferes with schedular. **suspended tasks break the ability for the rtos to guarantee a task is completed by deadlines**

States
1. Ready
	1. All tasks are created "Ready" to run
	2. There must always be something running on the CPU - so other tasks will sit as "ready" "blocked" or "delayed"
2. Running
	1. Running state can only have one task per cpu core
	2. There must always be something running on the CPU - so there is often a "null" task which does nothing but keeps the cpu occupied until another task is ready
	3. Only one thing can be running due to the CPU core only being able to execute one stream of instructions (thread) at a time
3. Blocked
	1. Waiting on an unsigned resource
	2. Something the task wants is not available
	3. Blocked tasks do not automatically become the next task in queue
4. Delayed
	1. osDelay()
	2. osDelayUntil()

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


An RTOS **MUST** support multitasking
- Multitasking is not a pre-req for an application to be real-time; many Embedded real time systems have been built as single-threaded but there are significant limits to the scope of such applications, i.e., only the simplest real-time applications can be implemented with a single task model

With multitasking comes the requirements that the RTOS provide a means for the tasks to communicate with each other and to manage resources
- Basically, a means to control the singled threaded execution is needed so that no application is executing a block of code or accessing a resource that another application is also executing or accessing.

An RTOS must provide a mechanism where multiple tasks can appear to be executing in parallel, even though the underlying processor hardware only supports executing a single task at a time

**COUNTING SEMAPHORE**

# H5
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
**NULL TASK IS USED TO KEEP THE CPU DOING STUFF - AS THE CPU MUST ALWAYS BE DOING *SOMETHING***

Can Bare Metal systems achieve real time? - Yes some firmware implementations can achieve real time but it's restricted to very simple systems. 

Bare Metal - one thread of execution, typically a main() loop

Can we achieve any parallelism? Yes we can as we can use an ISR to interrupt the main loop and achieve parallelism
- this causes the state of the previous GPIO to remain high until the ISR clears - hence why we use semaphores

Semaphores prevent the issues with bare metal and ISR's
- Values being lost 
- Unwanted variability
- main() being interrupted

With semaphores, you want to...
1. Own the lock (down())
2. Copy the private variable protected by the semaphore locally
3. Release the lock (up())

# Multitasking
**Cooperative** (Simple RTOS design)
- Tasks must be designed considering how they will ensure that all other tasks are allowed to execute when they need to - 
- Tasks almost never get a "fair" share of the CPU
- Adding a task to the application might require re-designing of the other tasks
*tasks decide when to give up cpu via delays*

**Preemptive** (More Complicated RTOS design (barely))
- Tasks can be designed considering how they will interact with other tasks but not whether the other tasks will execute when they need to
- Tasks always get a "fair" share of the cpu
- adding a task to the application only requires re-design of other tasks to the degree they interact 
*rtos decides when to give up the cpu via the scheduler and scheduler policy*
# **$Utilization = n \times (2^{\frac{1}{n}} - 1)$

As n approaches infinity utilization goes to 70% (69.3)

Whether a task is **compute bound** or **io bound** 
- IO bound tasks are typically low priority
- Compute tasks use a lot of CPU so they are given higher priority 

# Scheduling
**Rate Monotonic Scheduling** - assigns static priorities to tasks at design time - priorities are assigned **inversely** to periodicity 
i.e. *TASK THAT EXECUTES THE MOST FREQUENTLY HAS THE HIGHEST PRIORITY*
Guarantees that tasks will hit their deadlines

**Rate Monotonic Analysis**
Example...

| TASK   | WCETE | PERIOD |
| ------ | ----- | ------ |
| Task 1 | 2msec | 20msec |
| Task 2 | 3msec | 9msec  |
| Task 3 | 6msec | 25msec |
CPU utilization max is defined as $Util_{max} = n \times (2^{\frac{1}{n}} - 1)$ which we call $ln(2) = 69.314\%$
current CPU Utilization is defined as 
$\displaystyle\sum_{k=1}^n \frac{WCET_k}{Period_k}$ = $\frac{WCET_{T1}}{Period_{T1}} + \frac{WCET_{T2}}{Period_{T2}} + \frac{WCET_{T3}}{Period_{T3}}$ = $\frac{2}{20} + \frac{3}{9} + \frac{6}{25}$ = 67.33%

67.3 < 69.314 so we are good - the three tasks here pass Rate Monotonic Analysis and so they will all meet their deadlines


**Earliest Deadline First Scheduler** - Also known as the *Clairvoyant scheduler* -  causes the task with the closest deadline to have the highest priority so that it finishes on time before it's deadline.
Issue is that it's difficult to implement as the scheduler must know the tasks deadlines, which means the tasks must know the deadlines when they're preempted by the scheduler  - which is difficult because the task does not know when the scheduler will preempt the task.
Alternatively...
The RTOS can make this decision whenever it considers switching to a new task, however this is difficult because the RTOS has no way of knowing what a task was doing or what it will do next!

The RTOS must support **Periodic Construct** - an API function to allow a periodic task to specify it's period (which FreeRTOS does not support)

The RTOS must infer or be told the deadline for EDFS to work! Which is a very difficult thing to do.

# Priorities
**Round Robin Scheduler** is typically considered fair because all tasks get to execute and no one task or group of tasks hog the CPU - however this is only true for tasks of the same priority group

RTOS's support the ability for tasks to have different priorities

**Priority Inversion** -the situation when a higher priority task is prevented from executing because a lower priority task is executing *with which it does not interact*

A higher priority task is blocked by a lower priority task happens all the time with tasks that interact with each other, and its a natural part of task interaction
- Such as a higher priority task waiting on a semaphore signaled by a lower priority task

However, having application tasks with different priorities creates the possibility that a task will starve due to *priority inversion*
![[Pasted image 20260222183753.png]]

Take this diagram...
Task 1 is the highest priority but is blocked from completing its task by the other tasks as it needs the shared resource.
Task 3 has the shared resource taken via a ``down()``
Task 2, a higher priority task than 3 takes the CPU but doesn't need the resource so it runs to completion - task 3 is now blocked
Task 1 cannot overtake Task 2 because Task 3 has the resource which is blocked, this is **priority inversion** - as task 2 is taking the CPU despite it being a lower priority and not interacting with resources task 1 needs
Once task 2 is completed task 3 may resume 
Task 3 completes its task, releasing the resource via ``up()``
Task 1 can now be completed LAST
**This is unbound priority inversion and it has four conditions**
1. There must be at least three tasks
2. There must be at least three different priorities
3. A high priority task must interact with a low priority task
4. There must be at least one task with a priority in-between the two interacting low/high priority tasks

This is unbounded because the intermediate priority can prevent the high priority task from executing *forever*

![[Pasted image 20260222184220.png]]
Task 3 (low priority) locks a shared resource
Task 1 (high priority) attempts a ``down()`` on the shared resource but cannot -- Task 3 is now changed from low priority to *high* priority
Task 2 (med priority) is ready to execute but is blocked by the now high priority task 3
Task 3 finishes its use of the resource, and performs an ``up()`` -- and is reverted back to low priority
Task 1 performs a ``down()`` and runs to completion before ``up()``
Task 2 runs to completion

**This is bounded priority inversion** - as the low priority task *inherits* the high priority to ensure the intermediate priority tasks do not execute
- Has the same characteristics/conditions as unbounded priority inversion 

**Priority Inheritance** - The process by which the priority of a task is increased when a higher priority task attempts to lock a resource, and its priority is restored when it releases the resource
Implementing Priority inheritance can be computationally expensive because every time that any resource is locked there is the potential for the priority of a task to be changed, to do that the RTOS must keep track of which tasks have what resources at all times

Many RTOS's only implement priority inheritance with *mutexes* (binary semaphore)

## What happens if a periodic task’s execution time exceeds its period?

Answer:
- Deadline miss.
- Task consumes future CPU time. 
- **System is no longer real-time.**
## Why is a semaphore sometimes used for synchronization instead of mutual exclusion?

Answer
- **Used to signal events between tasks.**
- **Not protecting data but coordinating execution order.**

## Why is cooperative behavior still required in a preemptive RTOS?

Expected insight:
- Tasks still block, delay, and signal resources.
- Preemption alone cannot guarantee correct interaction.
- RTOS operation is cooperative + preemptive.
**A Task in the RTOS still has the ability to block, delay, and signal a mutex - therefore the scheduler needs to be able to respond to this and not sit idle when an event occurs**

Can't hold semaphores due to **blocking higher priority tasks (priority inversion risk)**

Interrupts vs RTOS - key word of determinism. Interrupts occur at unpredictable times and complicate timi