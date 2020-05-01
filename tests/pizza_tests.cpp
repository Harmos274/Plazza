/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** unit test for pizzas
*/

#include "include/catch2.hpp"
#include "pizzas/Ingredient.hpp"
#include "pizzas/Pizza.hpp"
#include "Marmiton.hpp"
#include <chrono>
#include <sstream>
#include <string>

TEST_CASE("Ingredient enum", "operators")
{
    using plazza::pizzas::ingredient;

    SECTION("| operator")
    {
        ingredient ing = ingredient::DOE;

        CHECK(static_cast<int>((ing | ingredient::TOMATO)) == 3);
        REQUIRE(static_cast<int>((ing | ingredient::TOMATO | ingredient::GRUYERE |
                 ingredient::HAM)) == 15);
    }

    SECTION("<< operator")
    {
        std::stringstream sstream;
        ingredient bitst = ingredient::DOE | ingredient::TOMATO |
                           ingredient::GRUYERE | ingredient::HAM;

        sstream << bitst;
        REQUIRE(sstream.str() == "🦌💀🍅🧀🐷💀");
    }
}

TEST_CASE("Pizzas", "Pizza class")
{
    using namespace std::literals::chrono_literals;
    using namespace plazza;
    using namespace plazza::pizzas;

    using plazza::pizzas::ingredient;

    auto ptest = Pizza("test", ingredient::DOE | ingredient::GRUYERE | ingredient::HAM, 1s, size::XL);

    SECTION("Baking time")
    {
        REQUIRE(ptest.getBakingTime() == 1s);
    }

    SECTION("Name")
    {
        REQUIRE(ptest.getName() == "test");
    }

    SECTION("Serializing")
    {
        REQUIRE(ptest.pack() == "test XL : 🦌💀🧀🐷💀");
    }
}

TEST_CASE("Recipe", "Using the recipes")
{
    using namespace plazza;
    using namespace plazza::pizzas;

    SECTION("Using string to access a recipe")
    {
        auto recipe = "americana" >> marmiton;

        REQUIRE(recipe.getName() == "americana");
    }

    SECTION("Using invalid string to access a recipe")
    {
        CHECK_THROWS("Americanus" >> marmiton);
    }

    SECTION("Create a pizza from a recipe")
    {
        auto recipe = "margarita" >> marmiton;
        auto pizza = recipe(size::XL);

        REQUIRE(pizza.pack() == "margarita XL : 🦌💀🍅🧀");
    }
}
