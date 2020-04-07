/*
** EPITECH PROJECT, 2020
** CCP_plaza_2019
** File description:
** pizza.hpp
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

namespace plazza
{
enum PizzaType
{
    REGINA = 1,
    MARGARITA = 1 << 1,
    AMERICANA = 1 << 2,
    FANATASIA = 1 << 3,
};

enum PizzaSize
{
    S = 1,
    M = 1 << 1,
    L = 1 << 2,
    XL = 1 << 3,
    XXL = 1 << 4
};

} // namespace plazza

#endif /* !PIZZA_HPP_ */

