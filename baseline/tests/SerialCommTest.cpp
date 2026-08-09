#include <gtest/gtest.h>
#include <string>
#include <sys/select.h>
#include <unistd.h>

#include "helpers/SerialComm/PtyDevice.hpp"
#include "helpers/SerialComm/WaitableData.hpp"

#include "SerialComm/serialComm.hpp"
#include "SerialComm/serialDetector.h"

bool isGitHubActions()
{
    return std::getenv("GITHUB_ACTIONS") != nullptr;
}

using namespace std::chrono_literals;

TEST(SerialCommTest, CanConstruct)
{
    PtyDevice pty;

    SerialComm serial{pty.slavePath(), 115200};

    SUCCEED();
}

TEST(SerialCommTest, StartAndStop)
{
    PtyDevice pty;

    SerialComm serial{pty.slavePath(), 115200};

    EXPECT_FALSE(serial.isRunning());

    serial.start();

    EXPECT_TRUE(serial.isRunning());

    serial.stop();

    EXPECT_FALSE(serial.isRunning());
}

TEST(SerialCommTest, Detect)
{
    if (isGitHubActions())
    {
        GTEST_SKIP() << "Only runs locally";
    }

    auto device = SerialDetector::findCastanetHub();

    EXPECT_FALSE(device.port.empty());
}