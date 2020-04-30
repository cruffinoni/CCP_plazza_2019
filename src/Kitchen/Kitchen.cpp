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
    printf("(%p) Cooks: %i & Ipc: %p\n", this, cooks, ipc.get());
    this->_sizeList = 2 * cooks;
    //for (uint16_t i = 0; i < cooks; ++i) {
        //printf("current: %p & parent: %p\n", this, this->_ipc->getAscendant());
        //this->_cookPool.emplace_back(this,
        //                             std::make_shared<Cook::Cook>(Plazza::IPC<Kitchen *, std::shared_ptr<Cook::Cook>>(this)));
        //std::this_thread::sleep_for(std::chrono::milliseconds(300 * i));
        //auto &lastCook = this->_cookPool.back();
        //lastCook.setDescendant(lastCook.getDescendant());
    //}
}

void Kitchen::Kitchen::checkForWork(std::shared_ptr<Cook::Cook> &worker) {
    if (this->_orders.empty())
        return;
    for (auto &pizza : this->_orders) {
        if (pizza->status == Pizza::WAITING) {
            this->_mutex.try_lock();
            pizza->status = Pizza::COOKING;
            try {
                worker->giveWork(pizza);
            } catch (const Cook::Exceptions::WorkerBusy &e) {
                std::cerr << e.what() << std::endl;
                this->_mutex.unlock();
                continue;
            }
            this->_mutex.unlock();
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
    if (!this->_mutex.try_lock())
        return;
    this->_stock.refresh();
    this->_mutex.unlock();
}

void Kitchen::Kitchen::withdrawStock(std::list<Pizza::Ingredients> &list) {
    if (!this->_mutex.try_lock())
        return;
    this->_stock.withdrawStock(list);
    this->_mutex.unlock();
}

void Kitchen::Kitchen::changePizzaStatus(std::shared_ptr<Pizza::pizza_t> &pizza, Pizza::Status status) {
    if (!this->_mutex.try_lock())
        return;
    pizza->status = status;
    if (status == Pizza::Status::BAKED)
        this->_ipc->getAscendant()->checkCompletedOrders();
    this->_mutex.unlock();
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
