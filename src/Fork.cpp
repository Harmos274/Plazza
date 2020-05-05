/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Fork class implementation
*/

#include <functional>

#include <sys/wait.h>
#include <unistd.h>

#include <Fork.hpp>

namespace plazza
{

Fork::Fork(Fork&& to_move) noexcept : pid{to_move.pid}
{
    to_move.pid = -1;
}

Fork::~Fork()
{
    if (this->pid != 0 && this->isRunning())
    {
        this->wait();
    }
}

auto Fork::operator=(Fork&& rhs) noexcept -> Fork&
{
    if (this->pid != 0 && this->isRunning())
    {
        this->wait();
    }

    this->pid = rhs.pid;
    rhs.pid = -1;

    return *this;
}

auto Fork::wait() noexcept -> int
{
    siginfo_t info;
    int status = waitid(P_PID, this->pid, &info, WEXITED);

    return status;
}

auto Fork::isRunning() noexcept -> bool
{
    if (this->pid != -1 && this->is_running)
    {
        siginfo_t info;
        info.si_pid = -1;
        waitid(P_PID, this->pid, &info, WEXITED | WNOHANG);

        this->is_running = (info.si_pid == 0);
    }
    return this->pid != -1 && this->is_running;
}

}
