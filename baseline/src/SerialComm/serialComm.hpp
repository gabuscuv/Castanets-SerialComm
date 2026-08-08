#pragma once

#include <cstdint>
#include <memory>
#include "nano_signal_slot.hpp"

class SerialComm
{
public:
    SerialComm(
        std::string device,
        unsigned int baudRate = 115200);
    SerialComm();
    ~SerialComm();

    SerialComm(const SerialComm&) = delete;
    SerialComm& operator=(const SerialComm&) = delete;

    SerialComm(SerialComm&&) noexcept;
    SerialComm& operator=(SerialComm&&) noexcept;

    void start();
    void stop();

    void send(
        const std::uint8_t* data,
        std::size_t size);

    bool isRunning() const noexcept;

    Nano::Signal<void(const char*)>* getNewDataAvaliable();


private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};