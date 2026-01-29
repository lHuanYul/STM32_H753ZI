#include "main/dht.h"

#include "HY_MOD/main/tim.h"
#include "tim.h"

DhtParametar dht_h = {
    .const_h = {
        .htimx = &htim2,
        .TIM_CHANNEL_x = TIM_CHANNEL_1,
        .HAL_TIM_ACTIVE_CHANNEL_x = HAL_TIM_ACTIVE_CHANNEL_1,
        .tim_clk = &tim_clk_APB1,
        .gpio = {
            .GPIOx = GPIOA,
            .GPIO_Pin_x = GPIO_PIN_0,
        },
    },
};
