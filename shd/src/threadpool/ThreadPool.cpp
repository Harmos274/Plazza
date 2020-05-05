#include <vector>

#include <ThreadPool.hpp>

namespace shd
{

ThreadPool::ThreadPool(size_t thread_nbr)
{
    this->workers.reserve(thread_nbr);

    for (size_t pos = 0; pos < thread_nbr; ++pos)
    {
        this->workers.emplace_back(this->queue);
    }
}

ThreadPool::~ThreadPool()
{
    for (auto& worker : this->workers)
    {
        worker.setRunning(false);
    }

    this->queue.clear();

    for (auto& worker : this->workers)
    {
        while (worker.isRunning())
        {
            this->queue.notifyAll();
        }
    }
}

auto ThreadPool::size() const noexcept -> size_t
{
    return this->workers.size();
}

}
