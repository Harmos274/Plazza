#ifndef SHD_GUI_WINDOW
#define SHD_GUI_WINDOW

#include <string>

#include <imgui.h>

namespace shd::gui
{

template <typename T_widget>
class Window
{
public:
    Window(T_widget&& widget,
           std::string&& name,
           ImGuiWindowFlags flags = ImGuiWindowFlags_None) noexcept
        : widget{std::forward<T_widget>(widget)},
          name{std::forward<std::string>(name)},
          flags{flags}
    {
    }

    Window(Window const& to_copy) noexcept = default;
    Window(Window&& to_move) noexcept = default;
    ~Window() noexcept = default;

    auto operator=(Window const& rhs) noexcept -> Window& = default;
    auto operator=(Window&& rhs) noexcept -> Window& = default;

    template <typename... T_args>
    auto update(T_args&&... args) -> bool
    {
        bool displayed = ImGui::Begin(this->name.data(), nullptr, this->flags);

        if (displayed)
        {
            this->widget.update(std::forward<T_args>(args)...);
        }

        ImGui::End();

        return displayed;
    }

    auto setName(std::string const& new_name)
    {
        this->name = new_name;
    }

private:
    T_widget widget;

    std::string name;
    ImGuiWindowFlags flags;
};

}

#endif
