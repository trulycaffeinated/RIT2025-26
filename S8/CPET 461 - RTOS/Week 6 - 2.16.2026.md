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

The tasks are schedulable using RM Scheduling if the calculated utiliation is less than the maximum allowed utilization
$Util_{Max} = n \times (2^{1/n}-1)$
in the limit as n -> infinity 
Utilization max = ln(2) ie. 69.314%

We're kinda wasting around 30% of the CPU, and we're assuming we have an infinite number of tasks which is unrealistic 

We can always substitute $n$ with the number of tasks we have

**The more tasks we have, the more free cpu there needs to be to handle those tasks**

# Exam Review Questions
**MONDAY the 23RD!!!**

## How to make a task Diagram?
Task is represented by parallelogram - give a name.
Variable is a rectangle (can be represented differently) - label at the top if its protected by some thing
Inside parallelogram but a smaller parallelogram to represent semaphore on edge of task, arrow from semaphore to variable to show task uses that semaphore to access that variable.
Variables protected by the same semaphore should be in the same block, different semaphores are different blocks
Piece of hardware like the UART will have an arrow from the device to a task **HARDWARE CAN ONLY BE ATTACHED TO ONE TASK**