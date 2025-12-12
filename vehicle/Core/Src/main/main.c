#include "main/main.h"

// #define DEFALT_TASK_DELAY_MS 50
// uint32_t defalt_running;
// void StartDefaultTask(void *argument)
// {
//     const uint32_t osPeriod = pdMS_TO_TICKS(DEFALT_TASK_DELAY_MS);
//     uint32_t next_wake = osKernelGetTickCount() + osPeriod;
//     for(;;)
//     {
//         defalt_running = HAL_GetTick();
//         osDelayUntil(next_wake);
//         next_wake += osPeriod;
//     }
//     osThreadExit();
// }
