#ifndef THREAD_POOL_HPP_
#define THREAD_POOL_HPP_

#include <vector>

#include <shd/threadpool/Job.hpp>
#include <shd/threadpool/JobQueue.hpp>
#include <shd/threadpool/Worker.hpp>

namespace shd
{

class ThreadPool
{
public:
    ThreadPool(size_t thread_nbr);
    ThreadPool(ThreadPool const& to_copy) = delete;
    ~ThreadPool();

    template <typename T_func, typename... T_args>
    auto push(T_func&& func, T_args&&... args)
        -> std::future<std::invoke_result_t<T_func, T_args...>>
    {
        return this->queue.push(std::forward<T_func>(func),
                                std::forward<T_args>(args)...);
    }

    [[nodiscard]] auto size() const noexcept -> size_t;

private:
    threadpool::JobQueue queue;
    std::vector<threadpool::Worker> workers;
};

}

#endif
