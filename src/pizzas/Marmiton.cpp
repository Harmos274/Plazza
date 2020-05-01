/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Marmiton operator
*/

#include "Marmiton.hpp"
#include <iterator>

namespace plazza
{
auto operator>>(std::string_view pizza_name, Marmiton marmiton) -> pizzas::Recipe const&
{
    auto const* recipe = std::find_if(marmiton.begin(), marmiton.end(),
            [pizza_name](auto const& recipe) {
                return (recipe.getName() == pizza_name);
            });

    if (recipe == marmiton.end())
    {
        throw RecipeException("Can't find pizza recipe on Marmiton.");
    }
    return *recipe;
}

}
