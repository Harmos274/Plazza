#include <catch2.hpp>

#include <threadpool/Job.hpp>
#include <threadpool/JobQueue.hpp>
#include <threadpool/Worker.hpp>

namespace
{

auto get_value() -> int
{
    return 42;
}

}

TEST_CASE("Simple Worker test", "[Worker]")
{
    shd::threadpool::JobQueue queue;

    auto future = queue.push(get_value);

    auto worker = shd::threadpool::Worker{queue};

    REQUIRE(future.get() == 42);

    worker.setRunning(false);
    while (worker.isRunning())
    {
        queue.notifyAll();
    }
}
