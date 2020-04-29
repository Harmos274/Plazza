#ifndef WORDITERATOR_HPP_
#define WORDITERATOR_HPP_

#include <cassert>
#include <exception>
#include <string_view>

namespace shd
{

template <char... separators>
class WordIterator
{
public:
    WordIterator() = delete;

    constexpr WordIterator(std::string_view str, size_t pos = 0) noexcept
        : view{str}, current_begin{}, current_end{pos}
    {
        this->getNextBegin();
        this->getNextEnd();
    }

    constexpr WordIterator(WordIterator const& to_copy) noexcept = default;
    ~WordIterator() = default;

    constexpr auto operator=(WordIterator const& rhs) noexcept -> WordIterator& =
        default;

    constexpr auto operator==(WordIterator const& other) const noexcept -> bool
    {
        return this->view == other.view &&
               this->current_begin == other.current_begin;
    }

    constexpr auto operator!=(WordIterator const& other) const noexcept -> bool
    {
        return !this->operator==(other);
    }

    constexpr auto operator++() noexcept -> WordIterator
    {
        this->getNextBegin();
        this->getNextEnd();

        return *this;
    }

    constexpr auto operator++(int) noexcept -> WordIterator
    {
        auto copy = WordIterator{*this};

        this->getNextBegin();
        this->getNextEnd();

        return copy;
    }

    constexpr auto operator+(size_t inc) const noexcept -> WordIterator
    {
        auto ret = WordIterator{*this};

        ret += inc;

        return ret;
    }

    constexpr auto operator+=(size_t inc) noexcept -> WordIterator&
    {
        for (size_t pos = 0; pos < inc; ++pos)
        {
            this->getNextBegin();
            this->getNextEnd();
        }

        return *this;
    }

    constexpr auto operator*() const -> std::string_view
    {
        assert(!this->isEnd());

        return std::string_view{this->view.data() + this->current_begin,
                                this->current_end - this->current_begin};
    }

    [[nodiscard]] constexpr auto begin() const noexcept -> WordIterator
    {
        return *this;
    }

    [[nodiscard]] constexpr auto end() const noexcept -> WordIterator
    {
        auto ret = WordIterator{*this};

        ret.current_begin = ret.view.size();
        ret.current_end = ret.view.size();

        return ret;
    }

private:
    constexpr void getNextBegin() noexcept
    {
        size_t pos = this->current_end;

        while (pos < this->view.size() &&
               ((this->view[pos] == separators) || ...))
        {
            ++pos;
        }

        if (pos >= this->view.size())
        {
            this->current_begin = this->view.size();
        }
        else
        {
            this->current_begin = pos;
        }
    }

    constexpr void getNextEnd() noexcept
    {
        size_t pos = this->current_begin;

        while (pos < this->view.size() &&
               !((this->view[pos] == separators) || ...))
        {
            ++pos;
        }

        this->current_end = pos;
    }

    [[nodiscard]] constexpr auto isEnd() const noexcept -> bool
    {
        return this->current_begin == this->view.size();
    }

    std::string_view view;
    size_t current_begin;
    size_t current_end;
};

}
#endif
