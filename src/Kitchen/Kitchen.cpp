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

Kitchen::Kitchen::Kitchen(uint16_t cooks, const IPC::IPC<Cook, std::shared_ptr<Kitchen>> &IPC) :  _IPC(IPC) {
    this->_timer = std::chrono::system_clock::now();
    for (uint16_t i = 0; i < cooks; ++i)
        this->_cooksList.emplace_back(this, std::make_shared<Cook>());
    printf("Size of the list: %llu\n", this->_cooksList.size());
    // unsigned long long a = 0;
    // for (int i = 0; i < 50; ++i)
    //     _cooksList.emplace_back(std::thread(starter, &a, &_mut));
    // for (auto &it : _cooksList)
    //     it.join();

    // std::cout << a << std::endl;
    //int stock = 40;
    //for (int i = 0; i < nb; ++i)
    //    _cooksList.emplace_back(new Cook(&_mut, &stock));
    //for (auto &it :_cooksList) {
        //it->checkWork();
    //}
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
