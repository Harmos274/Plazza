/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** GuiWindow.cpp
*/

#include <cmath>
#include <iostream>

#include "imgui.h"

#include <GuiWindow.hpp>
#include <KitchenForkPool.hpp>

namespace plazza
{

namespace
{

constexpr float gui_window_padding_x = 10.f;
constexpr float gui_window_padding_y = 10.f;
constexpr float gui_window_size_min_x = 200.f;
constexpr float gui_window_size_min_y = 50.f;

auto get_gui_window_size(ImVec2 window_size, size_t gui_windows_nbr) -> ImVec2
{
    auto gui_window_nbr_x = std::min(
        std::max(
            static_cast<size_t>((window_size.x - gui_window_padding_x) /
                                (gui_window_size_min_x + gui_window_padding_x)),
            1ul),
        gui_windows_nbr);
    auto gui_window_nbr_y = std::max(
        static_cast<size_t>(std::ceil(static_cast<float>(gui_windows_nbr) /
                                      static_cast<float>(gui_window_nbr_x))),
        1ul);
    auto ret = ImVec2{};

    ret.x =
        std::max(((window_size.x - gui_window_padding_x) / gui_window_nbr_x) -
                     gui_window_padding_x,
                 gui_window_size_min_x);
    ret.y =
        std::max(((window_size.y - gui_window_padding_y) / gui_window_nbr_y) -
                     gui_window_padding_y,
                 gui_window_size_min_y);

    return ret;
}

}

auto GuiWindow::InputWidget::update(KitchenForkPool& kitchens) -> void
{
    bool confirm = false;

    confirm |= ImGui::InputText("##UserInput",
                                buffer.data(),
                                1024,
                                ImGuiInputTextFlags_EnterReturnsTrue);
    ImGui::SameLine();
    confirm |= ImGui::Button("Order");

    if (confirm)
    {
        auto end_pos = this->buffer.find('\0');

        if (end_pos != std::string::npos)
        {
            this->buffer.resize(end_pos);
        }

        auto orders = Reception::parseOrder(this->buffer);

        for (auto const& order : orders)
        {
            kitchens.pushOrder(order);
        }

        this->buffer.resize(1024, '\0');
    }
}

auto GuiWindow::DisplayWidget::update(std::string const& state)
{
    ImGui::Text("%s", state.c_str());
}

GuiWindow::GuiWindow(sf::RenderWindow const& sfml_window) noexcept
    : input_window{InputWidget{},
                   sfml_window,
                   "Input",
                   ImGuiWindowFlags_NoBringToFrontOnFocus},
      display_window{
          DisplayWidget{}, "State", ImGuiWindowFlags_NoFocusOnAppearing},
      sfml_window{sfml_window},
      logger{"log"}
{
}

auto GuiWindow::update(KitchenForkPool& kitchens, sf::Vector2u window_size)
    -> void
{
    this->input_window.update(kitchens);

    auto start_y = ImGui::GetCursorPosY();

    auto gui_window_size =
        get_gui_window_size(ImVec2(window_size.x, window_size.y - start_y),
                            kitchens.getForks().size());
    float pos_x = gui_window_padding_x;
    float pos_y = start_y + gui_window_padding_y;

    for (auto& kitchen : kitchens.getForks())
    {
        for (auto const& pizza : kitchen.collectFinishedOrders())
        {
            std::cout << "Got a " << pizza.getName() << ' ' << pizza.getSize()
                      << " from kitchen " << kitchen.getId() << '\n';
            this->logger << "Got a " << pizza.getName() << ' '
                         << pizza.getSize() << " from kitchen "
                         << kitchen.getId() << '\n';
        }

        this->display_window.setName(
            std::string{"Kitchen "}.append(std::to_string(kitchen.getId())));

        kitchen.updateState();

        ImGui::SetNextWindowSize(gui_window_size);
        ImGui::SetNextWindowPos({pos_x, pos_y});
        this->display_window.update(kitchen.getState());

        pos_x += gui_window_size.x + gui_window_padding_x;

        if (pos_x >= window_size.x - gui_window_padding_x)
        {
            pos_x = gui_window_padding_x;
            pos_y += gui_window_size.y + gui_window_padding_y;
        }

        kitchen.requestState();
    }
}

}
