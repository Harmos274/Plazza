/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Exception base class
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <string>
#include <utility>

namespace plazza
{

class Exception : public std::exception
{
public:
    Exception(std::string what) : description{std::move(what)}
    {
    }

    ~Exception() override = default;

    [[nodiscard]] char const* what() const noexcept override
    {
        return this->description.data();
    }

private:
    std::string description;
};

}

#endif
