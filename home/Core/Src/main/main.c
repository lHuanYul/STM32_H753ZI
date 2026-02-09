#include "main/main.h"
#include "HY_MOD/vehicle/basic.h"
#include "HY_MOD/main/tim.h"

void INIT_OWN(void)
{
    INIT_OWN_TIM();
}

#include "main/fdcan.h"
#include "HY_MOD/fdcan/callback.h"
#include "HY_MOD/dht/callback.h"

void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs)
{
    fdcan_error_status_cb(&fdcan_h, hfdcan, ErrorStatusITs);
}

void HAL_FDCAN_TxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs)
{
    fdcan_tx_fifo_cb(&fdcan_h, hfdcan, TxEventFifoITs);
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    fdcan_rx_fifo0_cb(&fdcan_h, hfdcan, RxFifo0ITs, &fdcan_pkt_pool, &fdcan_recv_pkt_buf);
}

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    fdcan_rx_fifo1_cb(&fdcan_h, hfdcan, RxFifo1ITs);
}

#include "main/spi_json.h"
#include "HY_MOD/spi/callback.h"

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_tx_rx_cb(&spi1_h.spi_p, hspi);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_rx_cb(&spi1_h.spi_p, hspi);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_tx_cb(&spi1_h.spi_p, hspi);
}

#include "main/dht.h"
#include "HY_MOD/dht/callback.h"

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    dht_tim_IC_cb(&dht_h, htim);
}

#include "usb_device.h"
#include "main/rbytes.h"
#include "HY_MOD/usb_otg/basic.h"
#include "HY_MOD/packet/raw_bytes.h"

#define DEFALT_TASK_DELAY_MS 1000
uint32_t default_running;
void StartDefaultTask(void *argument)
{
    rbytes_pkt_pool_init(&rbytes_pkt_pool);
    RBytesPkt *pkt = RESULT_UNWRAP_HANDLE(rbytes_pkt_pool_alloc(&rbytes_pkt_pool));
    usb_otg_h.rx_pkt = pkt;
    pkt = RESULT_UNWRAP_HANDLE(rbytes_pkt_pool_alloc(&rbytes_pkt_pool));
    usb_otg_h.tx_pkt = pkt;
    MX_USB_DEVICE_Init();
    const uint32_t osPeriod = pdMS_TO_TICKS(DEFALT_TASK_DELAY_MS);
    uint32_t next_wake = osKernelGetTickCount() + osPeriod;
    for (;;)
    {
        default_running = HAL_GetTick();
        osDelayUntil(next_wake);
        next_wake += osPeriod;
    }
}
