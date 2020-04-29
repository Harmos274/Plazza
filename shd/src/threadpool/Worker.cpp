#include <thread>

#include <threadpool/JobQueue.hpp>
#include <threadpool/Worker.hpp>

namespace shd::threadpool
{

Worker::Worker(JobQueue& queue)
    : thread{&Worker::loop, this},
      keep_running{true},
      is_running{true},
      queue{queue}
{
}

Worker::Worker(Worker&& to_move) noexcept
    : thread{std::move(to_move.thread)},
      keep_running{to_move.keep_running.load()},
      queue{to_move.queue}
{
}

Worker::~Worker()
{
    this->setRunning(false);

    this->join();
}

auto Worker::operator=(Worker&& rhs) noexcept -> Worker&
{
    this->join();

    this->thread = std::move(rhs.thread);
    this->keep_running = rhs.keep_running.load();
    this->queue = rhs.queue;

    return *this;
}

auto Worker::setRunning(bool running) -> void
{
    this->keep_running.store(running, std::memory_order::relaxed);
}

auto Worker::isRunning() const noexcept -> bool
{
    return this->is_running.load(std::memory_order::relaxed);
}

auto Worker::loop() -> void
{
    while (this->keep_running.load(std::memory_order::relaxed) == true)
    {
        auto job = this->queue.get().takeJob();

        if (job != nullptr)
        {
            job->launch();
        }
    }
    this->is_running.store(false);
}

auto Worker::join() -> void
{
    if (this->thread.joinable())
    {
        this->thread.join();
    }
}

}
