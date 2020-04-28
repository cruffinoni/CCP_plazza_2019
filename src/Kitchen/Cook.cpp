/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include "Kitchen/Cook.hpp"
#include "Kitchen/Kitchen.hpp"

void work(Cook *work) {
    printf("(%p) Inside a thread\n", &work->_thread);
    do {
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::seconds(5));
        printf("(%p) Slept for 5sec\n", &work->_thread);
        work->_IPC.getAscendant()->refreshStock();
    } while (work->_state == Cook::PENDING);
}

Cook::Cook(const IPC::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> &&ipc) : _IPC(ipc) {
    this->_state = PENDING;
    printf("Test: %p\n", &this->_thread);
    this->_timer = std::chrono::system_clock::now();
    this->_thread = std::make_shared<std::thread>(work, this);
}

Cook::~Cook() {
    this->_state = LEAVING;
    if (this->_thread->joinable()) {
        this->_thread->join();
    }
}
