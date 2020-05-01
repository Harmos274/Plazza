/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Pizza class
*/

#include "pizzas/Pizza.hpp"
#include <sstream>

namespace plazza::pizzas
{

auto Pizza::pack() const noexcept -> std::string
{
    std::stringstream sstream;

    sstream << this->name << " " << this->size << " : " << this->ingredients;
    return std::string(sstream.str());
}

auto Pizza::getName() const noexcept -> std::string_view
{
    return this->name;
}

auto Pizza::getSize() const noexcept -> enum size
{
    return this->size;
}

auto Pizza::getBakingTime() const noexcept -> bakingTime
{
    return this->baking_time;
}

auto Pizza::getIngredients() const noexcept -> ingredientsBitset
{
    return this->ingredients;
}

auto operator<<(std::ostream& os, size pizza_size) -> std::ostream&
{
    switch (pizza_size)
    {
        case size::S:
            os << "S";
            break;
        case size::M:
            os << "M";
            break;
        case size::L:
            os << "L";
            break;
        case size::XL:
            os << "XL";
            break;
        case size::XXL:
            os << "XXL";
            break;
    }
    return os;
}

}
