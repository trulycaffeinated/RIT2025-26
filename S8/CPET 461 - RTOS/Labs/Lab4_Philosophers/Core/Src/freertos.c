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
static int PhilosopherNum[NumPHIL];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void App_RTOS_Init(void);

static void startDefaultTask(void *argument);
static void PhilosopherTask(void *argument);

static bool GetLeftFork(int leftForkIndex);
static bool GetRightFork(int rightForkIndex);
static void putLeftFork(int leftForkIndex);
static void putRightFork(int rightForkIndex);

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
	for(int i = 0; i < NumPHIL; i++){
		PhilosopherNum[i] = i;
		osThreadNew(PhilosopherTask, i, &philAttr);
	}
}

static void startDefaultTask(void *argument){
	//Print_Line("RTOS Initialized");
	osThreadExit();
}

static void PhilosopherTask(void *argument)
{

    int id = *(int*)argument; // Pull Philosopher ID from arbitrary argument
	srand(id); // SEED Rand() with Philosopher ID - when removed, every philosopher has the same delays

    int desiredLeftFork  = id;
    int desiredRightFork = (id + NumPHIL - 1) % NumPHIL;

    bool gotLeft  = false;
    bool gotRight = false;

    while (1) // Begin state machine
    {

    	// MAX Value for delay
    	int ranMAX = 5;

        // Thinking state
        Print_Line("Philosopher %d - Thinking...", id);
        int ranNum = (rand() % ranMAX) + 1;
        Print_Line("Delay : %d", ranNum); // DEBUG LINE | DELAY
        osDelay(ranNum * 1000);

        // Hungry state
        Print_Line("Philosopher %d - Hungry...", id);
        while (!(gotLeft && gotRight))
        {

        	gotLeft = false;
        	gotRight = false;

        	// Randomize which fork is picked up first
            int randFork = rand() & 1;  // 0 or 1
            if (randFork == 0) {
                gotLeft  = GetLeftFork(desiredLeftFork);
                gotRight = GetRightFork(desiredRightFork);
            }
            else {
                gotRight = GetRightFork(desiredRightFork);
                gotLeft  = GetLeftFork(desiredLeftFork);
            }

            // Check forks
            if (gotLeft && !gotRight)
            {
                putLeftFork(desiredLeftFork);
                gotLeft = false;
            }

            if (gotRight && !gotLeft)
            {
                putRightFork(desiredRightFork);
                gotRight = false;
            }

            osDelay(10);
        }

        // Eat
        Print_Line("Philosopher %d - do I eat for I am hungry? Or because the creator said so?",id);
        ranNum = (rand() % ranMAX) + 1;
        Print_Line("Delay : %d", ranNum); // DEBUG LINE | DELAY
        osDelay(ranNum * 1000);
        putLeftFork(desiredLeftFork);
        putRightFork(desiredRightFork);
    } // End State Machine

    // Debug Section
    //Print_Line("Philosopher #: %d | Desired LF : %d | Desired Right Fork : %d",
    //           id, desiredLeftFork, desiredRightFork);
    //osThreadExit();
}


static bool GetLeftFork(int leftForkIndex){
	return(osSemaphoreAcquire(forkSemaphoreHandle[leftForkIndex], 0) == osOK);
}

static bool GetRightFork(int rightForkIndex){
	return(osSemaphoreAcquire(forkSemaphoreHandle[rightForkIndex], 0) == osOK);
}

static void putLeftFork(int leftForkIndex){
	osSemaphoreRelease(forkSemaphoreHandle[leftForkIndex]);
}

static void putRightFork(int rightForkIndex){
	osSemaphoreRelease(forkSemaphoreHandle[rightForkIndex]);
}
/* USER CODE END Application */

