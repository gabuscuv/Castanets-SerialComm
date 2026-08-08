#pragma once

#include "shared/dataStruct.h"
#include <nlohmann/json.hpp>

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IMU,
    time,
    x,
    y,
    z
)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Click,
    time,
    button
)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ControllerInput,
    clicks,
    imu
)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FootInput,
    time,
    value
)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(InputFrame,
    version,
    type,
    hubTime,
    leftController,
    rightController,
    feetController
)