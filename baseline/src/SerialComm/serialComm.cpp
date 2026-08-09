#include "SerialComm/serialComm.hpp"
#include "SerialComm/serialCommImpl.h"

SerialComm::SerialComm()
    : impl_(std::make_unique<Impl>())
{
}

SerialComm::SerialComm(
    std::string device,
    unsigned int baudRate)
    : impl_(std::make_unique<Impl>(
          std::move(device),
          baudRate))
{
}

SerialComm::~SerialComm() = default;

void SerialComm::start()
{
    impl_->start();
}

void SerialComm::stop()
{
    impl_->stop();
}

bool SerialComm::isRunning() const noexcept { return impl_->isRunning(); }

Nano::Signal<void(const char *)> *SerialComm::getNewDataAvaliable()
{
    return impl_->getNewDataAvaliable();
}