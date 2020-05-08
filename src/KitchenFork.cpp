/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** KichenFork source file
*/

#include <iostream>

#include <KitchenFork.hpp>
#include <Pipe.hpp>

namespace plazza
{

namespace
{

auto kitchen_process(Pipe ipc,
                     size_t cook_nbr,
                     double time_multiplier,
                     IngredientStock::RegenTime regen) -> void
{
    try
    {
        KitchenManager manager{
            cook_nbr, regen, std::move(ipc), time_multiplier};

        manager.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << '\n';
    }
}

}

KitchenFork::KitchenFork(size_t cook_nbr,
                         double time_multiplier,
                         IngredientStock::RegenTime regen,
                         size_t id)
    : IpcFork{kitchen_process, cook_nbr, time_multiplier, regen},
      last_pizza{ClockType::now()},
      id{id}
{
}

auto KitchenFork::operator=(KitchenFork&& rhs) noexcept -> KitchenFork&
{
    this->sendClose();

    IpcFork::operator=(std::move(rhs));
    this->latest_state = std::move(rhs.latest_state);
    this->to_deliver = std::move(rhs.to_deliver);
    this->last_pizza = std::move(rhs.last_pizza);
    this->current_orders = rhs.current_orders;
    this->id = rhs.id;

    return *this;
}

auto KitchenFork::sendClose() noexcept -> void
{
    if (this->isRunning())
    {
        this->ipc.send(reception_action::close);
    }
}

auto KitchenFork::getState() noexcept -> std::string&
{
    return this->latest_state;
}

auto KitchenFork::putOrder(Reception::Order const& order) -> void
{
    auto msg = std::string{order.recipe.get().getName()}.append(1, ' ').append(
        Reception::pizzaSizeToStr(order.size));

    this->ipc.send(reception_action::putOrder);
    this->ipc.send(msg.size());
    this->ipc.send(msg);
}

auto KitchenFork::getOrderResponse() -> pizzas::bakingTime
{
    auto action = std::optional<kitchen_action>{std::nullopt};

    while (!action.has_value() || action.value() != kitchen_action::answerOrder)
    {
        this->ipc.waitForInputData(std::chrono::duration<int, std::milli>{-1});
        action = this->updateState();
    }

    return pizzas::bakingTime{this->ipc.receive<pizzas::bakingTime::rep>()};
}

auto KitchenFork::cancelOrder() -> void
{
    this->ipc.send(reception_action::cancelOrder);
}

auto KitchenFork::confirmOrder() -> void
{
    ++this->current_orders;

    this->ipc.send(reception_action::confirmOrder);
}

auto KitchenFork::requestState() -> void
{
    this->ipc.send(reception_action::requestState);
}

auto KitchenFork::updateState() -> std::optional<kitchen_action>
{
    bool has_data = this->ipc.inputHasData();
    auto ret = std::optional<kitchen_action>{std::nullopt};

    while (has_data)
    {
        auto action = this->ipc.receive<kitchen_action>();

        if (action == kitchen_action::sendPizza)
        {
            auto size = this->ipc.receive<size_t>();
            auto pizza_str = this->ipc.receive(size);

            this->to_deliver.push_back(Reception::deserializePizza(pizza_str));

            has_data = this->ipc.inputHasData();
        }
        else if (action == kitchen_action::sendState)
        {
            auto size = this->ipc.receive<size_t>();
            auto state = this->ipc.receive(size);

            this->latest_state = std::move(state);
            has_data = this->ipc.inputHasData();
        }
        else
        {
            has_data = false;
        }
        ret.emplace(action);
    }
    return ret;
}

auto KitchenFork::collectFinishedOrders() noexcept -> std::vector<pizzas::Pizza>
{
    auto ret = std::move(this->to_deliver);

    this->to_deliver.clear();

    if (!ret.empty())
    {
        this->current_orders -= ret.size();
        this->last_pizza = ClockType::now();
    }

    return ret;
}

auto KitchenFork::getId() const noexcept -> size_t
{
    return this->id;
}

auto KitchenFork::shouldClose() const noexcept -> bool
{
    auto now = ClockType::now();

    return (now - this->last_pizza) > std::chrono::seconds{5} &&
           this->current_orders == 0;
}

}
