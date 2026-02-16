# Task Scheduling 4

**RM Scheduling** assigns static priorities to tasks at design time
All tasks must be strictly periodic, or can be modeled as periodic,
- modeling an aperiodic task as periodic requries that the minumum inter-arrival time of the task be known
- The inter-arrival time is time between any two successive times

Priorities are assigned inversely to periodicity
- if the RTOS supports strict numeric priorities, they are assigned proportional to execution frequency, but the exact values are not important, the relation between the priorities is what matters
- If the rtos has enumerated priori