/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Kitchen/Kitchen.hpp"

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
