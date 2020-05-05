/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** GuiWindow header
*/

#include <shd/gui/FullscreenWindow.hpp>
#include <shd/gui/Window.hpp>

#include <KitchenForkPool.hpp>

#ifndef GUIWINDOW_HPP_
#define GUIWINDOW_HPP_

namespace plazza
{
class GuiWindow
{
public:
    class InputWidget
    {
    public:
        InputWidget() noexcept : buffer(1024, '\0')
        {
        }

        InputWidget(InputWidget const& to_copy) noexcept = default;
        InputWidget(InputWidget&& to_move) noexcept = default;
        ~InputWidget() noexcept = default;

        auto operator=(InputWidget const& rhs) noexcept
            -> InputWidget& = default;
        auto operator=(InputWidget&& rhs) noexcept -> InputWidget& = default;

        auto update(KitchenForkPool& kitchens) -> void;

    private:
        std::string buffer;
    };

    class DisplayWidget
    {
    public:
        DisplayWidget() noexcept = default;
        DisplayWidget(DisplayWidget const& to_copy) noexcept = default;
        DisplayWidget(DisplayWidget&& to_move) noexcept = default;
        ~DisplayWidget() noexcept = default;

        auto operator=(DisplayWidget const& rhs) noexcept
            -> DisplayWidget& = default;
        auto operator=(DisplayWidget&& rhs) noexcept
            -> DisplayWidget& = default;

        static auto update(std::string const& state);
    };

    GuiWindow(sf::RenderWindow const& sfml_window) noexcept;
    GuiWindow(GuiWindow const& to_copy) noexcept = default;
    GuiWindow(GuiWindow&& to_move) noexcept = default;
    ~GuiWindow() noexcept = default;

    auto operator=(GuiWindow const& rhs) noexcept -> GuiWindow& = default;
    auto operator=(GuiWindow&& rhs) noexcept -> GuiWindow& = default;

    auto update(KitchenForkPool& kitchens) noexcept -> void;

private:
    shd::gui::FullscreenWindow<InputWidget> input_window;
    shd::gui::Window<DisplayWidget> display_window;
    std::reference_wrapper<sf::RenderWindow const> sfml_window;
};

}

#endif
