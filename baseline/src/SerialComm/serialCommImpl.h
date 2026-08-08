#include "serialComm.hpp"

#include <asio.hpp>

#include <atomic>
#include <mutex>
#include <thread>

class SerialComm::Impl
{
public:
    Impl(
        std::string device,
        unsigned int baudRate);
    Impl();
    ~Impl();

    Impl(const Impl&) = delete;
    Impl& operator=(const Impl&) = delete;

    int start();
    int stop();

    void send(
        const std::uint8_t* data,
        std::size_t size);

    bool isRunning() const noexcept;

    Nano::Signal<void(const char*)>* getNewDataAvaliable();


private:
    void loop();

private:
    asio::io_context ioContext;
    asio::serial_port serial;

    std::thread thread;
    std::atomic_bool running{false};

    std::mutex writeMutex;
    Nano::Signal<void(const char*)> newDataAvaliable; 
};