/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** IpcFork class header
*/

#ifndef IPCFORK_HPP_
#define IPCFORK_HPP_

#include <utility>

#include <Fork.hpp>
#include <Pipe.hpp>

namespace plazza
{

class IpcFork
{
public:
    template <typename T_function, typename... T_args>
    IpcFork(Pipe ipc, T_function&& function, T_args&&... arguments)
        : ipc{std::move(ipc)},
          fork{std::forward<T_function>(function),
               this->ipc.getOtherEnd(),
               std::forward<T_args>(arguments)...}
    {
    }

    template <typename T_function, typename... T_args>
    IpcFork(T_function&& function, T_args&&... arguments)
        : ipc{},
          fork{std::forward<T_function>(function),
               this->ipc.getOtherEnd(),
               std::forward<T_args>(arguments)...}
    {
    }

    IpcFork(IpcFork const& to_copy) noexcept = delete;
    IpcFork(IpcFork&& to_move) noexcept = default;
    ~IpcFork() noexcept = default;

    auto operator=(IpcFork const& rhs) noexcept -> IpcFork& = delete;
    auto operator=(IpcFork&& rhs) noexcept -> IpcFork& = default;

    auto getIpc() -> Pipe&
    {
        return this->ipc;
    }

    [[nodiscard]] auto isRunning() noexcept -> bool
    {
        return this->fork.isRunning();
    }

protected:
    Pipe ipc;

private:
    Fork fork;
};

}

#endif
