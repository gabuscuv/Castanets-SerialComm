#include "serialCommImpl.h"
#include "serialComm.hpp"
#include "spdlog/spdlog.h"
#include <thread>
#include <string>
#include "serialDetector.h"

std::string findCastanetPort()
{
    auto device = SerialDetector::findCastanetHub();

    if (device.port.empty())
    {
        throw std::runtime_error(
            "Castanets Hub not found");
    }
    spdlog::info("Selected: {} {}", device.description, device.port);
    return device.port;
}

SerialComm::Impl::Impl(std::string device, unsigned int baudRate)
    : ioContext{}, serial{ioContext, device}
{
}

SerialComm::Impl::Impl() : ioContext{}, serial{ioContext, findCastanetPort()}
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
    spdlog::info("Starting Serial Threading");

    try
    {
        thread = std::thread(&SerialComm::Impl::loop, this);
        running = true;
    }
    catch (...)
    {
        spdlog::error("Failed to Create Thread");
        return -1;
    }
    return 0;
}

int SerialComm::Impl::stop()
{
    running = false;

    std::error_code ec;
    serial.cancel(ec);
    serial.close(ec);

    if (thread.joinable())
    {
        thread.join();
    }

    return 0;
}

bool SerialComm::Impl::isRunning() const noexcept
{
    return running;
}

Nano::Signal<void(const char *)> *SerialComm::Impl::getNewDataAvaliable()
{
    return &newDataAvaliable;
}

void SerialComm::Impl::loop()
{
    constexpr std::size_t BufferSize = 1024;

    std::array<std::uint8_t, BufferSize> buffer{};
    std::string receiveBuffer;

    while (running)
    {
        std::error_code ec;

        const auto bytesRead = serial.read_some(asio::buffer(buffer), ec);

        if (ec)
        {
            if (!running)
            {
                break;
            }

            spdlog::error("Serial read error: {}", ec.message());

            break;
        }

        if (bytesRead == 0)
        {
            continue;
        }

        receiveBuffer.append(
            reinterpret_cast<const char *>(buffer.data()),
            bytesRead);

        // Process complete JSON messages.
        std::size_t delimiter;

        while ((delimiter = receiveBuffer.find('\n')) != std::string::npos)
        {
            std::string json = receiveBuffer.substr(0, delimiter);
            receiveBuffer.erase(0, delimiter + 1);

            if (json.empty())
            {
                continue;
            }

            newDataAvaliable.fire(json.c_str());
        }
    }

    running = false;
}
