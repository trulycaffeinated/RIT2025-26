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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* Definitions for lowPriorityTask */
osThreadId_t lowPriorityTaskHandle;
const osThreadAttr_t lowPriorityTask_attributes = {
  .name = "lowPriorityTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for medPriorityTask */
osThreadId_t medPriorityTaskHandle;
const osThreadAttr_t medPriorityTask_attributes = {
  .name = "medPriorityTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for highPriorityTask */
osThreadId_t highPriorityTaskHandle;
const osThreadAttr_t highPriorityTask_attributes = {
  .name = "highPriorityTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};

// Semaphore and Mutex

#if USE_MUTEX
osMutexId_t sharedLockHandle;
const osMutexAttr_t sharedLock_attr = {
  .name = "sharedLock"
};
#else
osSemaphoreId_t sharedLockHandle;
const osSemaphoreAttr_t sharedLock_attr = {
  .name = "sharedLock"
};
#endif

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void App_RTOS_Init(void);

void StartLowTask(void *argument);
void StartMedTask(void *argument);
void StartHighTask(void *argument);
/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void App_RTOS_Init(void)
{
	Print_Init();

	// Use pre-processing if statement to avoid warnings
	#if USE_MUTEX
		Print_Line("===== LAB 6 RUNNING W/ MUTEX =====");
		sharedLockHandle = osMutexNew(&sharedLock_attr);
		Print_Line("Mutex Handle : %p", sharedLockHandle);
	#else
		Print_Line("===== LAB 6 RUNNING W/ SEMAPHORE =====");
		sharedLockHandle = osSemaphoreNew(1, 1, &sharedLock_attr);
		Print_Line("Semaphore Handle : %p", sharedLockHandle);
	#endif

    if(sharedLockHandle == NULL){
    	Print_Line("Failed to create mutex/semaphore");
    	Error_Handler();
    }

    lowPriorityTaskHandle = osThreadNew(StartLowTask, NULL, &lowPriorityTask_attributes);
    medPriorityTaskHandle = osThreadNew(StartMedTask, NULL, &medPriorityTask_attributes);
    highPriorityTaskHandle = osThreadNew(StartHighTask, NULL, &highPriorityTask_attributes);

    if(lowPriorityTaskHandle == NULL || medPriorityTaskHandle == NULL || highPriorityTaskHandle == NULL){
    	Print_Line("Failed to create tasks...");
    	Error_Handler();
    }

}
//---------------------------------------------//
// LOW PRIORITY TASK
//---------------------------------------------//
void StartLowTask(void *argument)
{
	Print_Line("LOW: starting");
	Print_Line("LOW: Acquiring shared resource");
	#if USE_MUTEX
		osMutexAcquire(sharedLockHandle, osWaitForever);
	#else
		osSemaphoreAcquire(sharedLockHandle, osWaitForever);
	#endif
	Print_Line("LOW: acquired shared resource");

  // CPU IS WORKING - SHOULD NOT GET INTERRUPTED WHEN USE_MUTEX IS 1
	for (int i = 1; i <= LOW_WORK_ITERATIONS; i++)
	{
		for(int j = 1; j <= 500000; j++) {}
	}

	Print_Line("LOW: releasing shared resource - done");
	#if USE_MUTEX
	  osMutexRelease(sharedLockHandle);
	#else
	  osSemaphoreRelease(sharedLockHandle);
	#endif


	for (;;)
	{
		// process is done
		osDelay(1000);
	}
}
//---------------------------------------------//
// HIGH PRIORITY TASK
//---------------------------------------------//
void StartHighTask(void *argument)
{
  /* Let LOW start first and take the resource */
	  osDelay(100);

	  Print_Line("HIGH: starting");

  // LOW PRIORITY TASK HAS SHARED RESOURCE AT THE TIME, SHOULD DELAY HIGH PRIORITY TASK UNTIL LOW IS DONE
	  Print_Line("HIGH: Acquiring shared resource");
	#if USE_MUTEX
		osMutexAcquire(sharedLockHandle, osWaitForever);
	#else
		osSemaphoreAcquire(sharedLockHandle, osWaitForever);
	#endif
		Print_Line("HIGH: Acquired shared resource");


	HAL_Delay(1000);

	Print_Line("HIGH: releasing shared resource - done");

	#if USE_MUTEX
	  osMutexRelease(sharedLockHandle);
	#else
	  osSemaphoreRelease(sharedLockHandle);
	#endif

  for (;;)
  {
	  // process is done
		osDelay(1000);
  }
}

//---------------------------------------------//
// MEDIUM PRIORITY TASK
//---------------------------------------------//
void StartMedTask(void *argument)
{
  // Starts after low, and after high
  osDelay(200);

  Print_Line("MED: starting");

  for (int i = 1; i <= MED_WORK_ITERATIONS; i++)
  {
    Print_Line("MED: running %d/%d", i, MED_WORK_ITERATIONS);
    HAL_Delay(MED_WORK_DELAY_MS);
  }

  Print_Line("MED: done");

  for (;;)
  {
	  // process is done
	  osDelay(1000);
  }
}

/* USER CODE END Application */

