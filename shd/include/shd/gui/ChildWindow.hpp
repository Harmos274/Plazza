#include <string>

#include <imgui.h>

namespace shd::gui
{

template <typename T_widget>
class ChildWindow
{
public:
    ChildWindow(T_widget&& widget,
                std::string&& name,
                ImGuiWindowFlags flags = ImGuiWindowFlags_None) noexcept
        : widget{std::forward<T_widget>(widget)},
          name{std::forward<std::string>(name)},
          flags{flags}
    {
    }

    ChildWindow(ChildWindow const& to_copy) noexcept = default;
    ChildWindow(ChildWindow&& to_move) noexcept = default;
    ~ChildWindow() noexcept = default;

    auto operator=(ChildWindow const& rhs) noexcept -> ChildWindow& = default;
    auto operator=(ChildWindow&& rhs) noexcept -> ChildWindow& = default;

    template <typename... T_args>
    auto update(T_args&&... args) -> bool
    {
        bool displayed =
            ImGui::BeginChild(this->name.c_str(), {-1, -1}, false, this->flags);

        if (displayed)
        {
            this->widget.update(std::forward<T_args>(args)...);
        }

        ImGui::EndChild();

        return displayed;
    }

    [[nodiscard]] auto getName() const noexcept -> std::string const&
    {
        return this->name;
    }

    auto setName(std::string const& new_name) -> void
    {
        this->name = new_name;
    }

private:
    T_widget widget;

    std::string name;
    ImGuiWindowFlags flags;
};

}
