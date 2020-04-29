#include <chrono>
#include <thread>

#include <catch2.hpp>

#include <ThreadPool.hpp>
#include <threadpool/Job.hpp>
#include <threadpool/JobQueue.hpp>

namespace
{

auto get_value() -> int
{
    return 42;
}

auto wait_and_get_value() -> int
{
    std::this_thread::sleep_for(std::chrono::seconds{1});

    return 42;
}

}

TEST_CASE("Simple job push", "[ThreadPool]")
{
    shd::ThreadPool pool{1};

    auto future = pool.push(get_value);

    REQUIRE(future.get() == 42);
}

TEST_CASE("Basic Job parallelization", "[ThreadPool][Time]")
{
    shd::ThreadPool pool{4};

    auto start = std::chrono::system_clock::now();

    auto future1 = pool.push(wait_and_get_value);
    auto future2 = pool.push(wait_and_get_value);
    auto future3 = pool.push(wait_and_get_value);
    auto future4 = pool.push(wait_and_get_value);

    REQUIRE(future1.get() == 42);
    REQUIRE(future2.get() == 42);
    REQUIRE(future3.get() == 42);
    REQUIRE(future4.get() == 42);

    auto end = std::chrono::system_clock::now();

    REQUIRE(end - start < std::chrono::seconds{2});
}
