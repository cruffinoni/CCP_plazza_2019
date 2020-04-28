/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include <algorithm>
#include "Kitchen.hpp"

void *starter(void *a, void *b)
{
    auto test = static_cast<std::mutex*>(b);
    test->lock();
    auto *_a = static_cast<unsigned long long *>(a);
    printf("Start: %llu\n", *_a);
    for (unsigned long long k = (*_a) + 100000; (*_a) < k;)
        *_a = *_a + 1;
    test->unlock();
    return (nullptr);
}

Kitchen::Kitchen::Kitchen(uint16_t cooks, const IPC::IPC<Reception::Reception *, std::shared_ptr<Kitchen>> &ipc) : _ipc(ipc) {
    this->_timer = std::chrono::system_clock::now();
    for (uint16_t i = 0; i < cooks; ++i) {
        this->_cooksList.emplace_back(this,
            std::make_shared<Cook>(IPC::IPC<Kitchen *, std::shared_ptr<Cook>>(this)));

        auto &lastCook = this->_cooksList.back();
        lastCook.setDescendant(lastCook.getDescendant());
    }
    printf("Size of the list: %llu\n", this->_cooksList.size());
}

std::chrono::time_point<std::chrono::system_clock> Kitchen::Kitchen::getTime() const {return _timer;}

Kitchen::Kitchen::~Kitchen() {
    //for (auto &i: this->_cooksList)
    //    i.getDescendant()->
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
        printf("Food: %i = %i\n", i.first, i.second);
}
