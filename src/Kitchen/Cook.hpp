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
#include "IPC/IPC.hpp"

namespace Kitchen {
    class Kitchen;
}

class Cook {
    public:
        enum State_e {
            PENDING,
            WORKING,
        };
        Cook(const IPC::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> &&ipc);
        ~Cook() = default;

        std::chrono::time_point<std::chrono::system_clock> _timer;
        const IPC::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> _IPC;
        State_e _state;
        std::shared_ptr<std::thread> _thread;
};

#endif /* !COOK_HPP_ */
