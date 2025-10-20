#pragma once

#include "main/config.h"
#include "main/fn_state.h"

typedef struct SD_CARD_CONST
{
    SD_HandleTypeDef *hsdx;
    MDMA_HandleTypeDef *hmdma;
    char *SDPath;
} SD_CARD_CONST;

typedef enum SD_CARD_STATE {
    SD_CARD_STATE_INVALID,
    SD_CARD_STATE_READY,
    SD_CARD_STATE_ERROR,
} SD_CARD_STATE;

typedef struct SD_CARD
{
    SD_CARD_CONST const_h;
    SD_CARD_STATE state;
    uint8_t MSD_state;
    HAL_SD_CardStateTypeDef card_state;
    HAL_StatusTypeDef hal_status;
    FRESULT f_result;
    FATFS fs;
    FIL file_0;
    UINT bits;
} SD_CARD;

extern SD_CARD sd_card0;

HAL_StatusTypeDef mdma_memcpy_align32(void *dst32, const void *src, size_t len);
