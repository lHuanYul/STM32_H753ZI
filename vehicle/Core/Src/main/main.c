#include "main/main.h"
#include "main/mod_cfg.h"
#include "vehicle/basic.h"
#include "HY_MOD/fdcan/callback.h"
#include "HY_MOD/spi_json/callback.h"
#include "fdcan.h"

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

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_json_rx_cb(&spi1_h, hspi, &json_pkt_pool, &spi_recv_buf);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_json_tx_cb(&spi1_h, hspi, &json_pkt_pool, &spi_trsm_buf);
}
