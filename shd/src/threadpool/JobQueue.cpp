#include <mutex>

#include <threadpool/JobQueue.hpp>

namespace shd::threadpool
{

auto JobQueue::notifyAll() -> void
{
    this->condition.notify_all();
}

auto JobQueue::notifyOne() -> void
{
    this->condition.notify_one();
}

auto JobQueue::takeJob() -> std::unique_ptr<IJob>
{
    auto lock = std::unique_lock{this->mutex};

    if (this->queue.empty())
    {
        this->condition.wait(lock);
    }
    if (!this->queue.empty())
    {
        auto ret = std::move(this->queue.front());

        this->queue.pop_front();
        return ret;
    }
    return nullptr;
}

auto JobQueue::clear() -> void
{
    auto lock = std::lock_guard{this->mutex};

    this->queue.clear();
}

}
