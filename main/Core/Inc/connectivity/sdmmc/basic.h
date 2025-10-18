#pragma once

#include "main/config.h"
#include "main/fn_state.h"

typedef struct SD_CARD_CONST
{
    SD_HandleTypeDef *hsdx;
    MDMA_HandleTypeDef *hmdma;
} SD_CARD_CONST;

typedef struct SD_CARD
{
    SD_CARD_CONST const_h;
    HAL_SD_CardStateTypeDef state;
    HAL_StatusTypeDef hal_status;
    FRESULT f_result;
    FATFS fs;
    FIL file;
    UINT bits;
} SD_CARD;

extern SD_CARD sd_card;

HAL_StatusTypeDef mdma_memcpy_align32(void *dst32, const void *src, size_t len);
