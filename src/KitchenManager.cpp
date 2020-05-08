/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** KitchenManager source file
*/

#include <KitchenManager.hpp>

namespace plazza
{

KitchenManager::KitchenManager(size_t cook_nbr,
                               IngredientStock::RegenTime regen,
                               Pipe ipc,
                               double time_multiplier) noexcept
    : kitchen{cook_nbr, regen},
      ipc{std::move(ipc)},
      cooking_time_multiplier{time_multiplier}
{
}

auto KitchenManager::answerOrder(pizzas::bakingTime time) noexcept
{
    ipc.send(kitchen_action::answerOrder);
    ipc.send<pizzas::bakingTime::rep>(time.count());
}

auto KitchenManager::receiveOrder() noexcept
{
    auto size = ipc.receive<size_t>();
    auto input = ipc.receive(size);

    auto iter = shd::WordIterator<' '>{input};
    auto const& recipe = *iter >> marmiton;

    auto pizza_size = Reception::strToPizzasize(*(iter + 1));

    if (this->kitchen.getStock().hasIngredient(recipe.getIngredient()) &&
        this->kitchen.hasRoom())
    {
        this->answerOrder(this->kitchen.getTimeUntilReady());
    }
    else
    {
        this->answerOrder(pizzas::bakingTime::max());
    }

    this->potential_order.emplace(
        recipe, pizza_size, this->cooking_time_multiplier);
}

auto KitchenManager::processEvents() noexcept
{
    auto timeout =
        std::min(std::chrono::duration_cast<std::chrono::milliseconds>(
                     this->kitchen.timeUntilNextPizza()),
                 std::chrono::milliseconds{50});
    if (timeout == std::chrono::milliseconds::zero() &&
        this->kitchen.getOrders().empty())
    {
        timeout = std::chrono::milliseconds{-1};
    }

    bool has_data = ipc.waitForInputData(timeout);

    while (has_data)
    {
        auto action = ipc.receive<reception_action>();

        switch (action)
        {
        case reception_action::putOrder:
            this->receiveOrder();
            break;

        case reception_action::confirmOrder:
            this->kitchen.pushOrder(std::move(this->potential_order).value());
            // fall through

        case reception_action::cancelOrder:
            this->potential_order.reset();
            break;

        case reception_action::close:
            this->running = false;
            break;

        case reception_action::requestState:
            auto state = kitchen.infoString();

            this->ipc.send(kitchen_action::sendState);
            this->ipc.send(state.size());
            this->ipc.send(state);
            break;
        }

        has_data = ipc.inputHasData();
    }
}

auto KitchenManager::isOpen() const noexcept
{
    return this->running;
}

auto KitchenManager::run() -> void
{
    while (this->isOpen())
    {
        this->processEvents();

        auto pizzas = kitchen.collectFinishedOrders();

        for (auto const& pizza : pizzas)
        {
            auto tmp = pizza.pack();

            this->ipc.send(kitchen_action::sendPizza);
            this->ipc.send(tmp.size());
            this->ipc.send(tmp);
        }
    }
}

}
