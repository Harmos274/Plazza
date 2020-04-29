#ifndef JOB_QUEUE_HPP_
#define JOB_QUEUE_HPP_

#include <deque>
#include <mutex>
#include <type_traits>

#include <threadpool/Job.hpp>

namespace shd::threadpool
{

class JobQueue
{
public:
    JobQueue() = default;
    JobQueue(JobQueue const& to_copy) = delete;
    JobQueue(JobQueue&& to_move) noexcept = delete;
    ~JobQueue() = default;

    auto operator=(JobQueue&& rhs) noexcept -> JobQueue& = delete;

    template <typename T_func, typename... T_args>
    auto push(T_func&& func, T_args&&... args)
        -> std::future<std::invoke_result_t<T_func, T_args...>>
    {
        auto job = std::make_unique<Job<T_func, T_args...>>(
            std::forward<T_func>(func), std::forward<T_args>(args)...);
        auto future = job->getFuture();
        auto lock = std::lock_guard{this->mutex};

        this->queue.push_back(std::move(job));
        this->notifyOne();
        return future;
    }

    auto takeJob() -> std::unique_ptr<IJob>;

    auto clear() -> void;

    auto notifyAll() -> void;

private:
    auto notifyOne() -> void;

    std::deque<std::unique_ptr<IJob>> queue;
    std::condition_variable condition;
    std::mutex mutex;
};

}

#endif
