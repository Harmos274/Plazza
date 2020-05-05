/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Reception implementation
*/

#include "Reception.hpp"
#include "Marmiton.hpp"
#include "exception.hpp"
#include "shd/WordIterator.hpp"
#include <iostream>
#include <iterator>

namespace plazza
{
Reception::Reception(int ac, char const* const* av)
{
    using namespace std::chrono_literals;

    size_t pos = 0;

    if (ac < 4)
    {
        throw ArgumentException("Bad number of argument.");
    }

    std::string smultiplier = av[1];
    std::string snbr_cook = av[2];
    std::string srestock_time = av[3];

    this->multiplier = std::stod(smultiplier, &pos);
    if (pos != smultiplier.size() || this->multiplier <= 0)
    {
        throw ArgumentException("Invalid multiplier. Should be float");
    }

    this->nbr_cook = std::stoul(snbr_cook, &pos);
    if (pos != snbr_cook.size() or this->nbr_cook < 1)
    {
        throw ArgumentException(
            "Invalid cook number."
            "Should be positive non-null integer.");
    }

    this->restock_time =
        std::chrono::milliseconds{std::stoul(srestock_time, &pos)};
    if (pos != srestock_time.size() or this->restock_time < 1ms)
    {
        throw ArgumentException(
            "Invalid restock couldown."
            "Should be non-nul positive.");
    }
}

auto Reception::deserializePizza(std::string const& serialized_pizza)
    -> pizzas::Pizza
{
    shd::WordIterator<' '> serial_selector{serialized_pizza};
    auto const& recipe = *serial_selector >> marmiton;

    ++serial_selector;
    if (serial_selector == serial_selector.end())
    {
        throw DeserializingException("Fail to deserialize pizza.");
    }
    return recipe(Reception::strToPizzasize(*serial_selector));
}

constexpr auto dict_str_pizzas =
    std::array<std::pair<std::string_view, pizzas::size>, 5>{
        {{"S", pizzas::size::S},
         {"M", pizzas::size::M},
         {"L", pizzas::size::L},
         {"XL", pizzas::size::XL},
         {"XXL", pizzas::size::XXL}}};

auto Reception::pizzaSizeToStr(pizzas::size pizza_size) -> std::string
{
    auto const* it =
        std::find_if(dict_str_pizzas.begin(),
                     dict_str_pizzas.end(),
                     [pizza_size](auto pair_str_pizza) {
                         return (pizza_size == pair_str_pizza.second);
                     });

    if (it != dict_str_pizzas.end())
    {
        return std::string(it->first);
    }
    throw SerializingException("Fail to serialize pizza size.");
}

auto Reception::strToPizzasize(std::string_view str) -> pizzas::size
{
    auto const* it = std::find_if(
        dict_str_pizzas.begin(),
        dict_str_pizzas.end(),
        [str](auto pair_str_pizza) { return (str == pair_str_pizza.first); });

    if (it != dict_str_pizzas.end())
    {
        return it->second;
    }
    throw DeserializingException("Fail to get size in str.");
}

auto Reception::parseOrder(std::string const& sorders) -> std::vector<Order>
{
    shd::WordIterator<';'> order_selector{sorders};
    std::vector<Order> orders;

    for (auto order : order_selector)
    {
        shd::WordIterator<' '> order_attributes{order};

        try
        {
            // refacto later
            // std::distance unimplemented in word iterator
            if (order_attributes != order_attributes.end())
            {
                auto const& recipe = *order_attributes >> marmiton;
                ++order_attributes;

                if (order_attributes != order_attributes.end())
                {
                    auto pizza_size = strToPizzasize(*order_attributes);
                    ++order_attributes;

                    if (order_attributes != order_attributes.end())
                    {
                        size_t nbr_pizza = 0;

                        if ((*order_attributes)[0] == 'x')
                        {
                            nbr_pizza = std::stoul(
                                std::string(*order_attributes).substr(1));

                            ++order_attributes;
                        }
                        if (order_attributes == order_attributes.end())
                        {
                            std::vector<Order> inserted{
                                nbr_pizza, Order{recipe, pizza_size}};

                            orders.insert(
                                orders.end(),
                                std::make_move_iterator(inserted.begin()),
                                std::make_move_iterator(inserted.end()));
                        }
                    }
                }
            }
        }
        catch (std::exception const& e)
        {
        }
    }
    return orders;
}

auto Reception::getMultiplier() const -> double
{
    return this->multiplier;
}

auto Reception::getCookNbr() const -> size_t
{
    return this->nbr_cook;
}

auto Reception::getRestockTime() const -> std::chrono::milliseconds
{
    return this->restock_time;
}

}
