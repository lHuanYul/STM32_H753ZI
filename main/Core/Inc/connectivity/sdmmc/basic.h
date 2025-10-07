#pragma once

#include "main/config.h"
#include "main/fn_state.h"

typedef struct SD_CARD_CONST
{
    SD_HandleTypeDef *hsdx;
} SD_CARD_CONST;

typedef struct SD_CARD
{
    SD_CARD_CONST const_h;
    HAL_SD_CardStateTypeDef state;
    HAL_StatusTypeDef result;
} SD_CARD;

extern SD_CARD sd_card;
