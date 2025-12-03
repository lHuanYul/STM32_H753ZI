#pragma once

#include "vehicle/basic.h"

void vehicle_search
(
    VehicleParameter *vehicle,
    VehicleMode reach_next,
    VehicleMode timeout_next,
    uint32_t unfind_ms
);
