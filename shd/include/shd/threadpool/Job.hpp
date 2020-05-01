#ifndef JOB_HPP_
#define JOB_HPP_

#include <future>
#include <tuple>
#include <type_traits>
#include <utility>

namespace shd::threadpool
{

struct IJob
{
public:
    virtual ~IJob() = default;
    virtual auto launch() -> void = 0;
};

template <typename T_func, typename... T_args>
class Job : public IJob
{
    using retType = typename std::invoke_result_t<T_func&&, T_args&&...>;

    static_assert(std::is_invocable_v<T_func&&, T_args&&...>, "Not a callable");

public:
    Job() = delete;
    Job(Job const& to_copy) = delete;
    Job(Job&& to_copy) noexcept = default;

    Job(T_func&& func, T_args&&... args)
        : task{std::forward<T_func>(func)}, args{std::forward<T_args>(args)...}
    {
    }

    ~Job() override = default;

    auto operator=(Job&& rhs) noexcept -> Job& = default;

    auto launch() -> void override
    {
        std::apply(this->task, std::move(this->args));
    }

    auto getFuture() -> std::future<retType>
    {
        return this->task.get_future();
    }

private:
    std::packaged_task<retType(T_args...)> task;
    std::tuple<T_args...> args;
};

}

#endif
