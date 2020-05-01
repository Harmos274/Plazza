/*
** EPITECH PROJECT, 2020
** Plazza
** File description:
** Abstract class for pizzas
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include "Ingredient.hpp"
#include <chrono>
#include <string>

namespace plazza::pizzas
{

using bakingTime = std::chrono::duration<double, std::milli>;
using ingredientsBitset = ingredient;

enum class size
{
    S,
    M,
    L,
    XL,
    XXL
};
auto operator<<(std::ostream& os, size pizza_size) -> std::ostream&;

class Pizza {
  public:
    explicit Pizza(std::string_view const name,
                   ingredientsBitset const ingrediens,
                   bakingTime const baking_time,
                   enum size const size) :
        name{name},
        ingredients{ingrediens},
        baking_time{baking_time},
        size{size} {};
    ~Pizza() = default;

    [[nodiscard]] auto pack() const noexcept -> std::string;
    [[nodiscard]] auto getName() const noexcept -> std::string_view;
    [[nodiscard]] auto getSize() const noexcept -> size;
    [[nodiscard]] auto getIngredients() const noexcept -> ingredientsBitset;
    [[nodiscard]] auto getBakingTime() const noexcept -> bakingTime;

  private:
    std::string_view const name;
    ingredientsBitset const ingredients;
    bakingTime const baking_time;
    enum size const size;
};

}

#endif // PIZZA_HPP_
