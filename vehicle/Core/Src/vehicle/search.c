#include "vehicle/search.h"

void vehicle_search
(
    VehicleParameter *vehicle,
    VehicleMode reach_next,
    VehicleMode timeout_next,
    uint32_t unfind_ms
) {
    vehicle->motor_left_ref.value = 20;
    vehicle->motor_right_ref.value = 20;
    if (vehicle->hall_front != ADC_HALL_STATE_NONE)
    {
        vehicle->last_tick_on_mag = HAL_GetTick();
        vehicle_set_mode(vehicle, reach_next);
    }
    if (HAL_GetTick() - vehicle->last_tick_on_mag >= unfind_ms)
    {
        vehicle_set_mode(vehicle, timeout_next);
    }
}
