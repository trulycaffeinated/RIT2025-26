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

