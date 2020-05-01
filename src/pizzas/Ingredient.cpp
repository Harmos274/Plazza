/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** ingredient implementation
*/

#include "pizzas/Ingredient.hpp"
#include <algorithm>
#include <array>

namespace plazza::pizzas
{
auto operator<<(std::ostream& os, ingredient ingr_bitset) -> std::ostream&
{
    struct UnicodeIngredients
    {
        std::string str;
        ingredient bitset;
    };
    const std::array<UnicodeIngredients, 9> ingredients = {
        {{"🦌💀", ingredient::DOE},
         {"🍅", ingredient::TOMATO},
         {"🧀", ingredient::GRUYERE},
         {"🐷💀", ingredient::HAM},
         {"🍄", ingredient::MUSHROOMS},
         {"🐮💀", ingredient::STEAK},
         {"🍆", ingredient::EGGPLANT},
         {"🐐🧀", ingredient::GOAT_CHEESE},
         {"🇮🇹💘", ingredient::CHIEF_LOVE}}};

    std::for_each(ingredients.begin(), ingredients.end(),
                  [&](auto const& elem) {
                      if (static_cast<int>(elem.bitset) & static_cast<int>(ingr_bitset))
                      {
                          os << elem.str;
                      }
                  });
    return os;
}

}
