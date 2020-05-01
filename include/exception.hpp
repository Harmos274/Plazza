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
class Exception : public std::exception {
  public:
    Exception(std::string what) : description{std::move(what)}
    {}

    ~Exception() override = default;

    [[nodiscard]] auto what() const noexcept -> char const* override
    {
        return this->description.data();
    }

  private:
    std::string description;
};

class SerializingException : public Exception {
  public:
    SerializingException(std::string const& what) :
        Exception("Serializing exception : " + what){};
};

class DeserializingException : public Exception {
  public:
    DeserializingException(std::string const& what) :
        Exception("Deserializing exception : " + what){};
};

class RecipeException : public Exception {
  public:
    RecipeException(std::string const& what) :
        Exception("Recipe exception : " + what){};
};

}

#endif
