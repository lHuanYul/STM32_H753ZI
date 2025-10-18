#include "connectivity/sdmmc/main.h"

#define CACHE_LINE_SIZE 32
#define ALIGN_UP(x) (((x) + CACHE_LINE_SIZE - 1) & ~(CACHE_LINE_SIZE - 1))

// __attribute__((section(".dma_nc"), aligned(32))) uint8_t sd_dma_wbuf[512];
// __attribute__((section(".dma_nc"), aligned(32))) uint8_t sd_dma_rbuf[512];
__attribute__((aligned(32))) uint8_t wbuf[8];
__attribute__((aligned(32))) uint8_t rbuf[8] = {0};
static const char msg[] = "HELLO";

static bool sd_wait_transfer(uint32_t ms)
{
    uint32_t t = 0;
    while (HAL_SD_GetCardState(sd_card.const_h.hsdx) != HAL_SD_CARD_TRANSFER) {
        osDelay(1);
        if (++t >= ms) return false;
    }
    return true;
}

uint32_t running = 0;
void StartSDCardTask(void *argument)
{
    while (retSD != 0);
    running = 1;
    sd_card.f_result = f_mount(&sd_card.fs, (TCHAR const*)SDPath, 1);
    while (sd_card.f_result != FR_OK);

    running = 2;
    sd_card.f_result = f_open(&sd_card.file, "test.txt", FA_OPEN_ALWAYS);
    while (sd_card.f_result != FR_OK);

    running = 3;
    sd_card.f_result = f_close(&sd_card.file);
    while (sd_card.f_result != FR_OK);
    osDelay(100);
    
    running = 4;
    sd_card.f_result = f_open(&sd_card.file, "test.txt", FA_OPEN_ALWAYS | FA_WRITE);
    while (sd_card.f_result != FR_OK);

    running = 5;
    memcpy(wbuf, msg, sizeof(msg));
    SCB_CleanDCache_by_Addr((uint32_t*)wbuf, ALIGN_UP(sizeof(msg)-1));

    running = 6;
    sd_card.f_result = f_write(&sd_card.file, wbuf, sizeof(msg)-1, &sd_card.bits);
    while (sd_card.f_result != FR_OK && !sd_wait_transfer(2000));

    running = 7;
    sd_card.f_result = f_sync(&sd_card.file);
    while (sd_card.f_result != FR_OK && !sd_wait_transfer(2000));

    running = 8;
    sd_card.f_result = f_close(&sd_card.file);
    while (sd_card.f_result != FR_OK);
    osDelay(100);

    running = 9;
    sd_card.f_result = f_open(&sd_card.file, "test.txt", FA_OPEN_ALWAYS | FA_READ);
    while (sd_card.f_result != FR_OK);

    running = 10;
    SCB_InvalidateDCache_by_Addr((uint32_t*)rbuf, ALIGN_UP(sizeof(rbuf)));

    running = 11;
    sd_card.f_result = f_read(&sd_card.file, rbuf, sizeof(msg)-1, &sd_card.bits);
    while (sd_card.f_result != FR_OK);

    running = 12;
    sd_card.f_result = f_close(&sd_card.file);
    while (sd_card.f_result != FR_OK);

    running = 20;
    sd_card.f_result = f_mount(NULL, "", 0);
    while (sd_card.f_result != FR_OK);

    for(;;)
    {
        osDelay(1000);
        running++;
    }
}
