#pragma once

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

class PtyDevice
{
public:
    PtyDevice()
    {
        masterFd_ = posix_openpt(O_RDWR | O_NOCTTY);

        if (masterFd_ < 0)
            throw std::runtime_error("posix_openpt() failed");

        if (grantpt(masterFd_) < 0)
            throw std::runtime_error("grantpt() failed");

        if (unlockpt(masterFd_) < 0)
            throw std::runtime_error("unlockpt() failed");

        const char* name = ptsname(masterFd_);

        if (!name)
            throw std::runtime_error("ptsname() failed");

        slavePath_ = name;
    }

    ~PtyDevice()
    {
        if (masterFd_ >= 0)
            close(masterFd_);
    }

    PtyDevice(const PtyDevice&) = delete;
    PtyDevice& operator=(const PtyDevice&) = delete;

    int masterFd() const noexcept
    {
        return masterFd_;
    }

    const std::string& slavePath() const noexcept
    {
        return slavePath_;
    }

private:
    int masterFd_{-1};
    std::string slavePath_;
};