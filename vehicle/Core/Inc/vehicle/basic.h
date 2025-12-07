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
    ADC_HALL_STATE_UNK,
    ADC_HALL_STATE_NONE,
    ADC_HALL_STATE_ON_MAG,
} VehicleHallState;

typedef struct VehicleHall
{
    VehicleHallState state;
    uint32_t alive_tick;
} VehicleHall;

typedef enum USSState
{
    USS_STATUS_UNK,
    USS_STATUS_SAVE,
    USS_STATUS_WARNING,
    USS_STATUS_DANGER,
} USSState;

typedef struct VehicleUSS
{
    USSState state;
    uint32_t alive_tick;
} VehicleUSS;

typedef struct MotorParameter
{
    const uint16_t id;
    uint32_t alive_tick;
    uint8_t mode_ref;
    bool rev_ref;
    Percentage value_ref;
    uint8_t mode_fbk;
    bool rev_fbk;
    Percentage value_fbk;
    float32_t max;
} MotorParameter;

typedef struct VehicleParameter
{
    const VehicleConst const_h;
    VehicleMode mode;
    VehicleMotSpd user_set;
    VehicleMotSpd reference;
    uint8_t rot_need_count;
    VehicleHallState front_last_state;
    DirectionState dir_state;
    VehicleHall hall_front;
    VehicleHall hall_left;
    VehicleHall hall_right;
    VehicleUSS us_sensor;
    MotorParameter motor_left;
    MotorParameter motor_right;

    uint32_t last_tick_on_mag;
    uint8_t search_cnt;
} VehicleParameter;

extern VehicleParameter vehicle_h;

// void vehicle_ensure_stop(VehicleParameter *vehicle, uint32_t ms);
void vehicle_set_direction(VehicleParameter *vehicle, VehicleDirection direction);
void vehicle_set_speed(VehicleParameter *vehicle, Percentage value);
void vehicle_set_mode(VehicleParameter *vehicle, VehicleMode mode, uint8_t rot_cnt);
void vehicle_set_need_rotate(VehicleParameter *vehicle, uint8_t value);
