#include "connectivity/sdmmc/basic.h"
#include "sdmmc.h"

SD_CARD sd_card = {
    .const_h = {
        .hsdx = &hsd1,
    }
};
