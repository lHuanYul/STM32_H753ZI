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
#define STM32_H753ZI
#define ITS_CHECK(its, tag)  (((its) & (tag)) != RESET)
#define PROJECT_MAIN

#define TIM3_PSC        1700
#define TIM3_ARR        2000
#define TIM4_PSC        1700
#define TIM4_ARR        2000

#define FDCAN_STD_FILTER_NBR    2
#define FDCAN_RX0_NBR           16
#define FDCAN_RX1_NBR           16
#define FDCAN_RX_BUF_NBR        0
#define FDCAN_TX_BUF_NBR        4
#define FDCAN_TX_FIFO_NBR       16
#define FDCAN_TX_EVT_NBR        (FDCAN_TX_BUF_NBR+FDCAN_TX_FIFO_NBR)
#define FDCAN_FILTER0_ID_MIN    0x020
#define FDCAN_FILTER0_ID_MAX    0x021
#define FDCAN_FILTER1_ID_MIN    0x022
#define FDCAN_FILTER1_ID_MAX    0x023
#define FDCAN_TEST_ID           0x001
#define FDCAN_DATA_ID           0x011
#define FDCAN_PKT_LEN           8
#define FDCAN_PKT_POOL_CAP      32
#define FDCAN_TRSM_BUF_CAP      10
#define FDCAN_RECV_BUF_CAP      10

#define SDMMC_CLK_DIV           8

// ! Also CHECK ALL basic.c file
// ! SYSTEM config END ------------------------------
