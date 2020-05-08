/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Pipe class header file
*/

#include <array>
#include <chrono>
#include <string>

#include <fcntl.h>
#include <poll.h>
#include <sys/stat.h>

#include <Pipe.hpp>
#include <exception.hpp>

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

Pipe::Pipe(FileDescriptor in,
           FileDescriptor out,
           FileDescriptor second_in,
           FileDescriptor second_out)
    : input{std::move(in)},
      output{std::move(out)},
      second_input{std::move(second_in)},
      second_output{std::move(second_out)}
{
}

auto Pipe::receive(size_t size) -> std::string
{
    auto ret = std::string{};

    ret.resize(size);

    long read_bytes = read(this->input.getHandle(), ret.data(), size);

    if (read_bytes != static_cast<long>(size))
    {
        throw plazza::SystemException(std::string{"Pipe : read returned "}
                                          .append(std::to_string(read_bytes))
                                          .append(" when trying to read ")
                                          .append(std::to_string(size))
                                          .append(" bytes"));
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
    long written =
        write(this->output.getHandle(), to_send.data(), to_send.size());

    if (static_cast<size_t>(written) != to_send.size())
    {
        throw plazza::SystemException(
            std::string{"Pipe : write returned "}
                .append(std::to_string(written))
                .append(" when trying to write ")
                .append(std::to_string(to_send.size()))
                .append(" bytes"));
    }
}

Pipe::Pipe()
{
    auto first = std::array<int, 2>{};
    auto second = std::array<int, 2>{};
    int status = 0;

    status |= pipe(first.data());
    status |= pipe(second.data());

    if (status == -1)
    {
        throw PipeException{"Failed to create pipe"};
    }

    this->input = FileDescriptor{first[0]};
    this->output = FileDescriptor{second[1]};

    this->second_input = FileDescriptor{second[0]};
    this->second_output = FileDescriptor{first[1]};
}

auto Pipe::getOtherEnd() noexcept -> Pipe
{
    return Pipe{std::move(this->second_input), std::move(this->second_output)};
}

Pipe::Pipe(FileDescriptor in, FileDescriptor out)
    : input{std::move(in)}, output{std::move(out)}
{
}

auto make_fifo(size_t id) -> Pipe
{
    auto filename_kitchen = std::string{"kitchen_"}.append(std::to_string(id));
    auto filename_reception =
        std::string{"reception_"}.append(std::to_string(id));
    mkfifo(filename_kitchen.c_str(), S_IWUSR | S_IRUSR);
    mkfifo(filename_reception.c_str(), S_IWUSR | S_IRUSR);
    int fd_kitchen_out = open(filename_kitchen.c_str(), O_RDWR);
    int fd_reception_out = open(filename_reception.c_str(), O_RDWR);
    int fd_kitchen_in = open(filename_reception.c_str(), O_RDWR);
    int fd_reception_in = open(filename_kitchen.c_str(), O_RDWR);

    if (fd_kitchen_out == -1 || fd_reception_out == -1 || fd_kitchen_in == -1 ||
        fd_reception_in == -1)
    {
        throw PipeException{"Failed to create named pipe"};
    }
    return Pipe{
        fd_reception_in, fd_reception_out, fd_kitchen_in, fd_kitchen_out};
}

}
