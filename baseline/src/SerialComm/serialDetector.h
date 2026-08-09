#pragma once
#include <vector>
#include <string>
#include <cstdint>

struct SerialDevice
{
    std::string port = "";
    std::string description = "";
    std::string manufacturer = "";
    std::string serialNumber = "";
};

class SerialDetector
{
public:
    static SerialDevice findCastanetHub();

private:
    static const std::uint16_t CASTANETS_VID = 0x303a;
    static const std::uint16_t CASTANETS_PID = 0x4001;
    static std::vector<SerialDevice> enumerate(std::uint16_t vid = CASTANETS_VID, std::uint16_t pid = CASTANETS_PID);

#ifdef _WIN32
    static std::vector<SerialDevice> enumerateWindows(std::uint16_t vid, std::uint16_t pid);
#endif
#ifdef __linux__
    static std::vector<SerialDevice> enumerateLinux(std::uint16_t vid, std::uint16_t pid);
#endif
};