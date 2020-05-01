/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include <random>
#include "Kitchen/Cook.hpp"
#include "Kitchen/Kitchen.hpp"

static void work(Cook::Cook *worker) {
    do {
        // Force concurrency to happen
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //for (size_t i = 0; i < 10e+4; i++)
        //    worker->getIPC().getAscendant()->refreshStock();
        if (worker->getCookState() == Cook::Cook::WORKING)
            worker->cookPizza();
        std::this_thread::yield();
    } while (worker->getCookState() != Cook::Cook::LEAVING);
}

Cook::Cook::Cook(const Kitchen::Kitchen::SharedKitchenIPC_t &ipc) :
    _state(PENDING), _ipc(ipc), _thread(work, this) {
}

Cook::Cook::~Cook() {
    this->_state = LEAVING;
}

Cook::Cook::State Cook::Cook::getCookState() const {
    return (this->_state);
}

void Cook::Cook::setCookState(Cook::Cook::State state) {
    if (this->_state != LEAVING)
        this->_state = state;
}

void Cook::Cook::giveWork(std::shared_ptr<Pizza::pizza_t> &pizza) {
    if (this->_state != PENDING)
        throw Exceptions::WorkerBusy();
    this->_state = WORKING;
    this->_pizza = pizza;
}

std::shared_ptr<Pizza::pizza_t> Cook::Cook::getCurrentPizza() const {
    return (this->_pizza);
}

void Cook::Cook::cookPizza() {
    if (this->getCookState() == Cook::Cook::WORKING) {
        this->_ipc->getAscendant()->withdrawStock(Pizza::PizzaList[this->getCurrentPizza()->type].first);
        std::this_thread::sleep_for(std::chrono::seconds(Pizza::PizzaList[this->getCurrentPizza()->type].second));
        this->_ipc->getAscendant()->changePizzaStatus(this->_pizza, Pizza::Status::BAKED);
        this->setCookState(Cook::Cook::PENDING);
        printf("Pizza %p cooked!\n", this->_pizza.get());
    }
}

const char *Cook::Exceptions::WorkerBusy::what() const noexcept {
    return ("You cannot give work to this cook, he's already working");
}
