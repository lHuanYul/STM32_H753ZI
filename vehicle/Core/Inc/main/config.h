/*
#include "main/config.h"
*/
#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

#define ATTR_X(...) __attribute__((__VA_ARGS__))
#define ATTR_UNUSED __attribute__((unused))
#define ATTR_WEAK   __attribute__((weak))

// ! SYSTEM config, Change CAREFULLY --------------------
// ! Also CHECK ALL basic.c file
#include "arm_math.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "fatfs.h"

#include "stm32h753xx.h"
#include "stm32h7xx_hal.h"

#define STM32_DEVICE
#define STM32H753ZI
#define ITS_CHECK(its, tag)  (((its) & (tag)) != RESET)
#define MCU_VEHICLE_MAIN
#include "HY_MOD/cmds.h"
#define FDCAN_FIFO0_FILTER0_ID_MIN  0x108
#define FDCAN_FIFO0_FILTER0_ID_MAX  0x10F
#define FDCAN_FIFO1_FILTER0_ID_MIN  0x100
#define FDCAN_FIFO1_FILTER0_ID_MAX  0x107

#define MOTOR_HISTORY_LEN 600

#define TIM2_PSC        63
#define TIM2_ARR        UINT32_MAX
#define TIM3_PSC        639
#define TIM3_ARR        2000
#define TIM4_PSC        639
#define TIM4_ARR        2000

#define HY_MOD_STM32_FDCAN
#define FDCAN_STD_FILTER_NBR    2
#define FDCAN_RX0_NBR           16
#define FDCAN_RX1_NBR           16
#define FDCAN_RX_BUF_NBR        0
#define FDCAN_TX_BUF_NBR        4
#define FDCAN_TX_FIFO_NBR       16
#define FDCAN_TX_EVT_NBR        (FDCAN_TX_BUF_NBR+FDCAN_TX_FIFO_NBR)
#define FDCAN_FILTER0_ID_MIN    0x010
#define FDCAN_FILTER0_ID_MAX    0x011
#define FDCAN_FILTER1_ID_MIN    0x012
#define FDCAN_FILTER1_ID_MAX    0x013
#define FDCAN_PKT_LEN           8
#define FDCAN_PKT_POOL_CAP      32
#define FDCAN_TRSM_BUF_CAP      10
#define FDCAN_RECV_BUF_CAP      10

#define HY_MOD_STM32_SDMMC
#define SDMMC_CLK_DIV           8

#define HY_MOD_STM32_SPI_JSON
#define HY_MOD_STM32_JSON
#define JSON_PKT_LEN            1024
#define JSON_PKT_POOL_CAP       10
#define JSON_TRSM_BUF_CAP       4
#define JSON_RECV_BUF_CAP       4

#define HY_MOD_STM32_DHT11

// ! Also CHECK ALL basic.c file
// ! SYSTEM config END ------------------------------

typedef uint8_t Percentage;
