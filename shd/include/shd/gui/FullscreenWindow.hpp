#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include <imgui.h>

namespace shd::gui
{

template <typename T_widget>
class FullscreenWindow
{
public:
    FullscreenWindow(T_widget&& widget,
                     sf::RenderWindow const& window,
                     std::string&& name,
                     ImGuiWindowFlags flags = ImGuiWindowFlags_None) noexcept
        : widget{std::forward<T_widget>(widget)},
          name{std::forward<std::string>(name)},
          flags{flags | ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse},
          window{window}
    {
    }

    FullscreenWindow(FullscreenWindow const& to_copy) noexcept = default;
    FullscreenWindow(FullscreenWindow&& to_move) noexcept = default;
    ~FullscreenWindow() noexcept = default;

    auto operator=(FullscreenWindow const& rhs) noexcept
        -> FullscreenWindow& = default;
    auto operator=(FullscreenWindow&& rhs) noexcept
        -> FullscreenWindow& = default;

    template <typename... T_args>
    auto update(T_args&&... args) -> bool
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);

        auto size = this->window.getSize();
        ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
        ImGui::SetNextWindowPos({0, 0});

        bool displayed = ImGui::Begin(this->name.data(), nullptr, this->flags);

        if (displayed)
        {
            this->widget.update(std::forward<T_args>(args)...);
        }

        ImGui::End();

        ImGui::PopStyleVar(2);

        return displayed;
    }

private:
    T_widget widget;

    std::string name;
    ImGuiWindowFlags flags;

    sf::RenderWindow const& window;
};

}
