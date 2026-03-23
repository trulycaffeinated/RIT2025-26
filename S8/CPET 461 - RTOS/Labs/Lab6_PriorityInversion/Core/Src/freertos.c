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
#include "cmsis_os.h"

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
#define LOW_WORK_DELAY_MS   50
#define MED_WORK_ITERATIONS 12
#define MED_WORK_DELAY_MS   50
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

static osThreadId_t lowTaskHandle;
static osThreadId_t medTaskHandle;
static osThreadId_t highTaskHandle;

static const osThreadAttr_t lowTask_attributes = {
  .name = "lowTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

static const osThreadAttr_t medTask_attributes = {
  .name = "medTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

static const osThreadAttr_t highTask_attributes = {
  .name = "highTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};

#if USE_MUTEX
static osMutexId_t sharedLockHandle;
static const osMutexAttr_t sharedLock_attributes = {
  .name = "sharedLock"
};
#else
static osSemaphoreId_t sharedLockHandle;
static const osSemaphoreAttr_t sharedLock_attributes = {
  .name = "sharedLock"
};
#endif

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void App_RTOS_Init(void);

static void StartLowTask(void *argument);
static void StartMedTask(void *argument);
static void StartHighTask(void *argument);
/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void App_RTOS_Init(void)
{
  Print_Init();

#if USE_MUTEX
  Print_Line("=== Lab 6: MUTEX run ===");
  sharedLockHandle = osMutexNew(&sharedLock_attributes);
#else
  Print_Line("=== Lab 6: BINARY SEMAPHORE run ===");
  sharedLockHandle = osSemaphoreNew(1, 1, &sharedLock_attributes);
#endif

  if (sharedLockHandle == NULL)
  {
    Print_Line("ERROR: shared lock creation failed");
    Error_Handler();
  }

  lowTaskHandle = osThreadNew(StartLowTask, NULL, &lowTask_attributes);
  if (lowTaskHandle == NULL)
  {
    Print_Line("ERROR: low task creation failed");
    Error_Handler();
  }

  medTaskHandle = osThreadNew(StartMedTask, NULL, &medTask_attributes);
  if (medTaskHandle == NULL)
  {
    Print_Line("ERROR: med task creation failed");
    Error_Handler();
  }

  highTaskHandle = osThreadNew(StartHighTask, NULL, &highTask_attributes);
  if (highTaskHandle == NULL)
  {
    Print_Line("ERROR: high task creation failed");
    Error_Handler();
  }
}

static void StartLowTask(void *argument)
{
  (void)argument;

  Print_Line("LOW: starting");
  Print_Line("LOW: attempting to acquire shared resource");

#if USE_MUTEX
  osMutexAcquire(sharedLockHandle, osWaitForever);
#else
  osSemaphoreAcquire(sharedLockHandle, osWaitForever);
#endif

  Print_Line("LOW: acquired shared resource");

  for (int i = 1; i <= LOW_WORK_ITERATIONS; i++)
  {
    Print_Line("LOW: working %d/%d", i, LOW_WORK_ITERATIONS);
    Print_Line("LOW: tick before delay = %lu", HAL_GetTick());
    HAL_Delay(LOW_WORK_DELAY_MS);
    Print_Line("LOW: tick after delay = %lu", HAL_GetTick());
  }

  Print_Line("LOW: releasing shared resource");

#if USE_MUTEX
  osMutexRelease(sharedLockHandle);
#else
  osSemaphoreRelease(sharedLockHandle);
#endif

  Print_Line("LOW: done");

  for (;;)
  {
    osDelay(1000);
  }
}

static void StartHighTask(void *argument)
{
  (void)argument;

  /* Let LOW start first and take the resource */
  osDelay(100);

  Print_Line("HIGH: starting");
  Print_Line("HIGH: attempting to acquire shared resource");

#if USE_MUTEX
  osMutexAcquire(sharedLockHandle, osWaitForever);
#else
  osSemaphoreAcquire(sharedLockHandle, osWaitForever);
#endif

  Print_Line("HIGH: acquired shared resource");
  Print_Line("HIGH: tick before delay = %lu", HAL_GetTick());
  HAL_Delay(100);
  Print_Line("HIGH: tick after delay = %lu", HAL_GetTick());

  Print_Line("HIGH: releasing shared resource");

#if USE_MUTEX
  osMutexRelease(sharedLockHandle);
#else
  osSemaphoreRelease(sharedLockHandle);
#endif

  Print_Line("HIGH: done");

  for (;;)
  {
    osDelay(1000);
  }
}

static void StartMedTask(void *argument)
{
  (void)argument;

  /* Start after HIGH has already blocked on LOW's lock */
  osDelay(150);

  Print_Line("MED: starting");

  for (int i = 1; i <= MED_WORK_ITERATIONS; i++)
  {
    Print_Line("MED: running %d/%d", i, MED_WORK_ITERATIONS);
    Print_Line("MED: tick before delay = %lu", HAL_GetTick());
    HAL_Delay(MED_WORK_DELAY_MS);
    Print_Line("MED: tick after delay = %lu", HAL_GetTick());
  }

  Print_Line("MED: done");

  for (;;)
  {
    osDelay(1000);
  }
}

/* USER CODE END Application */
