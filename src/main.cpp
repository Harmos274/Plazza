/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** main
*/

#include <iostream>

#include <shd/gui/ImGuiRenderWindow.hpp>

#include <GuiWindow.hpp>
#include <KitchenForkPool.hpp>

constexpr int exit_success = 0;
constexpr int exit_failure = 84;

using namespace plazza;

auto main(int ac, char** av) -> int
{
    try
    {
        auto reception = Reception{ac, av};

        shd::sfml::ImGuiRenderWindow window{sf::VideoMode{640, 480}, "Plazza"};
        auto gui_window = plazza::GuiWindow{window};

        auto kitchens = KitchenForkPool{reception.getCookNbr(),
                                        reception.getMultiplier(),
                                        reception.getRestockTime()};

        while (window.isOpen())
        {
            window.initFrame();

            kitchens.cull();

            gui_window.update(kitchens);

            window.display();
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << '\n';

        return exit_failure;
    }
    return exit_success;
}
