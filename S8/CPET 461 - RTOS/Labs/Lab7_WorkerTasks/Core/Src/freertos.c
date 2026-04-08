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
#include "print.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define USE_MUTEX 1
#define LOW_WORK_ITERATIONS 8
#define LOW_WORK_DELAY_MS   250
#define MED_WORK_ITERATIONS 4
#define MED_WORK_DELAY_MS   500
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define numTasks 30
static int workerNum[numTasks];
volatile int tasksDone = 0;
uint32_t startTime = 0;
uint32_t endTime = 0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* Definitions for lowPriorityTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for checkIfPerfectT */
osThreadId_t checkIfPerfectTHandle;
const osThreadAttr_t checkIfPerfectT_attributes = {
  .name = "checkIfPerfectT",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

// Semaphore and Mutex

osMutexId_t workerDoneMutexHandle;
const osMutexAttr_t workerDoneMutex_attr = {
  .name = "workerDoneMutex"
};

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void App_RTOS_Init(void);

void StartDefaultTask(void *argument);
void StartWorkerTask(void *argument);

int isPerfect(int);
/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void App_RTOS_Init(void)
{
	Print_Init();

	workerDoneMutexHandle = osMutexNew(&workerDoneMutex_attr);

	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

	for (int i = 0; i < numTasks; i++) {
		workerNum[i] = i;
		checkIfPerfectTHandle = osThreadNew(StartWorkerTask, &workerNum[i], &checkIfPerfectT_attributes);
	}

}

void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
    while (1)
    {
        if (tasksDone == numTasks)
        {
            endTime = xTaskGetTickCount();

            uint32_t totalTime = endTime - startTime;

            Print_Line("Total time: %lu ticks", totalTime);

            // stop here so it doesn’t spam
            while (1);
        }

        osDelay(10);
    }
  /* USER CODE END 5 */
}

//---------------------------------------------//
// WORKER TASK
//---------------------------------------------//
void StartWorkerTask(void *argument)
{

	// worker ID to keep track of the workers
	int id = *(int*) argument;
	(void)id;

	Print_Line("Worker %d started...", id);
    for (int i = 0; i < (180 / numTasks); i++)
    {
        isPerfect(65530);
    }

    osMutexAcquire(workerDoneMutexHandle, osWaitForever);
    tasksDone++;
    osMutexRelease(workerDoneMutexHandle);

    osThreadExit();

}

int isPerfect(int n)
{
    if (n <= 1)
    {
        return 0;
    }

    int sum = 1;  // 1 is always a proper divisor for n > 1

    for (int i = 2; i <= n / 2; i++)
    {
        if ((n % i) == 0)
        {
            sum += i;
        }
    }

    return (sum == n);
}
/* USER CODE END Application */

