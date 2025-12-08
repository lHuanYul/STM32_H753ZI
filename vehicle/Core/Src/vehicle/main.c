#include "vehicle/main.h"
#include "vehicle/track.h"
#include "vehicle/search.h"
#include "main/fn_state.h"
#include "connectivity/fdcan/pkt_write.h"

// motor mode & spd update
static void mode_update(VehicleParameter *vehicle)
{
    switch (vehicle->mode)
    {
        case VEHICLE_MODE_END:
        {
            vehicle->motor_left.mode_ref = CMD_WHEEL_B0_BREAK;
            vehicle->motor_right.mode_ref = CMD_WHEEL_B0_BREAK;
            break;
        }
        case VEHICLE_MODE_FREE:
        {
            vehicle->dict_ref = vehicle->free.direction;
            vehicle->motor_left.mode_ref = CMD_WHEEL_B0_NORMAL;
            vehicle->motor_left.value_ref = vehicle->free.speed;
            vehicle->motor_right.mode_ref = CMD_WHEEL_B0_NORMAL;
            vehicle->motor_right.value_ref = vehicle->free.speed;
            break;
        }
        case VEHICLE_MODE_TRACK:
        {
            vehicle_track_normal(vehicle, 1000);
            break;
        }
        case VEHICLE_MODE_T_ROTATE:
        {
            vehicle_track_rotate(vehicle, 5000);
            break;
        }
        case VEHICLE_MODE_SEARCH_LEFT:
        {
            vehicle_search(
                vehicle,
                VEHICLE_MOTION_C_CLOCKWISE,
                VEHICLE_MODE_SEARCH_L_RET,
                VEHICLE_MODE_SEARCH_RIGHT,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_RIGHT:
        {
            vehicle_search(
                vehicle,
                VEHICLE_MOTION_CLOCKWISE,
                VEHICLE_MODE_SEARCH_R_RET,
                VEHICLE_MODE_END,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_L_RET:
        {
            vehicle_search(
                vehicle,
                VEHICLE_MOTION_FORWARD,
                VEHICLE_MODE_SEARCH_L_RET_FIX,
                VEHICLE_MODE_SEARCH_LEFT,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_R_RET:
        {
            vehicle_search(
                vehicle,
                VEHICLE_MOTION_FORWARD,
                VEHICLE_MODE_SEARCH_R_RET_FIX,
                VEHICLE_MODE_SEARCH_LEFT,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_L_RET_FIX:
        {
            vehicle_search(
                vehicle,
                VEHICLE_MOTION_CLOCKWISE,
                VEHICLE_MODE_END,
                VEHICLE_MODE_SEARCH_LEFT,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_R_RET_FIX:
        {
            vehicle_search(
                vehicle,
                VEHICLE_MOTION_C_CLOCKWISE,
                VEHICLE_MODE_END,
                VEHICLE_MODE_SEARCH_LEFT,
                2000
            );
            break;
        }
    }
}

// motor break & reverse update
static void direction_update(VehicleParameter *vehicle)
{
    VehicleDirection dict_set = vehicle->dict_ref;
    switch (vehicle->dict_state)
    {
        case DIRECTION_NORMAL:
        {
            if (vehicle->dict_ref == vehicle->dict_fbk) break;
            {
                vehicle->dict_state = DIRECTION_SWITCHING;
            }
        }
        case DIRECTION_SWITCHING:
        {
            uint8_t unstop = 2;
            if ((vehicle->motor_left.value_fbk < MOTOR_STOP_GATE))
            {
                unstop--;
                // vehicle->motor_left.mode_ref = CMD_WHEEL_B0_LOCK;
            }
            if ((vehicle->motor_right.value_fbk < MOTOR_STOP_GATE))
            {
                unstop--;
                // vehicle->motor_right.mode_ref = CMD_WHEEL_B0_LOCK;
            }
            if (unstop == 0)
            {
                vehicle->dict_state = DIRECTION_NORMAL;
                break;
            }
            dict_set = vehicle->dict_fbk;
            vehicle->motor_left.mode_ref = CMD_WHEEL_B0_BREAK;
            vehicle->motor_right.mode_ref = CMD_WHEEL_B0_BREAK;
            break;
        }
    }
    vehicle_motor_dir_set(vehicle, dict_set);
}

// emergency stop
static void uss_update(VehicleParameter *vehicle)
{
    if (
        vehicle->us_sensor.state == USS_STATUS_DANGER
        && vehicle->dict_ref == VEHICLE_MOTION_FORWARD
    ) {
        vehicle->motor_left.mode_ref = CMD_WHEEL_B0_BREAK;
        vehicle->motor_right.mode_ref = CMD_WHEEL_B0_BREAK;
    }
}

bool vehicle_ready = false;
void StartVehicleTask(void *argument)
{
    VehicleParameter *vehicle = &vehicle_h;
    for(;;)
    {
        vehicle_motor_dir_fbk(vehicle);
        mode_update(vehicle);
        direction_update(vehicle);

        uss_update(vehicle);

        fdcan_vehicle_motor_send(vehicle);

        osDelay(10);
        vehicle_ready = true;
    }
}
