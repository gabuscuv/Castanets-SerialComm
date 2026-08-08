#include <vector>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <mutex>

class WaitableData
{
public:
    void set(std::vector<std::uint8_t> data)
    {
        {
            std::scoped_lock lock(mutex_);
            data_ = std::move(data);
        }

        condition_.notify_all();
    }

    bool waitFor(std::chrono::milliseconds timeout)
    {
        std::unique_lock lock(mutex_);

        return condition_.wait_for(
            lock,
            timeout,
            [this]
            {
                return !data_.empty();
            });
    }

    std::vector<std::uint8_t> data()
    {
        std::scoped_lock lock(mutex_);
        return data_;
    }

private:
    std::mutex mutex_;
    std::condition_variable condition_;

    std::vector<std::uint8_t> data_;
};
