#include "vehicle/basic.h"
#include "main/variable_cal.h"
#include "connectivity/fdcan/pkt_write.h"

VehicleParameter vehicle_h = {
    .motor_left = {
        .id = CAN_ID_WHEEL_LEFT_SET,
        .max = 200.0f,
    },
    .motor_right = {
        .id = CAN_ID_WHEEL_RIGHT_SET,
        .max = 200.0f,
    },
};

void vehicle_set_direction(VehicleParameter *vehicle, VehicleDirection direction)
{
    vehicle->user_set.direction = direction;
}

void vehicle_set_speed(VehicleParameter *vehicle, Percentage value)
{
    vehicle->user_set.speed = value;
    VAR_CLAMPF(vehicle->user_set.speed, 0, 100);
}

void vehicle_set_mode(VehicleParameter *vehicle, VehicleMode mode, uint8_t rot_cnt)
{
    switch (mode)
    {
        case VEHICLE_MODE_END:
        case VEHICLE_MODE_FREE:
        {
            vehicle->search_cnt = 0;
            break;
        }
        case VEHICLE_MODE_TRACK:
        case VEHICLE_MODE_T_LEAVE:
        {
            vehicle->last_tick_on_mag = HAL_GetTick();
            vehicle->search_cnt = 0;
            break;
        }
        case VEHICLE_MODE_T_ROTATE:
        {
            vehicle->rot_need_count = rot_cnt;
            vehicle->last_tick_on_mag = HAL_GetTick();
            vehicle->search_cnt = 0;
            break;
        }
        case VEHICLE_MODE_SEARCH_LEFT:
        {
            vehicle->last_tick_on_mag = HAL_GetTick();
            vehicle->search_cnt++;
            if (vehicle->search_cnt >= 3)
            {
                vehicle->search_cnt = 0;
                mode = VEHICLE_MODE_END;
            }
            break;
        }
        default: break;
    }
    vehicle->mode = mode;
}
