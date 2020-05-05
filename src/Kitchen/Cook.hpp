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
#include "Plazza/Thread.hpp"
#include "Plazza/IPC/Memory.hpp"
#include "Pizza/Pizza.hpp"
#include "Kitchen/Kitchen.hpp"

namespace Cook {
    class Cook {
        public:
            explicit Cook(const Kitchen::Kitchen::SharedPtrKitchenIPC_t &ipc);
            ~Cook();

            enum State {
                PENDING,
                WORKING,
                LEAVING,
            };

            State getCookState() const;
            void setCookState(State state);
            std::shared_ptr<Pizza::pizza_t> getCurrentPizza() const;
            void giveWork(std::shared_ptr<Pizza::pizza_t> &pizza);
            void cookPizza();

        private:
            State _state;
            Kitchen::Kitchen::SharedPtrKitchenIPC_t _ipc;
            Plazza::Thread _thread;
            std::shared_ptr<Pizza::pizza_t> _pizza;
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
