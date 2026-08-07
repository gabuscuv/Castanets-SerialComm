#pragma once

#include "nano_signal_slot.hpp"

class SerialComm {
public:
    SerialComm();
    void init();
    Nano::Signal<void(const char*)> newDataAvaliable;
private:
  void loop();
};