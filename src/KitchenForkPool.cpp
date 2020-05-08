/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** KitchenForkPool source file
*/

#include <KitchenForkPool.hpp>

namespace plazza
{

KitchenForkPool::KitchenForkPool(size_t cook_nbr,
                                 double time_multiplier,
                                 std::chrono::milliseconds regen_time) noexcept
    : cook_nbr{cook_nbr},
      time_multiplier{time_multiplier},
      regen_time{regen_time}
{
}

auto KitchenForkPool::pushOrder(const Reception::Order& order) -> void
{
    auto iter = this->kitchen_forks.end();

    if (!this->kitchen_forks.empty())
    {
        auto delays = std::vector<pizzas::bakingTime>{};

        delays.reserve(this->kitchen_forks.size());

        for (auto& kitchen : this->kitchen_forks)
        {
            kitchen.putOrder(order);
        }
        for (auto& kitchen : this->kitchen_forks)
        {
            delays.push_back(kitchen.getOrderResponse());
        }

        auto min = std::min_element(delays.begin(), delays.end());

        if (*min != pizzas::bakingTime::max())
        {
            iter = this->kitchen_forks.begin() +
                   std::distance(delays.begin(), min);
        }
    }

    if (iter == this->kitchen_forks.end())
    {
        this->kitchen_forks.emplace_back(this->cook_nbr,
                                         this->time_multiplier,
                                         this->regen_time,
                                         this->getNewForkId());
        this->kitchen_forks.back().putOrder(order);
        this->kitchen_forks.back().getOrderResponse();
        iter = this->kitchen_forks.begin() + (this->kitchen_forks.size() - 1);
    }

    iter->confirmOrder();

    for (auto& kitchen : this->kitchen_forks)
    {
        kitchen.cancelOrder();
    }
}

auto KitchenForkPool::cull() -> void
{
    if (!this->kitchen_forks.empty())
    {
        this->kitchen_forks.erase(
            std::remove_if(
                this->kitchen_forks.begin(),
                this->kitchen_forks.end(),
                [](KitchenFork& kitchen) { return kitchen.shouldClose(); }),
            this->kitchen_forks.end());
    }
}

auto KitchenForkPool::getForks() noexcept -> std::vector<KitchenFork>&
{
    return this->kitchen_forks;
}

auto KitchenForkPool::getNewForkId() const noexcept -> KitchenFork::Id
{
    if (this->kitchen_forks.empty())
    {
        return 0;
    }
    return this->kitchen_forks.back().getId() + 1;
}

}
