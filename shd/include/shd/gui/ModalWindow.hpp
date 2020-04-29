#include <string>

#include <imgui.h>

namespace shd::gui
{

template <typename T_widget>
class ModalWindow
{
public:
    ModalWindow(T_widget&& widget,
                std::string&& name,
                ImGuiWindowFlags flags = ImGuiWindowFlags_None) noexcept
        : widget{std::forward<T_widget>(widget)},
          name{std::forward<std::string>(name)},
          flags{flags}
    {
    }

    ModalWindow(ModalWindow const& to_copy) noexcept = default;
    ModalWindow(ModalWindow&& to_move) noexcept = default;
    ~ModalWindow() noexcept = default;

    auto operator=(ModalWindow const& rhs) noexcept -> ModalWindow& = default;
    auto operator=(ModalWindow&& rhs) noexcept -> ModalWindow& = default;

    template <typename... T_args>
    auto update(T_args&&... args) -> bool
    {
        bool displayed =
            ImGui::BeginPopupModal(this->name.data(), nullptr, this->flags);

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
