#include <gtest/gtest.h>

#include "SerialComm/serialComm.hpp"
#include "helpers/SerialComm/PtyDevice.hpp"
#include "helpers/SerialComm/WaitableData.hpp"
#include <string>
#include <sys/select.h>
#include <unistd.h>

using namespace std::chrono_literals;

TEST(SerialCommTest, CanConstruct)
{
    PtyDevice pty;

    SerialComm serial{
        pty.slavePath(),
        115200
    };

    SUCCEED();
}

TEST(SerialCommTest, StartAndStop)
{
    PtyDevice pty;

    SerialComm serial{
        pty.slavePath(),
        115200
    };

    EXPECT_FALSE(serial.isRunning());

    serial.start();

    EXPECT_TRUE(serial.isRunning());

    serial.stop();

    EXPECT_FALSE(serial.isRunning());
}