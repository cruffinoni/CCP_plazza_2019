/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "Pizza/Pizza.hpp"

Kitchen::Kitchen::Kitchen(uint16_t cooks, const Plazza::IPC<Reception::Reception *, std::shared_ptr<Kitchen>> &ipc) : _ipc(ipc) {
    this->_timer = std::chrono::system_clock::now();
    this->_sizeList = 2 * cooks;
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
}

void Kitchen::Kitchen::run() {
    uint16_t counter;

    do {
        counter = 0;
        for (auto it :_cooksList)
            if (it->getCookState() == Cook::Cook::State::WORKING)
                counter++;
        if (counter > 0)
            _timer = std::chrono::system_clock::now();
    } while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _timer).count() < 5);
}

std::chrono::time_point<std::chrono::system_clock> Kitchen::Kitchen::getTime() const {
    return _timer;
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
