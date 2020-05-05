/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** ipc_action
*/

#ifndef IPC_ACTION_HPP_
#define IPC_ACTION_HPP_

namespace plazza
{

enum class kitchen_action : unsigned char
{
    answerOrder,
    sendPizza,
    sendState
};

enum class reception_action : unsigned char
{
    putOrder,
    confirmOrder,
    cancelOrder,
    close
};

}
#endif
