/*
** EPITECH PROJECT, 2020
** plaza
** File description:
** recipe implementation
*/

#include "pizzas/Recipe.hpp"
#include "pizzas/Pizza.hpp"
#include <unordered_map>

namespace plazza::pizzas
{
    auto Recipe::operator()(enum size size) const -> Pizza
    {
        return Pizza(this->name, this->ingredients, this->baking_time, size);
    }

    auto Recipe::getName() const noexcept -> std::string_view
    {
        return this->name;
    }

    auto Recipe::getIngredient() const noexcept -> ingredientsBitset
    {
        return this->ingredients;
    }

    auto Recipe::getBakingTime() const noexcept -> bakingTime
    {
        return this->baking_time;
    }
}
