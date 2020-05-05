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
#include "Reception.hpp"
#include <algorithm>
#include <array>
#include <optional>

namespace plazza
{
constexpr std::array marmiton{
    pizzas::Recipe("margarita",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::GRUYERE,
                   pizzas::bakingTime{1000}),

    pizzas::Recipe("regina",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::GRUYERE | pizzas::ingredient::HAM |
                       pizzas::ingredient::MUSHROOMS,
                   pizzas::bakingTime{2000}),

    pizzas::Recipe("americana",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::GRUYERE | pizzas::ingredient::STEAK,
                   pizzas::bakingTime{2000}),

    pizzas::Recipe("fantasia",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::EGGPLANT |
                       pizzas::ingredient::GOAT_CHEESE |
                       pizzas::ingredient::CHIEF_LOVE,
                   pizzas::bakingTime{4000}),
};

using Marmiton = decltype(marmiton);

auto operator>>(std::string_view pizza_name, Marmiton const& marmiton) -> pizzas::Recipe const&;

}

#endif // MARMITON_HPP_
