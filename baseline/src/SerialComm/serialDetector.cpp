#include "serialDetector.h"
#include "spdlog/spdlog.h"

#ifdef _WIN32
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>

#pragma comment(lib, "setupapi.lib")
#endif

#ifdef __linux__
#include <libudev.h>
#endif

SerialDevice SerialDetector::findCastanetHub()
{
    auto serial = enumerate();

    return serial.size() > 0 ? serial.front() : SerialDevice();
}

std::vector<SerialDevice> SerialDetector::enumerate(std::uint16_t vid, std::uint16_t pid)
{

#ifdef _WIN32
    return enumerateWindows(vid, pid);
#elif __linux__
    return enumerateLinux(vid, pid);
#endif

    return std::vector<SerialDevice>();
}

// TODO: NOT TESTED
#ifdef _WIN32
std::vector<SerialDevice> SerialDetector::enumerateWindows()
{
    GUID COM_PORT_GUID = {0x86e0d1e0, 0x8089, 0x11d0, {0x93, 0x49, 0x00, 0xa0, 0xc9, 0x0d, 0xca, 0xfa}};

    // Get all present devices matching the COM port interface GUID
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&COM_PORT_GUID, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (deviceInfoSet == INVALID_HANDLE_VALUE)
    {
        std::vector<SerialDevice>();
    }

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    DWORD deviceIndex = 0;

    // Enumerate through the devices in the list
    while (SetupDiEnumDeviceInfo(deviceInfoSet, deviceIndex, &deviceInfoData))
    {
        deviceIndex++;

        // Step 1: Query the Hardware ID string
        char hardwareId[512] = {0};
        if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)hardwareId, sizeof(hardwareId), NULL))
        {
            std::string hwIdStr(hardwareId);

            // Convert to uppercase to ensure a bulletproof match
            std::transform(hwIdStr.begin(), hwIdStr.end(), hwIdStr.begin(), ::toupper);

            // Step 2: Check if this string belongs to Espressif VID 303A & PID 4001
            if (hwIdStr.find("VID_303A") != std::string::npos && hwIdStr.find("PID_4001") != std::string::npos)
            {

                // Step 3: Open the device's registry key to grab the friendly COM port name
                HKEY deviceRegistryKey = SetupDiOpenDevRegKey(deviceInfoSet, &deviceInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
                if (deviceRegistryKey != INVALID_HANDLE_VALUE)
                {
                    char portName[64] = {0};
                    DWORD portNameSize = sizeof(portName);

                    LSTATUS status = RegQueryValueExA(deviceRegistryKey, "PortName", NULL, NULL, (PBYTE)portName, &portNameSize);
                    RegCloseKey(deviceRegistryKey);

                    if (status == ERROR_SUCCESS)
                    {
                        SetupDiDestroyDeviceInfoList(deviceInfoSet);
                        return std::string(portName); // Returns "COM3", "COM4", etc.
                    }
                }
            }
        }
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
    return ""; // Device not found or not plugged in
};
#endif

#ifdef __linux__

const char *uint16ToHex(std::uint16_t value, bool includePrefix = false, bool uppercase = true)
{
    // High-performance lookup arrays to avoid costly runtime calculations
    static constexpr std::string_view HEX_CHARS_UPPER = "0123456789ABCDEF";
    static constexpr std::string_view HEX_CHARS_LOWER = "0123456789abcdef";

    const std::string_view &hexAlphabet = uppercase ? HEX_CHARS_UPPER : HEX_CHARS_LOWER;

    // A uint16_t is exactly 4 hex characters.
    // We allocate a fixed buffer to completely avoid heap reallocations.
    std::array<char, 6> buffer;
    size_t index = 0;

    if (includePrefix)
    {
        buffer[index++] = '0';
        buffer[index++] = uppercase ? 'X' : 'x';
    }

    // Extract nibbles (4-bit chunks) from highest to lowest using bit shifts
    buffer[index++] = hexAlphabet[(value >> 12) & 0x0F]; // Nibble 4
    buffer[index++] = hexAlphabet[(value >> 8) & 0x0F];  // Nibble 3
    buffer[index++] = hexAlphabet[(value >> 4) & 0x0F];  // Nibble 2
    buffer[index++] = hexAlphabet[value & 0x0F];         // Nibble 1

    return std::string(buffer.data(), index).c_str();
}

std::uint16_t hexToUint16(const char *value)
{
    if (!value)
    {
        return 0;
    }

    unsigned int result = 0;
    std::sscanf(value, "%x", &result);
    return static_cast<std::uint16_t>(result);
}

std::vector<SerialDevice> SerialDetector::enumerateLinux(std::uint16_t vid, std::uint16_t pid)
{
    auto output = std::vector<SerialDevice>();

    udev *udevContext = udev_new();

    if (!udevContext)
    {
        return output;
    }

    udev_enumerate *enumerate = udev_enumerate_new(udevContext);

    if (!enumerate)
    {
        udev_unref(udevContext);
        return output;
    }

    udev_enumerate_add_match_subsystem(enumerate, "tty");
    udev_enumerate_add_match_property(enumerate, "ID_VENDOR_ID", uint16ToHex(vid));
    udev_enumerate_add_match_property(enumerate, "ID_MODEL_ID", uint16ToHex(pid));
    udev_enumerate_scan_devices(enumerate);

    udev_list_entry *devicesList = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry *entry = nullptr;

    udev_list_entry_foreach(entry, devicesList)
    {
        const char *syspath = udev_list_entry_get_name(entry);
        udev_device *device = udev_device_new_from_syspath(udevContext, syspath);

        if (!device)
            continue;

        const char *devnode = udev_device_get_devnode(device);

        if (!devnode)
        {
            udev_device_unref(device);
            continue;
        }

        udev_device *usb_parent = udev_device_get_parent_with_subsystem_devtype(
            device,
            "usb",
            "usb_device");

        const char *vid = nullptr;
        const char *pid = nullptr;

        if (usb_parent)
        {
            vid = udev_device_get_sysattr_value(usb_parent, "idVendor");
            pid = udev_device_get_sysattr_value(usb_parent, "idProduct");
        }

        spdlog::info("Checking node {0} -> VID: {1}, PID: {2}",
                     devnode,
                     vid ? vid : "NULL",
                     pid ? pid : "NULL");

        if (!vid || !pid || hexToUint16(vid) != CASTANETS_VID || hexToUint16(pid) != CASTANETS_PID)
        {
            udev_device_unref(device);
            continue;
        }

        SerialDevice serialDevice;

        serialDevice.port = devnode;
        serialDevice.manufacturer = udev_device_get_sysattr_value(usb_parent, "manufacturer");
        serialDevice.description = udev_device_get_property_value(device, "ID_MODEL");
        serialDevice.serialNumber = udev_device_get_property_value(device, "ID_SERIAL_SHORT");

        output.push_back(std::move(serialDevice));
        udev_device_unref(device);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udevContext);
    return output;
}
#endif