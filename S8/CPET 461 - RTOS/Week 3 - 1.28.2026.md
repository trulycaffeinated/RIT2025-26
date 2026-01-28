## Semaphore Example

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
In general RTOS will try to choose the task that was waiting the longest - it will create in essence a queue

Q - is it possible to achieve real-time (guaranteed temporal performance) without an RTOS?
A - Yes... firmware implementations can achieve real-time without an RTOS only for **simple systems**

A "Bare Metal" firmware design is an implementation where there is only one thread of execution, often called the **main loop**

```C
do {
	HAL_GPIO_TogglePin(<<GPIO PORT>>, <<GPIO PIN>);
	HAL_DELAY(1)_
```