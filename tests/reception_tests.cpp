/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** reception unit tests
*/

#include "Reception.hpp"
#include "include/catch2.hpp"
#include <chrono>

TEST_CASE("Reception arg parser", "Arg parser")
{
    SECTION("well formated input")
    {
        constexpr auto av = std::array<char const*, 4>{"./plazza", "2", "5", "2000"};
        CHECK_NOTHROW(plazza::Reception(4, av.data()));
    }

    SECTION("Fucked up input")
    {
        constexpr auto av = std::array<char const*, 4>{"./plaaazza", "aaaa2", "aaa5", "200aaaa0"};
        CHECK_THROWS(plazza::Reception(4, av.data()));
    }

    SECTION("Not enough input")
    {
        constexpr auto av = std::array<char const*, 1>{"./plaaazza"};
        CHECK_THROWS(plazza::Reception(1, av.data()));
    }
    SECTION("Arguments")
    {
        using namespace std::chrono_literals;

        constexpr auto av = std::array<char const*, 4>{"./plazza", "2", "5", "2000"};
        auto rec = plazza::Reception(4, av.data());

        CHECK(rec.getMultiplier() == 2);
        CHECK(rec.getCookNbr() == 5);
        CHECK(rec.getRestockTime() == 2000ms);
    }
}

TEST_CASE("Reception input parser", "input parser")
{
    SECTION("well formated input")
    {
        auto za = plazza::Reception::parseOrder("regina XXL x2; fantasia M x3; margarita S x1");

        CHECK(za.size() == 6);
        CHECK(za[1].size == plazza::pizzas::size::XXL);
        CHECK(za[1].recipe.get().getName() == "regina");
    }

    SECTION("Fucked up input")
    {

        auto za = plazza::Reception::parseOrder("regioina XaXL x2; fantasia M x; margarita S x1");

        CHECK(za.size() == 1);
        CHECK(za[0].size == plazza::pizzas::size::S);
        CHECK(za[0].recipe.get().getName() == "margarita");
    }
    SECTION("Good middle pizza")
    {

        auto za = plazza::Reception::parseOrder("regioina XaXL x2; fantasia M x1; margarita S xk");

        CHECK(za.size() == 1);
        CHECK(za[0].size == plazza::pizzas::size::M);
        CHECK(za[0].recipe.get().getName() == "fantasia");
    }
}

TEST_CASE("Receptiion deserializer", "input parser")
{
    SECTION("Well serialized string")
    {
        auto pizza = plazza::Reception::deserializePizza("margarita XL : 🦌💀🍅🧀");

        CHECK(pizza.getName() == "margarita");
        CHECK(pizza.getSize() == plazza::pizzas::size::XL);
    }
    SECTION("Bad string")
    {
        CHECK_THROWS(plazza::Reception::deserializePizza("mar"));
    }
}
