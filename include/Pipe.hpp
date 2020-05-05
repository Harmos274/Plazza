/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Pipe class header file
*/

#ifndef PIPE_HPP_
#define PIPE_HPP_

#include <array>
#include <chrono>

#include <unistd.h>

#include <ipc.hpp>
#include <ipc_action.hpp>

namespace plazza
{

class FileDescriptor
{
public:
    FileDescriptor() noexcept;
    FileDescriptor(int fd) noexcept;
    FileDescriptor(FileDescriptor&& to_move) noexcept;
    ~FileDescriptor();

    auto operator=(FileDescriptor&& rhs) noexcept -> FileDescriptor&;

    [[nodiscard]] auto getHandle() const noexcept -> int;

private:
    int fd;
};

class Pipe
{
public:
    Pipe() noexcept;
    Pipe(Pipe&& to_move) noexcept = default;
    ~Pipe() = default;

    auto operator=(Pipe&& rhs) noexcept -> Pipe& = default;

    [[nodiscard]] auto inputHasData() const noexcept -> bool;
    auto waitForInputData(
        std::chrono::duration<int, std::milli> timeout) noexcept -> bool;

    template <typename T_rcv>
    auto receive() -> T_rcv
    {
        static_assert(std::is_scalar_v<T_rcv>);

        T_rcv ret = T_rcv{};
        long read_bytes = read(this->input.getHandle(), &ret, sizeof(T_rcv));

        if (read_bytes != sizeof(T_rcv))
        {
            throw std::exception{};
        }

        return ret;
    }

    template <typename T_snd>
    auto send(T_snd to_send) -> void
    {
        static_assert(std::is_scalar_v<T_snd>);

        bool status =
            write(this->output.getHandle(), &to_send, sizeof(T_snd)) ==
            sizeof(T_snd);

        if (!status)
        {
            throw std::exception{};
        }
    }

    auto send(std::string const& to_send) -> void;
    auto receive(size_t size) -> std::string;

    auto getOtherEnd() noexcept -> Pipe;

private:
    Pipe(FileDescriptor in, FileDescriptor out);

    FileDescriptor input;
    FileDescriptor output;

    FileDescriptor second_input;
    FileDescriptor second_output;
};

};

#endif
