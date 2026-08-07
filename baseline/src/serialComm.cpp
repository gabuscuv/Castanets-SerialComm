#include "serialComm.h"
#include "asio.hpp"
#include <string>

void SerialComm::init()
{
    asio::io_context io;
    asio::serial_port serial(io, "/dev/ttyUSB0");
}

void SerialComm::loop()
{
    std::string _PLACEHOLDER;

    newDataAvaliable.fire(_PLACEHOLDER.c_str());
}

