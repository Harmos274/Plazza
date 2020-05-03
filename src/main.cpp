/*
** EPITECH PROJECT, 2020
** CNA_groundhpd_2019
** File description:
** main
*/

#include "Reception.hpp"
#include "exception.hpp"
#include <iostream>

auto main(int ac, char const* av[]) -> int
{
    try
    {
        plazza::Reception(ac, av);

    } catch (plazza::Exception const& e)
    {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
