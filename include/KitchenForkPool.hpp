/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** KitchenForkPool header file
*/

#include <chrono>
#include <vector>

#include <KitchenFork.hpp>

#ifndef KITCHENFORKPOOL_HPP_
#define KITCHENFORKPOOL_HPP_

namespace plazza
{

class KitchenForkPool
{
public:
    KitchenForkPool(size_t cook_nbr,
                    double time_multiplier,
                    std::chrono::milliseconds regen_time) noexcept;
    KitchenForkPool(KitchenForkPool const& to_copy) noexcept = default;
    KitchenForkPool(KitchenForkPool&& to_move) noexcept = default;
    ~KitchenForkPool() noexcept = default;

    auto operator=(KitchenForkPool const& rhs) noexcept
        -> KitchenForkPool& = default;
    auto operator=(KitchenForkPool&& rhs) noexcept
        -> KitchenForkPool& = default;

    auto pushOrder(Reception::Order const& order) -> void;

    auto cull() -> void;

    auto getForks() noexcept -> std::vector<KitchenFork>&;

private:
    [[nodiscard]] auto getNewForkId() const noexcept -> KitchenFork::Id;

    std::vector<KitchenFork> kitchen_forks;
    size_t cook_nbr;
    double time_multiplier;
    std::chrono::milliseconds regen_time;
};

}

#endif
