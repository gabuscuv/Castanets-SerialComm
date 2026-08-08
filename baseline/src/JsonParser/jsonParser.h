#pragma once

#include "dataStruct_json.h"
#include "nano_signal_slot.hpp"

class JsonParser {
public:
    static InputFrame parseJson(const char* json);

    void onNewData(const char* json);

    Nano::Signal<void(InputFrame)> newDataAvaliable;
};