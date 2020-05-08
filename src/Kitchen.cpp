/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Kitchen source file
*/

#include <chrono>

#include <Kitchen.hpp>
#include <Reception.hpp>
#include <pizzas/Pizza.hpp>
#include <pizzas/Recipe.hpp>

namespace plazza
{

namespace
{

auto pizzaiolo(std::atomic<pizzas::bakingTime>& duration_sync) -> void
{
    using ClockType = std::chrono::system_clock;

    pizzas::bakingTime duration = duration_sync.load(std::memory_order_relaxed);
    pizzas::bakingTime hundredth = duration / 100;
    auto now = ClockType::now();
    auto end_time = now + duration;

    while (now < end_time)
    {
        duration_sync.store(end_time - now, std::memory_order_relaxed);

        std::this_thread::sleep_for(std::min(
            hundredth,
            std::chrono::duration_cast<
                std::chrono::duration<double, std::milli>>(end_time - now)));

        now = ClockType::now();
    }
    duration_sync.store(pizzas::bakingTime::zero(), std::memory_order_relaxed);
}

}

Kitchen::Order::Order(pizzas::Recipe const& recipe,
                      pizzas::size size,
                      double multiplier) noexcept
    : recipe{recipe}, size{size}, time{recipe.getBakingTime() * multiplier}
{
}

auto Kitchen::Order::getRecipe() const noexcept -> pizzas::Recipe const&
{
    return this->recipe.get();
}

auto Kitchen::Order::getSize() const noexcept -> pizzas::size
{
    return this->size;
}

auto Kitchen::Order::getTime() const noexcept -> PizzaTime const&
{
    return this->time;
}

auto Kitchen::Order::getTime() noexcept -> PizzaTime&
{
    return this->time;
}

auto Kitchen::Order::getPizza() const noexcept -> pizzas::Pizza
{
    return pizzas::Pizza(this->recipe.get().getName(),
                         this->recipe.get().getIngredient(),
                         this->recipe.get().getBakingTime(),
                         this->size);
}

Kitchen::Kitchen(size_t cook_nbr, IngredientStock::RegenTime regen) noexcept
    : pool{cook_nbr}, stock{regen}
{
}

auto Kitchen::getTimeUntilReady() const noexcept -> pizzas::bakingTime
{
    if (this->orders.size() >= 2 * this->pool.size())
    {
        return pizzas::bakingTime::max();
    }
    return std::accumulate(this->orders.begin(),
                           this->orders.end(),
                           pizzas::bakingTime{0},
                           [](pizzas::bakingTime ret, Order const& order) {
                               return ret + order.getTime().getRemaining();
                           });
}

auto Kitchen::timeUntilNextPizza() const noexcept -> pizzas::bakingTime
{
    if (this->orders.empty())
    {
        return pizzas::bakingTime::zero();
    }

    auto end = std::min(this->pool.size(), this->orders.size());

    auto min = std::min_element(this->orders.begin(),
                                this->orders.begin() + end,
                                [](auto const& lhs, auto const& rhs) {
                                    return lhs.getTime().getRemaining() <
                                           rhs.getTime().getRemaining();
                                });

    return min->getTime().getRemaining();
}

auto Kitchen::pushOrder(Order new_order) noexcept -> void
{
    this->stock.consumeIngredients(new_order.getRecipe().getIngredient());

    this->orders.push_back(std::move(new_order));

    this->pool.push(pizzaiolo,
                    this->orders.back().getTime().getRemainingSync());
}

auto Kitchen::getOrders() const noexcept -> std::vector<Order> const&
{
    return this->orders;
}

auto Kitchen::collectFinishedOrders() noexcept -> std::vector<pizzas::Pizza>
{
    auto ret = std::vector<pizzas::Pizza>{};

    size_t pos = 0;

    while (pos < orders.size())
    {
        if (this->orders[pos].getTime().getRemaining() ==
            pizzas::bakingTime::zero())
        {
            ret.push_back(this->orders[pos].getPizza());

            this->orders.erase(this->orders.begin() + pos);
        }
        else
        {
            ++pos;
        }
    }
    return ret;
}

auto Kitchen::infoString() noexcept -> std::string
{
    auto ret = std::string{this->stock.infoString()};

    ret.append(1, '\n');
    auto original_size = ret.size();

    for (auto const& order : this->orders)
    {
        auto duration = order.getTime().getDuration();
        auto remaining = order.getTime().getRemaining();
        auto percentage = static_cast<size_t>(
            (duration.count() - remaining.count()) / duration.count() * 100);

        ret.append(order.getRecipe().getName())
            .append(1, ' ')
            .append(Reception::pizzaSizeToStr(order.getSize()))
            .append(" : ")
            .append(std::to_string(percentage))
            .append("%\n");
    }
    if (ret.size() > original_size)
    {
        ret.pop_back();
    }
    else
    {
        ret.append("This kitchen is inactive");
    }
    return ret;
}

auto Kitchen::getStock() noexcept -> IngredientStock&
{
    return this->stock;
}

auto Kitchen::hasRoom() const noexcept -> bool
{
    return this->pool.size() * 2 > this->orders.size();
}

}
