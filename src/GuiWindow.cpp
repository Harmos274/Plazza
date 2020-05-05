/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** GuiWindow.cpp
*/

#include <GuiWindow.hpp>
#include <KitchenForkPool.hpp>

namespace plazza
{

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
      sfml_window{sfml_window}
{
}

auto GuiWindow::update(KitchenForkPool& kitchens) noexcept -> void
{
    this->input_window.update(kitchens);

    for (auto& kitchen : kitchens.getForks())
    {
        kitchen.collectFinishedOrders();

        this->display_window.setName(
            std::string{"Kitchen "}.append(std::to_string(kitchen.getId())));

        kitchen.updateState();

        this->display_window.update(kitchen.getState());
    }
}

}
