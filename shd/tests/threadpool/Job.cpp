#include <functional>

#include <catch2.hpp>

#include <threadpool/Job.hpp>

namespace
{

auto multiply(int lhs, int rhs) -> int
{
    return lhs * rhs;
}

auto copy_string_value(std::string str) -> std::string
{
    return str;
}

auto copy_string_ref(std::string& str) -> std::string
{
    return str;
}

auto copy_string_const_ref(std::string const& str) -> std::string
{
    return str;
}

class Movable
{
public:
    Movable(int value) noexcept : value{value}
    {
    }
    Movable(Movable const& to_copy) noexcept = delete;
    Movable(Movable&& to_move) noexcept = default;
    ~Movable() noexcept = default;

    auto operator=(Movable const& rhs) noexcept -> Movable& = delete;
    auto operator=(Movable&& rhs) noexcept -> Movable& = default;

    [[nodiscard]] auto getValue() const -> int
    {
        return this->value;
    }

    auto setValue(int value) -> void
    {
        this->value = value;
    }

private:
    int value;
};

}

TEST_CASE("Job with function pointer", "[Job][threadpool][shd]")
{
    auto job = shd::threadpool::Job{multiply, 2, 10};
    auto future = job.getFuture();

    job.launch();
    REQUIRE(future.get() == 20);
}

TEST_CASE("Job with lambda", "[Job][threadpool][shd]")
{
    auto job =
        shd::threadpool::Job{[](int lhs, int rhs) { return lhs * rhs; }, 2, 10};
    auto future = job.getFuture();

    job.launch();
    REQUIRE(future.get() == 20);
}

TEST_CASE("Job with copied values", "[Job][threadpool][shd]")
{
    auto job =
        shd::threadpool::Job{copy_string_value, std::string{"Toothless"}};
    auto future = job.getFuture();

    job.launch();
    REQUIRE(future.get() == "Toothless");
}

TEST_CASE("Job with reference argument", "[Job][threadpool][shd]")
{
    auto str = std::string{"Nightfury"};
    auto job = shd::threadpool::Job{copy_string_ref, std::ref(str)};
    auto future = job.getFuture();

    str.assign("Get down");

    job.launch();
    REQUIRE(future.get() == "Get down");
}

TEST_CASE("Job with const reference argument", "[Job][threadpool][shd]")
{
    auto str = std::string{"Nightfury"};
    auto job = shd::threadpool::Job{copy_string_const_ref, std::ref(str)};
    auto future = job.getFuture();

    job.launch();
    REQUIRE(future.get() == "Nightfury");
}

TEST_CASE("Job with moved argument", "[Job][threadpool][shd]")
{
    auto str = std::string{"Nightfury"};
    auto job = shd::threadpool::Job{
        [](std::string str) { return str; }, std::move(str)};
    auto future = job.getFuture();

    str.assign("Get down");

    job.launch();
    REQUIRE(future.get() == "Nightfury");
}

TEST_CASE("Job with non-copyable argument", "[Job][threadpool][shd]")
{
    auto mov = Movable{42};
    auto job = shd::threadpool::Job{
        [](Movable mov) { return mov.getValue(); }, std::move(mov)};
    auto future = job.getFuture();

    mov.setValue(84);

    job.launch();
    REQUIRE(future.get() == 42);
}
