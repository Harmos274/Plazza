/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** IngredientStock header
*/

#ifndef INGREDIENTSTOCK_HPP_
#define INGREDIENTSTOCK_HPP_

#include <array>
#include <chrono>

#include <pizzas/Pizza.hpp>

namespace plazza
{

class IngredientStock
{
public:
    using RegenTime = std::chrono::duration<size_t, std::milli>;

    IngredientStock(RegenTime regen_time) noexcept;
    IngredientStock(IngredientStock const& to_copy) noexcept = default;
    IngredientStock(IngredientStock&& to_move) noexcept = default;
    ~IngredientStock() noexcept = default;

    auto operator=(IngredientStock const& rhs) noexcept
        -> IngredientStock& = default;
    auto operator=(IngredientStock&& rhs) noexcept
        -> IngredientStock& = default;

    auto update() noexcept -> void;

    [[nodiscard]] auto hasIngredient(
        pizzas::ingredientsBitset ingredients) const noexcept -> bool;

    auto consumeIngredients(pizzas::ingredientsBitset ingredients) noexcept
        -> void;

private:
    using ClockType = std::chrono::system_clock;
    using Time = pizzas::bakingTime;

    std::array<size_t, 9> stock;
    std::chrono::time_point<ClockType, Time> last_regen;
    RegenTime regen_time;
};

}

#endif
