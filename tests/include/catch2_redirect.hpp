/*
** EPITECH PROJECT, 2020
** catch2_redirection.hpp
** File description:
**
*/

#ifndef CATCH2_REDIRECTION_HPP_
#define CATCH2_REDIRECTION_HPP_

#include <iostream>
#include <sstream>
#include <string>

class streamRedirecter : public std::stringstream
{
public:
  streamRedirecter() = delete;
  streamRedirecter(std::ostream& to_redirect)
    : original_stream{to_redirect}, original_buffer{to_redirect.rdbuf()}
  {
    to_redirect.rdbuf(this->rdbuf());
  }

  ~streamRedirecter()
  {
    this->original_stream.rdbuf(this->original_buffer);
  }

private:
  std::ostream& original_stream;
  std::streambuf* original_buffer;
};

#endif /* !CATCH2_REDIRECTION_HPP_ */
