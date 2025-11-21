#pragma once

#include "main/config.h"
#include "main/fn_state.h"

typedef struct FILE_OWN_CONST
{
    char *name;
    uint8_t byte;
} FILE_OWN_CONST;

typedef struct FILE_OWN
{
    FILE_OWN_CONST const_h;
    uint32_t data_cnt;
} FILE_OWN;

extern FILE_OWN file_test;
