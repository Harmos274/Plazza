/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Pipe class header file
*/

#include <array>
#include <chrono>

#include <unistd.h>
#include <poll.h>

#include <Pipe.hpp>

namespace plazza
{

FileDescriptor::FileDescriptor() noexcept : fd{-1}
{
}

FileDescriptor::FileDescriptor(int fd) noexcept : fd{fd}
{
}

FileDescriptor::FileDescriptor(FileDescriptor&& to_move) noexcept
    : fd{to_move.fd}
{
    to_move.fd = -1;
}

FileDescriptor::~FileDescriptor()
{
    if (this->fd != -1)
    {
        close(this->fd);
    }
}

auto FileDescriptor::operator=(FileDescriptor&& rhs) noexcept -> FileDescriptor&
{
    if (this->fd != -1)
    {
        close(this->fd);
    }

    this->fd = rhs.fd;
    rhs.fd = -1;

    return *this;
}

auto FileDescriptor::getHandle() const noexcept -> int
{
    return this->fd;
}

auto Pipe::receive(size_t size) -> std::string
{
    auto ret = std::string{};

    ret.resize(size);

    long read_bytes = read(this->input.getHandle(), ret.data(), size);

    if (read_bytes == -1)
    {
        throw std::exception{};
    }
    if (read_bytes != static_cast<long>(size))
    {
        throw std::exception{};
    }

    return ret;
}

auto Pipe::inputHasData() const noexcept -> bool
{
    auto fd =
        pollfd{.fd = this->input.getHandle(), .events = POLLIN, .revents = 0};

    return poll(&fd, 1, 0) == 1;
}

auto Pipe::waitForInputData(
    std::chrono::duration<int, std::milli> timeout) noexcept -> bool
{
    auto fd =
        pollfd{.fd = this->input.getHandle(), .events = POLLIN, .revents = 0};

    return poll(&fd, 1, timeout.count()) == 1;
}

void Pipe::send(std::string const& to_send)
{
    bool status =
        write(this->output.getHandle(), to_send.data(), to_send.size()) != -1;

    if (!status)
    {
        throw std::exception{};
    }
}

Pipe::Pipe() noexcept
{
    auto first = std::array<int, 2>{};
    auto second = std::array<int, 2>{};
    int status = 0;

    status |= pipe(first.data());
    status |= pipe(second.data());

    this->input = FileDescriptor{first[0]};
    this->output = FileDescriptor{second[1]};

    this->second_input = FileDescriptor{second[0]};
    this->second_output = FileDescriptor{first[1]};
}

Pipe::Pipe(FileDescriptor in, FileDescriptor out)
    : input{std::move(in)}, output{std::move(out)}
{
}

auto Pipe::getOtherEnd() noexcept -> Pipe
{
    return Pipe{std::move(this->second_input), std::move(this->second_output)};
}

}
