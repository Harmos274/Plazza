/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Recipe (pizza factory)
*/

#ifndef RECEPE_HPP_
#define RECEPE_HPP_

#include "pizzas/Pizza.hpp"
#include <memory>

namespace plazza::pizzas
{
class Recipe {
  public:
    constexpr explicit Recipe(std::string_view const name,
                              ingredientsBitset const ingredients,
                              bakingTime const baking_time) :
        name{name},
        ingredients{ingredients},
        baking_time{baking_time} {}
    Recipe(Recipe const& copied) = delete;
    ~Recipe() = default;

    auto operator()(enum size size) const -> Pizza;

    [[nodiscard]] auto getName() const noexcept -> std::string_view;
    [[nodiscard]] auto getIngredient() const noexcept -> ingredientsBitset;
    [[nodiscard]] auto getBakingTime() const noexcept -> bakingTime;

  private:
    std::string_view  const name;
    ingredientsBitset const ingredients;
    bakingTime        const baking_time;
};

}
#endif
