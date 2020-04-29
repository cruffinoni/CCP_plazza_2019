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

namespace Cook {
    class Cook {
        private:
            typedef Plazza::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> CookIPC_t;

        public:
            explicit Cook(const Plazza::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> &ipc);
            ~Cook();

            enum State {
                PENDING,
                WORKING,
                LEAVING,
            };

            State getCookState() const;
            void setCookState(State state);
            Pizza::PizzaType getCurrentPizza() const;
            std::shared_ptr<std::thread> &getThread();
            CookIPC_t &getIPC();
            void giveWork(Pizza::PizzaType &&pizza);
            void cookPizza();

        private:
            CookIPC_t _ipc;
            State _state;
            std::shared_ptr<std::thread> _thread;
            Pizza::PizzaType _pizza;
    };

    namespace Exceptions {
        class WorkerBusy : std::exception {
            public:
                WorkerBusy() noexcept = default;
                const char *what() const noexcept override;
        };
    }
}

#endif /* !COOK_HPP_ */
