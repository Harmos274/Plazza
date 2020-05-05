/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Kitchen header
*/

#ifndef KITCHENMANAGER_HPP_
#define KITCHENMANAGER_HPP_

#include <shd/WordIterator.hpp>

#include <Kitchen.hpp>
#include <Marmiton.hpp>
#include <Pipe.hpp>
#include <pizzas/Pizza.hpp>

namespace plazza
{

class KitchenManager
{
public:
    KitchenManager(size_t cook_nbr,
                   IngredientStock::RegenTime regen,
                   Pipe ipc,
                   double time_multiplier) noexcept;
    KitchenManager(KitchenManager const& to_copy) noexcept = delete;
    KitchenManager(KitchenManager&& to_move) noexcept = delete;
    ~KitchenManager() noexcept = default;

    auto operator=(KitchenManager const& rhs) noexcept
        -> KitchenManager& = delete;
    auto operator=(KitchenManager&& rhs) noexcept -> KitchenManager& = delete;

    auto answerOrder(pizzas::bakingTime time) noexcept;
    auto receiveOrder() noexcept;

    auto processEvents() noexcept;

    [[nodiscard]] auto isOpen() const noexcept;

    auto run() -> void;

private:
    Kitchen kitchen;
    Pipe ipc;
    double cooking_time_multiplier;
    std::optional<Kitchen::Order> potential_order;
    bool running{true};
};

}

#endif
