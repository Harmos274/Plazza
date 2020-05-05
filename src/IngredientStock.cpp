/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** IngredientStock source file
*/

#include <IngredientStock.hpp>

namespace plazza
{

IngredientStock::IngredientStock(RegenTime regen_time) noexcept
    : stock{5, 5, 5, 5, 5, 5, 5, 5, 5},
      last_regen(ClockType::now()),
      regen_time{regen_time}
{
}

auto IngredientStock::update() noexcept -> void
{
    auto now = ClockType::now();
    auto elapsed_time = now - this->last_regen;
    size_t elapsed_cycles = elapsed_time / this->regen_time;
    auto current_cycle =
        std::chrono::duration_cast<RegenTime>(elapsed_time) %
        std::chrono::duration_cast<RegenTime>(this->regen_time);

    for (auto& ingredient : this->stock)
    {
        ingredient += elapsed_cycles;
    }

    this->last_regen = now - current_cycle;
}

auto IngredientStock::hasIngredient(
    pizzas::ingredientsBitset ingredients) const noexcept -> bool
{
    size_t pos = 0;

    while (pos < this->stock.size())
    {
        if ((static_cast<int>(ingredients) >> pos) & 1 && this->stock[pos] == 0)
        {
            return false;
        }
        ++pos;
    }
    return true;
}

auto IngredientStock::consumeIngredients(
    pizzas::ingredientsBitset ingredients) noexcept -> void
{
    size_t pos = 0;

    while (pos < this->stock.size())
    {
        if ((static_cast<int>(ingredients) >> pos) & 1)
        {
            this->stock[pos] -= 1;
        }
        ++pos;
    }
}

}
