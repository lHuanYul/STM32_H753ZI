#include "main/mod_cfg.h"

#include "HY_MOD/fdcan/basic.h"
#include "HY_MOD/packet/fdcan.h"
#include "spi.h"

FdcanPktPool fdcan_pkt_pool;

static FdcanPkt* trsm_pkt_buf[FDCAN_TRSM_BUF_CAP];
FdcanPktBuf fdcan_trsm_pkt_buf = {
    .buf = trsm_pkt_buf,
    .cap = FDCAN_TRSM_BUF_CAP,
};

static FdcanPkt* recv_pkt_buf[FDCAN_RECV_BUF_CAP];
FdcanPktBuf fdcan_recv_pkt_buf = {
    .buf = recv_pkt_buf,
    .cap = FDCAN_RECV_BUF_CAP,
};

FdcanParametar fdcan_h = {
    .const_h = {
        .hfdcanx = &hfdcan1,
        // .rx = { .GPIOx = , .GPIO_Pin_x = },
        // .tx = { .GPIOx = , .GPIO_Pin_x = },
    },
};

SPI_DMA_BUFFER_ATTR static uint8_t rx_buf[ALIGN_32(JSON_PKT_LEN)];
SPI_DMA_BUFFER_ATTR static uint8_t tx_buf[ALIGN_32(JSON_PKT_LEN)];

SpiParametar spi1_h = {
    .const_h = {
        .hspix = &hspi1,
        .SCK  = {GPIOA, GPIO_PIN_5},
        .MISO = {GPIOA, GPIO_PIN_6},
        .MOSI = {GPIOB, GPIO_PIN_5},
        .NSS  = {GPIOD, GPIO_PIN_14},
    },
    .rx_handle_attr = {
        .name = "spiRxSem"
    },
    .rx_buf = rx_buf,
    .tx_handle_attr = {
        .name = "spiTxSem"
    },
    .tx_buf = tx_buf,
};

JsonPktPool json_pkt_pool;

static JsonPkt* recv_pkts[JSON_RECV_BUF_CAP];
JsonPktBuf spi_recv_buf = {
    .buf = recv_pkts,
    .cap = JSON_RECV_BUF_CAP,
};

static JsonPkt* trsm_pkts[JSON_TRSM_BUF_CAP];
JsonPktBuf spi_trsm_buf = {
    .buf = trsm_pkts,
    .cap = JSON_TRSM_BUF_CAP,
};
