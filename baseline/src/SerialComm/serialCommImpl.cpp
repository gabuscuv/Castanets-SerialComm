#include "serialCommImpl.h"
#include "serialComm.hpp"
#include "spdlog/spdlog.h"
#include <thread>
#include <string>


SerialComm::Impl::Impl(std::string device, unsigned int baudRate)
    : Impl{}
{
}

SerialComm::Impl::Impl():
    serial{asio::serial_port(ioContext)}
{
  
}

SerialComm::Impl::~Impl()
{
    if (running)
    {
        stop();
    }
}

int SerialComm::Impl::start()
{
    try {
        thread = std::thread(&SerialComm::Impl::loop, this);
    } catch(...) {
        spdlog::error("Failed to Create Thread");
        return -1;
    }
    return 0;
}

int SerialComm::Impl::stop()
{
    running = false;
    return 0;
}

bool SerialComm::Impl::isRunning() const noexcept
{
    return running;
}

Nano::Signal<void(const char*)>* SerialComm::Impl::getNewDataAvaliable()
{
    return &newDataAvaliable;
}

void SerialComm::Impl::loop()
{
    std::array<std::uint8_t, 1024> buffer{};
    running = true;

    while (running)
    {
        std::error_code ec;

            const auto bytesRead =
                serial.read_some(
                    asio::buffer(buffer),
                    ec);

            if (ec)
            {
                if (!running)
                    break;

                // Handle serial error.
                break;
            }

            if (bytesRead > 0)
            {
                // onData(
                //     buffer.data(),
                //     bytesRead);
            }
        }
    std::string _PLACEHOLDER;

    newDataAvaliable.fire(_PLACEHOLDER.c_str());
}

