#include <catch2.hpp>

#include <threadpool/Job.hpp>
#include <threadpool/JobQueue.hpp>

namespace
{

auto get_value() -> int
{
    return 42;
}

}

TEST_CASE("Simple job push and take", "[JobQueue][threadpool][shd]")
{
    shd::threadpool::JobQueue queue;
    
    auto future = queue.push(get_value);
    auto job = queue.takeJob();

    REQUIRE(job != nullptr);

    job->launch();

    REQUIRE(future.get() == 42);
}
