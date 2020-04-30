/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "Pizza/Pizza.hpp"
#include "Kitchen/Cook.hpp"



Kitchen::Kitchen::Kitchen(uint16_t cooks, const Plazza::IPC<Reception::Reception *, std::shared_ptr<Kitchen>> &ipc) : _ipc(ipc) {
    this->_sizeList = 2 * cooks;
    this->_timer = std::chrono::system_clock::now();
    for (uint16_t i = 0; i < cooks; ++i) {
        this->_cooksList.emplace_back(this,
            std::make_shared<Cook::Cook>(Plazza::IPC<Kitchen *, std::shared_ptr<Cook::Cook>>(this)));
        std::this_thread::sleep_for(std::chrono::milliseconds(300 * i));
        auto &lastCook = this->_cooksList.back();
        lastCook.setDescendant(lastCook.getDescendant());
        //if (i == 1)
        //    lastCook->giveWork(Pizza::PizzaType::Americana);
    }
    printf("Size of the list: %zu\n", this->_cooksList.size());
    run();
}

void Kitchen::Kitchen::checkForWork(std::shared_ptr<Cook::Cook> &worker) {
    if (this->_orders.empty())
        return;
    for (auto &pizza : this->_orders) {
        if (pizza->status == Pizza::WAITING) {
            Plazza::ScopedLock lock(&_mutex);
            pizza->status = Pizza::COOKING;
            try {
                worker->giveWork(pizza);
            } catch (const Cook::Exceptions::WorkerBusy &e) {
                std::cerr << e.what() << std::endl;
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
        for (auto ipc : _cooksList) {
            if (ipc->getCookState() == Cook::Cook::State::WORKING)
                counter++;
            else
                this->checkForWork(ipc.getDescendant());
        }
        if (counter > 0)
            _timer = std::chrono::system_clock::now();
    } while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _timer).count() < 5000);
    printf("%p\n", _ipc.getDescendant().get());
    _ipc.getAscendant()->closeKitchen();
    printf("Nobody's working since 5 sec\n");
}

std::chrono::time_point<std::chrono::system_clock> Kitchen::Kitchen::getTime() const {
    return (_timer);
}

void Kitchen::Kitchen::refreshStock() {
    Plazza::ScopedLock lock(&_mutex);
    this->_stock.refresh();
}

void Kitchen::Kitchen::withdrawStock(std::list<Pizza::Ingredients> &list) {
    Plazza::ScopedLock lock(&_mutex);
    this->_stock.withdrawStock(list);
}

void Kitchen::Kitchen::changePizzaStatus(std::shared_ptr<Pizza::pizza_t> &pizza, Pizza::Status status) {
    Plazza::ScopedLock lock(&_mutex);
    pizza->status = status;
}

size_t Kitchen::Kitchen::getAvailableSpace() {
    return (this->_sizeList - this->_orders.size());
}

void Kitchen::Kitchen::addCommand(std::shared_ptr<Pizza::pizza_t> &order) {
    this->_orders.emplace_back(order);
}

Kitchen::Stock::Stock() {
    for (int i = Pizza::Ingredients::Ingredient_None; i != Pizza::Invalid; ++i)
        this->_food[static_cast<Pizza::Ingredients>(i)] = DEFAULT_INGREDIENT_QUANTITY;
}

void Kitchen::Stock::refresh() {
    for (auto &i: this->_food)
        i.second++;
}

bool Kitchen::Stock::operator==(std::list<Pizza::Ingredients> &list) {
    for (auto &i : list) {
        if (this->_food.find(i) == this->_food.end())
            return (false);
        if (this->_food[i] == 0)
            return (false);
    }
    return (true);
}

bool Kitchen::Stock::operator!=(std::list<Pizza::Ingredients> &list) {
    return (!(*this == list));
}

void Kitchen::Stock::withdrawStock(std::list<Pizza::Ingredients> &list) {
    if (*this != list)
        // throw exception
        return;
    for (auto &i : list)
        this->_food[i]--;
}

Kitchen::Stock::~Stock() {
    for (auto &i: this->_food)
        printf("Food: %i = %lu\n", i.first, i.second);
}
