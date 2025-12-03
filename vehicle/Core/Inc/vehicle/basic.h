#pragma once

#include "main/config.h"
#include "main/fn_state.h"

#define MOTOR_STOP_GATE 10.0f

typedef struct VehicleConst
{

} VehicleConst;

typedef enum VehicleMode
{
    // 停止
    VEHICLE_MODE_END,
    // 自由
    VEHICLE_MODE_FREE,
    // 循跡
    VEHICLE_MODE_TRACK,
    // 旋轉
    VEHICLE_MODE_T_ROTATE,
    // 離點(前進後循跡)
    VEHICLE_MODE_T_LEAVE,
    // 尋找
    VEHICLE_MODE_SEARCH_LEFT,
    VEHICLE_MODE_SEARCH_RIGHT,
    VEHICLE_MODE_SEARCH_L_RET,
    VEHICLE_MODE_SEARCH_R_RET,
    VEHICLE_MODE_SEARCH_L_RET_FIX,
    VEHICLE_MODE_SEARCH_R_RET_FIX,
} VehicleMode;

typedef enum VehicleDirection
{
    VEHICLE_MOTION_STOP,
    VEHICLE_MOTION_UNKNOWN,
    VEHICLE_MOTION_FORWARD,
    VEHICLE_MOTION_BACKWARD,
    VEHICLE_MOTION_CLOCKWISE,
    VEHICLE_MOTION_C_CLOCKWISE,
} VehicleDirection;

typedef struct VehicleMotSpd
{
    VehicleDirection direction;
    float32_t speed;
} VehicleMotSpd;

typedef enum DirectionState
{
    DIRECTION_NORMAL,
    DIRECTION_BRAKE_TO_ZERO,
    DIRECTION_SWITCH_DIR,
} DirectionState;

typedef enum VehicleHallState
{
    ADC_HALL_STATE_NONE,
    ADC_HALL_STATE_ON_MAG,
} VehicleHallState;

typedef struct VehicleTrackP
{
    uint8_t rot_need_count;
    VehicleHallState front_last_state;
} VehicleTrackP;

typedef enum USSStatus
{
    USS_STATUS_SAVE,
    USS_STATUS_WARNING,
    USS_STATUS_DANGER,
} USSStatus;

typedef struct MotorSet
{
    const uint16_t id;
    uint8_t mode;
    bool reverse;
    Percentage value;
    float32_t max;
} MotorSet;

typedef struct VehicleParameter
{
    const VehicleConst const_h;
    VehicleMode mode;
    VehicleMotSpd user_set;
    VehicleMotSpd reference;
    VehicleTrackP t_rotate;
    DirectionState dir_state;
    VehicleHallState hall_front;
    VehicleHallState hall_left;
    VehicleHallState hall_right;
    USSStatus us_sensor;
    MotorSet motor_left_ref;
    MotorSet motor_right_ref;
    MotorSet motor_left_fbk;
    MotorSet motor_right_fbk;

    uint32_t last_tick_on_mag;
    uint8_t search_cnt;
} VehicleParameter;

extern VehicleParameter vehicle_h;

// void vehicle_ensure_stop(VehicleParameter *vehicle, uint32_t ms);
void vehicle_set_direction(VehicleParameter *vehicle, VehicleDirection direction);
void vehicle_set_speed(VehicleParameter *vehicle, Percentage value);
void vehicle_set_mode(VehicleParameter *vehicle, VehicleMode mode);
void vehicle_set_need_rotate(VehicleParameter *vehicle, uint8_t value);
