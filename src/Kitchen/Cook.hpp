/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <thread>
#include <mutex>
#include "Plazza/IPC.hpp"
#include "Pizza/Pizza.hpp"

namespace Kitchen {
    class Kitchen;
}

class Cook {
    private:
        typedef Plazza::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> CookIPC_t;

    public:
        explicit Cook(const Plazza::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> &ipc);
        ~Cook();

        enum CookState {
            PENDING,
            WORKING,
            LEAVING,
        };
        CookState getCookState() const;
        void setCookState(CookState state);
        Pizza::PizzaType getCurrentPizza() const;
        std::shared_ptr<std::thread> &getThread();
        CookIPC_t &getIPC();
        void giveWork(Pizza::PizzaType &&pizza);
        void cookPizza();

    private:
        std::chrono::time_point<std::chrono::system_clock> _timer;
        CookIPC_t _ipc;
        CookState _state;
        std::shared_ptr<std::thread> _thread;
        Pizza::PizzaType _pizza;
};

#endif /* !COOK_HPP_ */
