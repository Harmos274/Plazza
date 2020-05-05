/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Kitchen header file
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <algorithm>
#include <chrono>
#include <numeric>

#include <shd/ThreadPool.hpp>

#include <IngredientStock.hpp>
#include <PizzaTime.hpp>
#include <pizzas/Pizza.hpp>
#include <pizzas/Recipe.hpp>

namespace plazza
{

class Kitchen
{
public:
    class Order
    {
    public:
        Order(pizzas::Recipe const& recipe,
              pizzas::size size,
              double multiplier) noexcept;
        Order(Order&& to_move) noexcept = default;
        ~Order() noexcept = default;

        auto operator=(Order&& rhs) noexcept -> Order& = default;

        [[nodiscard]] auto getRecipe() const noexcept -> pizzas::Recipe const&;
        [[nodiscard]] auto getSize() const noexcept -> pizzas::size;
        [[nodiscard]] auto getTime() const noexcept -> PizzaTime const&;
        [[nodiscard]] auto getTime() noexcept -> PizzaTime&;
        [[nodiscard]] auto getPizza() const noexcept -> pizzas::Pizza;

    private:
        std::reference_wrapper<pizzas::Recipe const> recipe;
        pizzas::size size;
        PizzaTime time;
    };

    Kitchen(size_t cook_nbr, IngredientStock::RegenTime regen) noexcept;
    Kitchen(Kitchen const& to_copy) noexcept = delete;
    Kitchen(Kitchen&& to_move) noexcept = delete;
    ~Kitchen() noexcept = default;

    auto operator=(Kitchen const& rhs) noexcept -> Kitchen& = delete;
    auto operator=(Kitchen&& rhs) noexcept -> Kitchen& = delete;

    [[nodiscard]] auto getTimeUntilReady() const noexcept -> pizzas::bakingTime;

    [[nodiscard]] auto timeUntilNextPizza() const noexcept
        -> pizzas::bakingTime;

    auto pushOrder(Order new_order) noexcept -> void;
    auto collectFinishedOrders() noexcept -> std::vector<pizzas::Pizza>;
    [[nodiscard]] auto getOrders() const noexcept -> std::vector<Order> const&;

    [[nodiscard]] auto infoString() const noexcept -> std::string;

    [[nodiscard]] auto getStock() const noexcept -> IngredientStock const&;

    [[nodiscard]] auto hasRoom() const noexcept -> bool;

private:
    shd::ThreadPool pool;
    std::vector<Order> orders;
    IngredientStock stock;
};

}

#endif
