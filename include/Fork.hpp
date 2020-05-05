/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Fork class header
*/

#ifndef FORK_HPP_
#define FORK_HPP_

#include <functional>
#include <stdexcept>

#include <sys/types.h>
#include <unistd.h>

namespace plazza
{

class Fork
{
public:
    template <typename T_function, typename... T_args>
    Fork(T_function&& function, T_args&&... arguments) : pid{fork()}
    {
        if (this->pid == -1)
        {
            throw std::exception{};
        }
        if (this->pid == 0)
        {
            int status = 0;

            try
            {
                std::invoke(std::forward<T_function>(function),
                            std::forward<T_args>(arguments)...);
            }
            catch (...)
            {
                status = 1;
            }
            std::_Exit(status);
        }
    }

    Fork(Fork const& to_move) = delete;
    Fork(Fork&& to_move) noexcept;
    ~Fork();

    auto operator=(Fork& rhs) -> Fork& = delete;
    auto operator=(Fork&& rhs) noexcept -> Fork&;

    auto wait() noexcept -> int;

    [[nodiscard]] auto isRunning() noexcept -> bool;

private:
    pid_t pid;
    bool is_running{true};
};

}

#endif
