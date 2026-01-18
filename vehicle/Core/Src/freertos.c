/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SDCardTask */
osThreadId_t SDCardTaskHandle;
const osThreadAttr_t SDCardTask_attributes = {
  .name = "SDCardTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for FdCanTask */
osThreadId_t FdCanTaskHandle;
const osThreadAttr_t FdCanTask_attributes = {
  .name = "FdCanTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for VehicleTask */
osThreadId_t VehicleTaskHandle;
const osThreadAttr_t VehicleTask_attributes = {
  .name = "VehicleTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for Spi1Task */
osThreadId_t Spi1TaskHandle;
const osThreadAttr_t Spi1Task_attributes = {
  .name = "Spi1Task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh1,
};
/* Definitions for Dht11Task */
osThreadId_t Dht11TaskHandle;
const osThreadAttr_t Dht11Task_attributes = {
  .name = "Dht11Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartSDCardTask(void *argument);
void StartFdCanTask(void *argument);
void StartVehicleTask(void *argument);
void StartSpi1Task(void *argument);
void StartDht11Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of SDCardTask */
  SDCardTaskHandle = osThreadNew(StartSDCardTask, NULL, &SDCardTask_attributes);

  /* creation of FdCanTask */
  FdCanTaskHandle = osThreadNew(StartFdCanTask, NULL, &FdCanTask_attributes);

  /* creation of VehicleTask */
  VehicleTaskHandle = osThreadNew(StartVehicleTask, NULL, &VehicleTask_attributes);

  /* creation of Spi1Task */
  Spi1TaskHandle = osThreadNew(StartSpi1Task, NULL, &Spi1Task_attributes);

  /* creation of Dht11Task */
  Dht11TaskHandle = osThreadNew(StartDht11Task, NULL, &Dht11Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
__weak void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartSDCardTask */
/**
* @brief Function implementing the SDCardTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSDCardTask */
__weak void StartSDCardTask(void *argument)
{
  /* USER CODE BEGIN StartSDCardTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartSDCardTask */
}

/* USER CODE BEGIN Header_StartFdCanTask */
/**
* @brief Function implementing the FdCanTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFdCanTask */
__weak void StartFdCanTask(void *argument)
{
  /* USER CODE BEGIN StartFdCanTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartFdCanTask */
}

/* USER CODE BEGIN Header_StartVehicleTask */
/**
* @brief Function implementing the VehicleTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartVehicleTask */
__weak void StartVehicleTask(void *argument)
{
  /* USER CODE BEGIN StartVehicleTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartVehicleTask */
}

/* USER CODE BEGIN Header_StartSpi1Task */
/**
* @brief Function implementing the Spi1Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSpi1Task */
__weak void StartSpi1Task(void *argument)
{
  /* USER CODE BEGIN StartSpi1Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartSpi1Task */
}

/* USER CODE BEGIN Header_StartDht11Task */
/**
* @brief Function implementing the Dht11Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDht11Task */
__weak void StartDht11Task(void *argument)
{
  /* USER CODE BEGIN StartDht11Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDht11Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

