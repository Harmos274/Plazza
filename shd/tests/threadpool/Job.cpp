#include <catch2.hpp>

#include <threadpool/Job.hpp>

namespace
{

auto multiply(int lhs, int rhs) -> int
{
    return lhs * rhs;
}

class Movable
{
public:
    Movable(int value) : value{value} {};
    Movable(Movable const& to_copy) = delete;
    Movable(Movable&& to_move) noexcept = default;
    ~Movable() = default;

    auto operator=(Movable&& rhs) noexcept -> Movable& = default;

    [[nodiscard]] auto getValue() const noexcept -> int
    {
        return this->value;
    }

private:
    int value;
};

}

TEST_CASE("Job with function pointer", "[Job]")
{
    auto job = shd::threadpool::Job{multiply, 2, 10};
    auto future = job.getFuture();

    job.launch();
    REQUIRE(future.get() == 20);
}

TEST_CASE("Job with lambda", "[Job]")
{
    auto job =
        shd::threadpool::Job{[](int lhs, int rhs) { return lhs * rhs; }, 2, 10};
    auto future = job.getFuture();

    job.launch();
    REQUIRE(future.get() == 20);
}

TEST_CASE("Job with non-copyable arguments")
{
    auto movable = Movable{20};
    auto job = shd::threadpool::Job{
        [](Movable const& movable) { return movable.getValue(); },
        std::move(movable)};
    auto future = job.getFuture();

    job.launch();
    REQUIRE(future.get() == 20);
}
