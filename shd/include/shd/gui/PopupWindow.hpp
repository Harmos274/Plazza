#include <string>

#include <imgui.h>

namespace shd::gui
{

template <typename T_widget>
class PopupWindow
{
public:
    PopupWindow(T_widget&& widget,
                std::string&& name,
                ImGuiWindowFlags flags = ImGuiWindowFlags_None) noexcept
        : widget{std::forward<T_widget>(widget)},
          name{std::forward<std::string>(name)},
          flags{flags}
    {
    }

    PopupWindow(PopupWindow const& to_copy) noexcept = default;
    PopupWindow(PopupWindow&& to_move) noexcept = default;
    ~PopupWindow() noexcept = default;

    auto operator=(PopupWindow const& rhs) noexcept -> PopupWindow& = default;
    auto operator=(PopupWindow&& rhs) noexcept -> PopupWindow& = default;

    template <typename... T_args>
    auto update(T_args&&... args) -> bool
    {
        bool displayed = ImGui::BeginPopup(this->name.data(), this->flags);

        if (displayed)
        {
            this->widget.update(std::forward<T_args>(args)...);

            ImGui::EndPopup();
        }

        return displayed;
    }

    auto open() -> void
    {
        ImGui::OpenPopup(this->name.c_str());
    }

private:
    T_widget widget;

    std::string name;
    ImGuiWindowFlags flags;
};

}
