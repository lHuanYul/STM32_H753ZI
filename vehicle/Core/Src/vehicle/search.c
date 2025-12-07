#include "vehicle/search.h"

void vehicle_search
(
    VehicleParameter *vehicle,
    VehicleMode reach_next,
    VehicleMode timeout_next,
    uint32_t unfind_ms
) {
    vehicle->motor_left.value_ref = 20;
    vehicle->motor_right.value_ref = 20;
    if (vehicle->hall_front.state != ADC_HALL_STATE_NONE)
    {
        vehicle->last_tick_on_mag = HAL_GetTick();
        vehicle_set_mode(vehicle, reach_next, 0);
    }
    if (HAL_GetTick() - vehicle->last_tick_on_mag >= unfind_ms)
    {
        vehicle_set_mode(vehicle, timeout_next, 0);
    }
}
