#include "vehicle/track.h"

/**
 * @brief 循跡模式
 */
void vehicle_track_normal(VehicleParameter *vehicle, uint32_t unfind_ms)
{
    vehicle->motor_left.value_ref = vehicle->reference.speed;
    vehicle->motor_right.value_ref = vehicle->reference.speed;
    if (vehicle->hall_front != ADC_HALL_STATE_NONE)
        vehicle->last_tick_on_mag = HAL_GetTick();
    else
    {
        if (
            vehicle->hall_left != ADC_HALL_STATE_NONE &&
            vehicle->hall_right == ADC_HALL_STATE_NONE
        ) {
            vehicle->last_tick_on_mag = HAL_GetTick();
            vehicle->motor_left.value_ref = 0;
        }
        else if (
            vehicle->hall_left == ADC_HALL_STATE_NONE &&
            vehicle->hall_right != ADC_HALL_STATE_NONE
        ) {
            vehicle->last_tick_on_mag = HAL_GetTick();
            vehicle->motor_right.value_ref = 0;
        }
        else if (
            vehicle->hall_left != ADC_HALL_STATE_NONE &&
            vehicle->hall_right != ADC_HALL_STATE_NONE
        ) {
            vehicle->last_tick_on_mag = HAL_GetTick();
        }
        else if (
            vehicle->hall_left == ADC_HALL_STATE_NONE &&
            vehicle->hall_right == ADC_HALL_STATE_NONE &&
            (HAL_GetTick() - vehicle->last_tick_on_mag >= unfind_ms)
        ) {
            vehicle_set_mode(vehicle, VEHICLE_MODE_SEARCH_LEFT);
            vehicle_set_direction(vehicle, VEHICLE_MOTION_STOP);
        }
    }
}

/**
  * @brief AGV 原地旋轉直到對準方向，根據強磁計數更新 AGV 方向資料
  */
void vehicle_track_rotate(VehicleParameter *vehicle, uint32_t unfind_ms)
{
    vehicle->motor_left.value_ref = vehicle->reference.speed;
    vehicle->motor_right.value_ref = vehicle->reference.speed;
    if (vehicle->hall_front != ADC_HALL_STATE_NONE)
    {
        vehicle->last_tick_on_mag = HAL_GetTick();
        if (vehicle->t_rotate.front_last_state == ADC_HALL_STATE_NONE)
            vehicle->t_rotate.rot_need_count--;
    }
    vehicle->t_rotate.front_last_state = vehicle->hall_front;
    if (vehicle->t_rotate.rot_need_count <= 0)
    {
        vehicle_set_mode(vehicle, VEHICLE_MODE_TRACK);
        vehicle_set_direction(vehicle, VEHICLE_MOTION_FORWARD);
    }
    if (HAL_GetTick() - vehicle->last_tick_on_mag >= unfind_ms)
    {
        vehicle_set_mode(vehicle, VEHICLE_MODE_END);
        vehicle_set_direction(vehicle, VEHICLE_MOTION_STOP);
        return;
    }
}
