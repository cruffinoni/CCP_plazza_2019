/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include "Kitchen/Cook.hpp"
#include "Kitchen/Kitchen.hpp"
#include <random>

static void work(Cook *worker) {
    printf("(%p) Inside a thread\n", &worker->getThread());
    do {
        // Force concurrency to happen
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //for (size_t i = 0; i < 10e+4; i++)
        //    worker->getIPC().getAscendant()->refreshStock();
        if (worker->getCookState() == Cook::WORKING)
            worker->cookPizza();
        //printf("(%p - %p) Slept for 1sec\n", &worker->getThread(), worker->getIPC().getAscendant());
        std::this_thread::yield();
    } while (worker->getCookState() != Cook::LEAVING);
}

Cook::Cook(const Plazza::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> &ipc) : _ipc(ipc), _pizza(Pizza::None) {
    this->_state = PENDING;
    this->_timer = std::chrono::system_clock::now();
    this->_thread = std::make_shared<std::thread>(work, this);
}

Cook::~Cook() {
    this->_state = LEAVING;
    if (this->_thread->joinable()) {
        printf("(%p) waiting for the thread to end\n", this);
        this->_thread->join();
    }
}

Cook::CookState Cook::getCookState() const {
    return (this->_state);
}

void Cook::setCookState(Cook::CookState state) {
    if (this->_state != LEAVING)
        this->_state = state;
}

std::shared_ptr<std::thread> &Cook::getThread() {
    return (this->_thread);
}

Cook::CookIPC_t &Cook::getIPC() {
    return (this->_ipc);
}

void Cook::giveWork(Pizza::PizzaType &&pizza) {
    if (this->_state != PENDING) {
        std::cerr << "You cannot give work to this cook, he's already working" << std::endl;
        return;
    }
    this->_pizza = pizza;
    this->_state = WORKING;
}

Pizza::PizzaType Cook::getCurrentPizza() const {
    return (this->_pizza);
}

void Cook::cookPizza() {
    if (this->getCookState() == Cook::WORKING) {
        this->_ipc.getAscendant()->withdrawStock(Pizza::PizzaList[this->getCurrentPizza()].first);
        std::this_thread::sleep_for(std::chrono::seconds(Pizza::PizzaList[this->getCurrentPizza()].second));
        this->setCookState(Cook::PENDING);
    }
}

