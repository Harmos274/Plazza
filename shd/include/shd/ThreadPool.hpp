#ifndef THREAD_POOL_HPP_
#define THREAD_POOL_HPP_

#include <vector>

#include <threadpool/Job.hpp>
#include <threadpool/JobQueue.hpp>
#include <threadpool/Worker.hpp>

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

private:
    threadpool::JobQueue queue;
    std::vector<threadpool::Worker> workers;
};

}

#endif
