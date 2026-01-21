## Task States
1. Running -> Ready
	1. Running state can only have one task per CPU
	2. Preempted by scheduler
	3. Wait on signaled resource
	4. signal a resource
	5. Call osThreadYield()
2. Ready -> Running
	1. Selected by schedule
3. Running -> Blocked
	1. Wait on unsigned resource
4. Running -> Delayed
	1. Call osDelay()
	2. Call osDelayUntil()
5. Blocked -> Ready
	1. Resource is signaled
6. Delayed -> Ready
	1. Time Delay Expires