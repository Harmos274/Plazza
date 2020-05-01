#ifndef WORKER_HPP_
#define WORKER_HPP_

#include <atomic>
#include <thread>
#include <functional>

#include <shd/threadpool/JobQueue.hpp>

namespace shd::threadpool
{

class Worker
{
public:
    Worker(JobQueue& queue);
    Worker(Worker const& to_copy) = delete;
    Worker(Worker&& to_move) noexcept;
    ~Worker();

    auto operator=(Worker&& rhs) noexcept -> Worker&;

    auto setRunning(bool running) -> void;
    [[nodiscard]] auto isRunning() const noexcept -> bool;

private:
    auto loop() -> void;

    auto join() -> void;

    std::thread thread;
    std::atomic<bool> keep_running;
    std::atomic<bool> is_running;
    std::reference_wrapper<JobQueue> queue;
};

}

#endif
