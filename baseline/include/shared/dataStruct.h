#pragma once
#include <string>
#include <vector>
#include <stdint.h>

#define CONTROLLER_CLICK_HISTORY 3
#define FEET_CONTROLLER_COUNT     3

typedef uint64_t HubTime;

struct IMU
{
    uint64_t time;
    float x;
    float y;
    float z;
};

struct Click
{
    uint64_t time;
    std::string button;
};

struct ControllerInput
{
    std::vector<Click> clicks;
    IMU imu;
};

struct FootInput
{
    uint64_t time;
    float value;
};

struct InputFrame
{
    int version;
    std::string type;
    uint64_t hubTime;

    ControllerInput leftController;
    ControllerInput rightController;

    std::vector<FootInput> feetController;
};

typedef void (*InputCallBack)(InputFrame);
