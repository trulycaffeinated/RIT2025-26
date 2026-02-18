# Task Scheduling 4

**RM Scheduling** assigns static priorities to tasks at design time
All tasks must be strictly periodic, or can be modeled as periodic,
- modeling an aperiodic task as periodic requries that the minumum inter-arrival time of the task be known
- The inter-arrival time is time between any two successive times

Priorities are assigned inversely to periodicity
- if the RTOS supports strict numeric priorities, they are assigned proportional to execution frequency, but the exact values are not important, the relation between the priorities is what matters
- If the RTOS has enumerated priorities (like freeRTOS) they are assigned so that the task that executes most frequently (smallest period) has the highest priority, next most frequently has the next lower priority, etc.

Tasks of the same period will be given the same priority, and round-robin scheduling will be used with such tasks

**RM Scheduling** guarantees tasks will hit their deadlines

For each collection of tasks, we need to know each task's period and worst-case execution time (WCET)
- Task 1 - executes for not more than 2msec every 2msec
- Task 2 - executes for not more than 3msec with an inter-arrival time of 9, 12,18 and 20msec
- Task 3 - executes for not more than 6msec every 25msec

| TASK   | WCETE | PERIOD |
| ------ | ----- | ------ |
| Task 1 | 2msec | 20msec |
| Task 2 | 3msec | 9msec  |
| Task 3 | 6msec | 25msec |
We can measure WCET by setting a GPIO pin high at task start, and low at task completion and measuring with an oscilloscope\
- Complex code will have a variable runtimes, so measuring WCET could take awhile to properly determine

Compute Utilization of the CPU with the WCET of the tasks

The tasks are schedulable using RM Scheduling if the calculated utilization is less than the maximum allowed utilization
$Util_{Max} = n \times (2^{1/n}-1)$
in the limit as n -> infinity 
Utilization max = ln(2) ie. 69.314%

We're kinda wasting around 30% of the CPU, and we're assuming we have an infinite number of tasks which is unrealistic 

We can always substitute $n$ with the number of tasks we have

**The more tasks we have, the more free cpu there needs to be to handle those tasks**

# Task Scheduling 5
**Earliest Deadline First Scheduler** - causes the task which must complete some operation nearest in the future to be scheduled next. **(Clairvoyant Scheduler) - sees what the future needs**

The RTOS must chose the task to execute next which hsa the earliest future deadline
- EDFS allows processor utilization to reach 100%
	- Recall that utilization = $\displaystyle\sum_{k=1}^n(\frac{WCET}{Period})$
	- For RMS
		- Utilization = $U_{max} = n \times (2^{\frac{1}{n}}-1)$
	- Allowing the CPU to be as high as 100% is a tremendous improvement
		- this could allow us to use a slower, cheaper processor

How do we know which task has a deadline in the early future?

Two ways...
at each scheduling decision...
	deadlines for all tasks must be considered
- Either
	- When tasks are preempted the task must be able to describe its future deadline - this is difficult because the task can't know when the RTOS will preempt it
- or
	- That determination must be made by the RTOS whenever it considers switching to a new task - this difficult because the RTOS has no way of knowing what the application was doing or what it will do next

These two functions are how we do this
```C
void EDF_NextDeadlineAbsolute(uint32_t ticks);
// or
void EDF_NextDeadlineRelative(uint32_t ticks);
```
Only works with periodic tasks

otherwise the RTOS can do it
The RTOS must infer the deadline from some information about the task
We will have the RTOS know the periods of every task

in FreeRTOS this isn't the case - we construct periodic tasks using functions FreeRTOS provides. But FreeRTOS doesn't know why we're using those functions. There are other RTOS software's that let the task convey it's periodicity to the scheduler/RTOS. 

Note : FreeRTOS does not support EDFS

If our CPU Utilization for our tasks is greater than the allowed value, we MUST use EDFS otherwise we cannot run the system - only other option is getting a better faster more expensive CPU.


# Exam Review Questions
**MONDAY the 23RD!!!**
Don't write any code to answer a question
## How to make a task Diagram?
Task is represented by parallelogram - give a name.
Variable is a rectangle (can be represented differently) - label at the top if its protected by some thing
Inside parallelogram but a smaller parallelogram to represent semaphore on edge of task, arrow from semaphore to variable to show task uses that semaphore to access that variable.
Variables protected by the same semaphore should be in the same block, different semaphores are different blocks
Piece of hardware like the UART will have an arrow from the device to a task **HARDWARE CAN ONLY BE ATTACHED TO ONE TASK**

## Would you say a good majority of the information from slides, textbooks or labs?
The slides should be used more as a refresher, syllabus will have textbook references which we should read.
Labs are made as a way to perform operations - if we go through labs and you understand what they do, then we understand the topics.

## No IDE Specific questions