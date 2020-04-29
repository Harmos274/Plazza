#ifndef IMGUIRENDERWINDOW_HPP_
#define IMGUIRENDERWINDOW_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace shd::sfml
{

class ImGuiRenderWindow : public sf::RenderWindow
{

public:
    ImGuiRenderWindow(sf::VideoMode mode,
                      std::string const& title,
                      sf::Uint32 style = sf::Style::Default) noexcept;
    ~ImGuiRenderWindow() noexcept override;

    auto display() -> void;

    auto setupImGui() -> void;

    auto getEvents() -> std::vector<sf::Event>;

    auto initFrame(sf::Color const& color = {0, 0, 0, 255})
        -> std::vector<sf::Event>;

private:
    sf::Clock delta_clock;
};

}

#endif
