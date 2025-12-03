#include "vehicle/main.h"
#include "vehicle/track.h"
#include "vehicle/search.h"
#include "main/fn_state.h"
#include "connectivity/fdcan/pkt_write.h"

static void mode_update(VehicleParameter *vehicle)
{
    switch (vehicle->mode)
    {
        case VEHICLE_MODE_END:
        {
            vehicle_set_direction(vehicle, VEHICLE_MOTION_STOP);
            vehicle_set_mode(vehicle, VEHICLE_MODE_FREE);
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
            vehicle_set_direction(vehicle, VEHICLE_MOTION_C_CLOCKWISE);
            vehicle_search(
                vehicle,
                VEHICLE_MODE_SEARCH_L_RET,
                VEHICLE_MODE_SEARCH_RIGHT,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_RIGHT:
        {
            vehicle_set_direction(vehicle, VEHICLE_MOTION_CLOCKWISE);
            vehicle_search(
                vehicle,
                VEHICLE_MODE_SEARCH_R_RET,
                VEHICLE_MODE_END,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_L_RET:
        {
            vehicle_set_direction(vehicle, VEHICLE_MOTION_FORWARD);
            vehicle_search(
                vehicle,
                VEHICLE_MODE_SEARCH_L_RET_FIX,
                VEHICLE_MODE_SEARCH_LEFT,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_R_RET:
        {
            vehicle_set_direction(vehicle, VEHICLE_MOTION_FORWARD);
            vehicle_search(
                vehicle,
                VEHICLE_MODE_SEARCH_R_RET_FIX,
                VEHICLE_MODE_SEARCH_LEFT,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_L_RET_FIX:
        {
            vehicle_set_direction(vehicle, VEHICLE_MOTION_CLOCKWISE);
            vehicle_search(
                vehicle,
                VEHICLE_MODE_END,
                VEHICLE_MODE_SEARCH_LEFT,
                2000
            );
            break;
        }
        case VEHICLE_MODE_SEARCH_R_RET_FIX:
        {
            vehicle_set_direction(vehicle, VEHICLE_MOTION_C_CLOCKWISE);
            vehicle_search(
                vehicle,
                VEHICLE_MODE_END,
                VEHICLE_MODE_SEARCH_LEFT,
                2000
            );
            break;
        }
        default: break;
    }
}

static void motor_dir_update(VehicleParameter *vehicle, VehicleDirection dict)
{
    switch (dict)
    {
        case VEHICLE_MOTION_STOP:
        {
            vehicle->motor_left_ref.mode = CMD_WHEEL_B0_LOCK;
            vehicle->motor_right_ref.mode = CMD_WHEEL_B0_LOCK;
            break;
        }
        case VEHICLE_MOTION_FORWARD:
        {
            vehicle->motor_left_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_left_ref.reverse = 0;
            vehicle->motor_right_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_right_ref.reverse = 1;
            break;
        }
        case VEHICLE_MOTION_BACKWARD:
        {
            vehicle->motor_left_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_left_ref.reverse = 1;
            vehicle->motor_right_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_right_ref.reverse = 0;
            break;
        }
        case VEHICLE_MOTION_CLOCKWISE:
        {
            vehicle->motor_left_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_left_ref.reverse = 0;
            vehicle->motor_right_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_right_ref.reverse = 0;
            break;
        }
        case VEHICLE_MOTION_C_CLOCKWISE:
        {
            vehicle->motor_left_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_left_ref.reverse = 1;
            vehicle->motor_right_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_right_ref.reverse = 1;
            break;
        }
        default: break;
    }
}

static void direction_update(VehicleParameter *vehicle)
{
    switch (vehicle->dir_state)
    {
        case DIRECTION_NORMAL:
        {
            motor_dir_update(vehicle, vehicle->reference.direction);
            vehicle->reference.speed = vehicle->user_set.speed;
            if (vehicle->reference.direction != vehicle->user_set.direction)
            {
                vehicle->dir_state = DIRECTION_BRAKE_TO_ZERO;
            }
            break;
        }
        case DIRECTION_BRAKE_TO_ZERO:
        {
            vehicle->motor_left_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_right_ref.mode = CMD_WHEEL_B0_SET_SPD;
            motor_dir_update(vehicle, vehicle->reference.direction);
            vehicle->motor_left_ref.value = 0;
            vehicle->motor_right_ref.value = 0;
            uint8_t unstop = 2;
            if ((vehicle->motor_left_fbk.value < MOTOR_STOP_GATE))
            {
                unstop--;
                vehicle->motor_left_ref.mode = CMD_WHEEL_B0_LOCK;
            }
            if ((vehicle->motor_right_fbk.value < MOTOR_STOP_GATE))
            {
                unstop--;
                vehicle->motor_right_ref.mode = CMD_WHEEL_B0_LOCK;
            }
            if (unstop == 0) vehicle->dir_state = DIRECTION_SWITCH_DIR;
            break;
        }
        case DIRECTION_SWITCH_DIR:
        {
            vehicle->motor_left_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->motor_right_ref.mode = CMD_WHEEL_B0_SET_SPD;
            vehicle->reference.direction = vehicle->user_set.direction;
            motor_dir_update(vehicle, vehicle->reference.direction);
            vehicle->reference.speed = vehicle->user_set.speed;
            vehicle->dir_state = DIRECTION_NORMAL;
            break;
        }
    }
}

static void uss_update(VehicleParameter *vehicle)
{
    if (
        vehicle->us_sensor == USS_STATUS_DANGER
        && vehicle->reference.direction == VEHICLE_MOTION_FORWARD
    ) {
        vehicle->motor_left_ref.mode = CMD_WHEEL_B0_SET_SPD;
        vehicle->motor_right_ref.mode = CMD_WHEEL_B0_SET_SPD;
        vehicle->reference.direction = VEHICLE_MOTION_STOP;
        motor_dir_update(vehicle, vehicle->reference.direction);
        vehicle->motor_left_ref.value = 0;
        vehicle->motor_right_ref.value = 0;
    }
}

bool vehicle_ready = false;
void StartVehicleTask(void *argument)
{
    VehicleParameter *vehicle = &vehicle_h;
    for(;;)
    {
        mode_update(vehicle);
        direction_update(vehicle);

        uss_update(vehicle);

        if (vehicle->reference.direction != VEHICLE_MOTION_UNKNOWN)
            fdcan_vehicle_motor_send(vehicle);

        osDelay(10);
        vehicle_ready = true;
    }
}
