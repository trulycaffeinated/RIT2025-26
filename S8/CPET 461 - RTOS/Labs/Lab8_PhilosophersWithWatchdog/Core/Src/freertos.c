/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include "print.h"
#include <stdlib.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define NumPHIL 8
const osThreadAttr_t defaultAttr = {
    .name       = "defaultTask",
    .stack_size = 1024 * 4,    // bytes (2 KB)
    .priority   = osPriorityNormal
};
const osThreadAttr_t philAttr = {
    .name       = "Philosopher",
    .stack_size = 1024 * 4,   // bytes (4 KB)
    .priority   = osPriorityLow
};
osSemaphoreId_t forkSemaphoreHandle[NumPHIL];
const osSemaphoreAttr_t forkSemaphore_attributes = {
		.name = "forkSemaphore"
};
const osThreadAttr_t watchdogAttr = {
    .name = "Watchdog",
    .stack_size = 1024 * 4,
    .priority = osPriorityHigh
};
static osSemaphoreId_t heartbeatSemaphoreHandle;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
typedef struct {
	bool inUse;
} fork_t;

static fork_t forks[NumPHIL];
static uint32_t lastKickTick[NumPHIL];
static int PhilosopherNum[NumPHIL];

extern IWDG_HandleTypeDef hiwdg; // this comes from main as it's initialized via the ioc
/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void App_RTOS_Init(void);

static void startDefaultTask(void *argument);
static void PhilosopherTask(void *argument);
static void WatchdogTask(void *argument);

static bool getFork(int forkIndex);
static void putFork(int forkIndex);

static void PhilosopherHeartbeat(int id);
/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void App_RTOS_Init(void){
	Print_Init();

	// Start Default Task - Print RTOS initialized, then close
	osThreadNew(startDefaultTask, NULL, &defaultAttr);



	// Make 8 forks for the 8 philosophers
	for(int i = 0; i < NumPHIL; i++){
		forkSemaphoreHandle[i] = osSemaphoreNew(1, 1, NULL);
	}

	// Make 8 Philosoper's (tasks)
	heartbeatSemaphoreHandle = osSemaphoreNew(1, 1, NULL);

	for(int i = 0; i < NumPHIL; i++){
	    forks[i].inUse = false;
	    lastKickTick[i] = osKernelGetTickCount();
	    PhilosopherNum[i] = i;
	    osThreadNew(PhilosopherTask, &PhilosopherNum[i], &philAttr);
	}

	osThreadNew(WatchdogTask, NULL, &watchdogAttr);
}

static void startDefaultTask(void *argument){
	//Print_Line("RTOS Initialized");
	osThreadExit();
}

static void PhilosopherTask(void *argument)
{

    int id = *(int*)argument; // Pull Philosopher ID from arbitrary argument
	srand(id); // SEED Rand() with Philosopher ID - when removed, every philosopher has the same delays. This avoids the RAND() bug

    int desiredLeftFork  = id;
    int desiredRightFork = (id + NumPHIL - 1) % NumPHIL;

    bool gotLeft  = false;
    bool gotRight = false;

    int ranNum;
    int ranMAX = 4001;

    while (1)
    {
        PhilosopherHeartbeat(id);
        Print_Line("Philosopher %d - Thinking...", id);
        ranNum = (rand() % ranMAX) + 1000;
        osDelay(ranNum);

        PhilosopherHeartbeat(id);
        Print_Line("Philosopher %d - Hungry...", id);

        while (!(gotLeft && gotRight))
        {
            PhilosopherHeartbeat(id);

            gotLeft = false;
            gotRight = false;

            gotLeft = getFork(desiredLeftFork);
            gotRight = getFork(desiredRightFork);

            if (gotLeft && !gotRight) {
                putFork(desiredLeftFork);
                gotLeft = false;
            }

            if (gotRight && !gotLeft) {
                putFork(desiredRightFork);
                gotRight = false;
            }

            osDelay(10);
        }

        PhilosopherHeartbeat(id);
        Print_Line("Philosopher %d - Eating...", id);
        ranNum = (rand() % ranMAX) + 1000;
        osDelay(ranNum);
        PhilosopherHeartbeat(id);

        putFork(desiredLeftFork);
        putFork(desiredRightFork);
    }

    // Debug Section
    //Print_Line("Philosopher #: %d | Desired LF : %d | Desired Right Fork : %d",
    //           id, desiredLeftFork, desiredRightFork);
    //osThreadExit();
}

static void WatchdogTask(void *argument)
{
    const uint32_t philosopherTimeoutMs = 2000; // when a philosopher is declared dead - 2s for a failure, 5s for a non failure
    const uint32_t watchdogCheckPeriodMs = 500; // how frequently the watchdog checks

    while(1)
    {
        bool allAlive = true;
        uint32_t now = osKernelGetTickCount();

        if(osSemaphoreAcquire(heartbeatSemaphoreHandle, HAL_MAX_DELAY) == osOK){
            for(int i = 0; i < NumPHIL; i++){
                uint32_t age = now - lastKickTick[i];
                if(age > philosopherTimeoutMs){
                    allAlive = false;
                }
            }
            osSemaphoreRelease(heartbeatSemaphoreHandle);
        }

        if(allAlive){
            Print_Line("Watchdog: all philosophers alive, kicking watchdog.");
            HAL_IWDG_Refresh(&hiwdg);
        } else {
            Print_Line("Watchdog: philosopher timeout detected, watchdog would reset board.");
            HAL_IWDG_Refresh(&hiwdg); // refreshing the timer since we're just simulating a reset
//            while(1){
//            	// wait for IWDG reset
//            }
        }

        osDelay(watchdogCheckPeriodMs);
    }
}

static bool getFork(int forkIndex){

    if(osSemaphoreAcquire(forkSemaphoreHandle[forkIndex], HAL_MAX_DELAY) == osOK) {
        if(forks[forkIndex].inUse == false) {
            forks[forkIndex].inUse = true;
            osSemaphoreRelease(forkSemaphoreHandle[forkIndex]);
            return true;
        }
        osSemaphoreRelease(forkSemaphoreHandle[forkIndex]);
    }
    return false;
}

static void putFork(int forkIndex){
	if(osSemaphoreAcquire(forkSemaphoreHandle[forkIndex], HAL_MAX_DELAY) == osOK){
		forks[forkIndex].inUse = false;
		osSemaphoreRelease(forkSemaphoreHandle[forkIndex]);
	}
}

static void PhilosopherHeartbeat(int id){
    if(osSemaphoreAcquire(heartbeatSemaphoreHandle, HAL_MAX_DELAY) == osOK){
        lastKickTick[id] = osKernelGetTickCount();
        osSemaphoreRelease(heartbeatSemaphoreHandle);
    }
}
/* USER CODE END Application */

