#include "connectivity/sdmmc/main.h"

uint32_t running = 0;
void StartSDCardTask(void *argument)
{
    while (retSD != 0);
    running = 1;
    sd_card.f_result = f_mount(&sd_card.fs, (TCHAR const*)SDPath, 0);
    osDelay(1000);
    running = 2;
    sd_card.f_result = f_open(&sd_card.file, "test.txt", FA_CREATE_ALWAYS | FA_WRITE);
    for(;;)
    {
        
        osDelay(1000);
        running++;
    }
    f_mount(NULL, "", 0);
}
