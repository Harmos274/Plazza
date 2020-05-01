/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Marmiton
*/

#ifndef MARMITON_HPP_
#define MARMITON_HPP_

#include "exception.hpp"
#include "pizzas/Ingredient.hpp"
#include "pizzas/Recipe.hpp"
#include <algorithm>
#include <array>
#include <optional>

namespace plazza
{
constexpr std::array marmiton{
    pizzas::Recipe("Margarita",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::GRUYERE,
                   pizzas::bakingTime{1}),

    pizzas::Recipe("Regina",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::GRUYERE | pizzas::ingredient::HAM |
                       pizzas::ingredient::MUSHROOMS,
                   pizzas::bakingTime{2}),

    pizzas::Recipe("Americana",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::GRUYERE | pizzas::ingredient::STEAK,
                   pizzas::bakingTime{2}),

    pizzas::Recipe("Fantasia",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::EGGPLANT |
                       pizzas::ingredient::GOAT_CHEESE |
                       pizzas::ingredient::CHIEF_LOVE,
                   pizzas::bakingTime{4}),
};

using Marmiton = decltype(marmiton);

auto operator>>(std::string_view pizza_name, Marmiton marmiton) -> pizzas::Recipe const&;

}

#endif // MARMITON_HPP_
