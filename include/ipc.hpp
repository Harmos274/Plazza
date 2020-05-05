/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Ipc Interface header file
*/

#ifndef IPC_HPP_
#define IPC_HPP_

#include <string>

class Ipc
{
public:
    virtual ~Ipc() = default;

    virtual auto send(std::string const& to_send) -> void = 0;
    virtual auto receive(size_t size) -> std::string = 0;
};

#endif
