# Periodic Tasks
We will often need to create tasks that execute periodically, we have seen that in Labs 2 & 3, and we will see it going forward

Some RTOS's provide a mechanism to easily create a periodic task where the RTOS periodically signals a semaphore
- The body of the task waits on the semaphore at the top of an infinite loop
- The RTOS is responsible for ensuring that the semaphore is signaled precisely at the periodic rate
Free RTOS does not have this capability

Fortunately there is a design pattern that we can use to e