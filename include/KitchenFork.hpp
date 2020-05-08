/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** KitchenFork header
*/

#ifndef KITCHENFORK_HPP_
#define KITCHENFORK_HPP_

#include <chrono>

#include <IpcFork.hpp>
#include <Reception.hpp>
#include <KitchenManager.hpp>

namespace plazza
{

class KitchenFork : public IpcFork
{
public:
    using Id = size_t;

    KitchenFork(size_t cook_nbr,
                double time_multiplier,
                IngredientStock::RegenTime regen,
                size_t id);
    KitchenFork(KitchenFork const& to_copy) noexcept = delete;
    KitchenFork(KitchenFork&& to_move) noexcept = default;
    ~KitchenFork() noexcept
    {
        this->sendClose();
    }

    auto operator=(KitchenFork const& rhs) noexcept -> KitchenFork& = delete;
    auto operator=(KitchenFork&& rhs) noexcept -> KitchenFork&;

    auto sendClose() noexcept -> void;

    auto getState() noexcept -> std::string&;

    auto putOrder(Reception::Order const& order) -> void;
    auto getOrderResponse() -> pizzas::bakingTime;
    auto cancelOrder() -> void;
    auto confirmOrder() -> void;
    auto requestState() -> void;

    auto updateState() -> std::optional<kitchen_action>;

    auto collectFinishedOrders() noexcept -> std::vector<pizzas::Pizza>;

    [[nodiscard]] auto getId() const noexcept -> size_t;

    [[nodiscard]] auto shouldClose() const noexcept -> bool;

private:
    using ClockType = std::chrono::system_clock;

    std::string latest_state;
    std::vector<pizzas::Pizza> to_deliver;
    std::chrono::time_point<ClockType> last_pizza;
    size_t current_orders{0};
    Id id;
};

}

#endif
