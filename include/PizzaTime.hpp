/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** PizzaTime header
*/

#include <atomic>
#include <memory>

#include <pizzas/Pizza.hpp>

#ifndef PIZZATIME_HPP_
#define PIZZATIME_HPP_

namespace plazza
{

class PizzaTime
{
public:
    PizzaTime(pizzas::bakingTime duration) noexcept
        : duration{duration},
          remaining{std::make_unique<std::atomic<pizzas::bakingTime>>(duration)}
    {
    }
    PizzaTime(PizzaTime&& to_move) noexcept = default;
    ~PizzaTime() noexcept = default;

    auto operator=(PizzaTime&& rhs) noexcept -> PizzaTime& = default;

    [[nodiscard]] auto getDuration() const -> pizzas::bakingTime
    {
        return this->duration;
    }

    [[nodiscard]] auto getRemaining() const -> pizzas::bakingTime
    {
        return this->remaining->load(std::memory_order_relaxed);
    }

    auto getRemainingSync() -> std::atomic<pizzas::bakingTime>&
    {
        return *this->remaining;
    }

private:
    pizzas::bakingTime duration;
    std::unique_ptr<std::atomic<pizzas::bakingTime>> remaining;
};

}

#endif
