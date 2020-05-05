/*
** EPITECH PROJECT, 2020
** Plazza
** File description:
** Ingredient enum class
*/

#ifndef INGREDIENT_HPP_
#define INGREDIENT_HPP_

#include <ostream>

namespace plazza::pizzas
{
enum class ingredient : unsigned int
{
    DOE         = 1 << 0,
    TOMATO      = 1 << 1,
    GRUYERE     = 1 << 2,
    HAM         = 1 << 3,
    MUSHROOMS   = 1 << 4,
    STEAK       = 1 << 5,
    EGGPLANT    = 1 << 6,
    GOAT_CHEESE = 1 << 7,
    CHIEF_LOVE  = 1 << 8 // not sure about this one
};

constexpr auto operator|(ingredient lhs, ingredient rhs) -> ingredient
{
    return static_cast<ingredient>(static_cast<int>(lhs) |
                                   static_cast<int>(rhs));
}

auto operator<<(std::ostream& os, ingredient ingr_bitset) -> std::ostream&;

}

#endif // INGREDIENT_HPP_
