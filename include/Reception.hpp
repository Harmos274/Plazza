/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "pizzas/Pizza.hpp"
#include "pizzas/Recipe.hpp"
#include <chrono>
#include <functional>
#include <vector>

namespace plazza
{
class Reception
{
public:
    struct Order
    {
        Order(pizzas::Recipe const& rec, enum pizzas::size size)
            : recipe{rec}, size{size}
        {
        }
        Order() = delete;
        Order(Order&& moved) = default;
        Order(Order const& copied) = default;
        ~Order() = default;

        auto operator=(Order&& moved) noexcept -> Order& = default;

        std::reference_wrapper<pizzas::Recipe const> recipe;
        enum pizzas::size size;
    };

    Reception(int ac, char const* const* av);
    ~Reception() = default;

    static auto deserializePizza(std::string const& serialized_pizza)
        -> pizzas::Pizza;
    static auto pizzaSizeToStr(pizzas::size pizza_size) -> std::string;
    static auto strToPizzasize(std::string_view str) -> pizzas::size;
    static auto parseOrder(std::string const& sorders) -> std::vector<Order>;

    [[nodiscard]] auto getMultiplier() const -> double;
    [[nodiscard]] auto getCookNbr() const -> size_t;
    [[nodiscard]] auto getRestockTime() const -> std::chrono::milliseconds;

private:
    double multiplier;
    size_t nbr_cook;
    std::chrono::milliseconds restock_time;
};

}

#endif // RECEPTION_HPP_
