#include "connectivity/sdmmc/main.h"
#include "fatfs.h"

FATFS fs;
FIL file;
UINT bw;
FRESULT res;

uint32_t running = 0;
void StartSDCardTask(void *argument)
{
    while (retSD != 0);
    running = 1;
    res = f_mount(&fs, (TCHAR const*)SDPath, 0);
    osDelay(1000);
    res = f_open(&file, "test.txt", FA_CREATE_ALWAYS | FA_WRITE);
    for(;;)
    {
        // if (sd_card.const_h.hsdx->State == HAL_SD_STATE_RESET)
        //     sd_card.result = HAL_SD_Init(sd_card.const_h.hsdx);
        // sd_card.state = HAL_SD_GetCardState(sd_card.const_h.hsdx);
        // if (
        //        (sd_card.state != HAL_SD_CARD_TRANSFER)
        //     || (sd_card.const_h.hsdx->ErrorCode != HAL_SD_ERROR_NONE)
        // ) {
        //     discon++;
        //     HAL_SD_DeInit(sd_card.const_h.hsdx);
        //     sd_card.result = HAL_SD_Init(sd_card.const_h.hsdx);
        // }
        osDelay(1000);
        running++;
    }
    f_mount(NULL, "", 0);
}
