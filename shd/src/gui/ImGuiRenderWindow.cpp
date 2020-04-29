#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <gui/ImGuiRenderWindow.hpp>

namespace shd::sfml
{

ImGuiRenderWindow::ImGuiRenderWindow(sf::VideoMode mode,
                                     std::string const& title,
                                     sf::Uint32 style) noexcept
    : sf::RenderWindow{mode, title, style}
{
    this->setVerticalSyncEnabled(true);
    ImGui::SFML::Init(*this);
}

ImGuiRenderWindow::~ImGuiRenderWindow() noexcept
{
    this->close();
    ImGui::SFML::Shutdown();
}

auto ImGuiRenderWindow::display() -> void
{
    ImGui::SFML::Render(*this);
    sf::RenderWindow::display();
}

auto ImGuiRenderWindow::setupImGui() -> void
{
    ImGui::SFML::Update(*this, this->delta_clock.restart());
}

auto ImGuiRenderWindow::getEvents() -> std::vector<sf::Event>
{
    auto events = std::vector<sf::Event>{};
    auto event = sf::Event{};

    while (this->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
        {
            this->close();
        }
        else
        {
            events.push_back(event);
        }
    }

    return events;
}

auto ImGuiRenderWindow::initFrame(sf::Color const& color) -> std::vector<sf::Event>
{
    auto events = this->getEvents();

    this->setupImGui();

    this->clear(color);

    return events;
}

}
