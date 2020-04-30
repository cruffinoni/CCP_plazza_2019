/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "Pizza/Pizza.hpp"
#include "Kitchen/Cook.hpp"

Kitchen::Kitchen::Kitchen(uint16_t cooks, Reception::Reception::SharedReceptionIPC_t &ipc) : _ipc(ipc), _cookPool(cooks, this) {
    this->_sizeList = 2 * cooks;
}

void Kitchen::Kitchen::checkForWork(std::shared_ptr<Cook::Cook> &worker) {
    if (this->_orders.empty())
        return;
    for (auto &pizza : this->_orders) {
        if (pizza->status == Pizza::WAITING) {
            Plazza::ScopedLock lock(this->_mutex, "checkForWork");
            pizza->status = Pizza::COOKING;
            try {
                worker->giveWork(pizza);
            } catch (const Cook::Exceptions::WorkerBusy &e) {
                std::cerr << e.what() << std::endl;
                continue;
            }
            return;
        }
    }
}

void Kitchen::Kitchen::run() {
    uint16_t counter;

    this->_timer = std::chrono::system_clock::now();
    do {
        counter = 0;
        for (auto &ipc : _cookPool) {
            if (ipc->getDescendant()->getCookState() == Cook::Cook::State::WORKING)
                counter++;
            else
                this->checkForWork(ipc->getDescendant());
        }
        if (counter > 0)
            _timer = std::chrono::system_clock::now();
    } while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _timer).count() < 5000);
    printf("Nobody's working since 5 sec. Closing kitchen: %p\n", this->_ipc->getDescendant().get());
    this->_ipc->getAscendant()->closeKitchen(this->_ipc->getDescendant());
}

std::chrono::time_point<std::chrono::system_clock> Kitchen::Kitchen::getTime() const {
    return (_timer);
}

void Kitchen::Kitchen::refreshStock() {
    Plazza::ScopedLock lock(this->_mutex, "refreshStock");
    this->_stock.refresh();
}

void Kitchen::Kitchen::withdrawStock(std::list<Pizza::Ingredients> &list) {
    Plazza::ScopedLock lock(this->_mutex, "withdrawStock");
    this->_stock.withdrawStock(list);
}

void Kitchen::Kitchen::changePizzaStatus(std::shared_ptr<Pizza::pizza_t> &pizza, Pizza::Status status) {
    Plazza::ScopedLock lock(this->_mutex, "changePizzaStatus");
    pizza->status = status;
    if (status == Pizza::Status::BAKED)
        this->_ipc->getAscendant()->checkCompletedOrders();
}

size_t Kitchen::Kitchen::getAvailableSpace() {
    return (this->_sizeList - this->_orders.size());
}

void Kitchen::Kitchen::addCommand(std::shared_ptr<Pizza::pizza_t> &order) {
    this->_orders.emplace_back(order);
}

Kitchen::Kitchen::~Kitchen() {
    this->_orders.clear();
}
