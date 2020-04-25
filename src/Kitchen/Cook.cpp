/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include "Cook.hpp"

void work(void *_mut, void *_stock) {
    auto mut = static_cast<std::mutex*>(_mut);
    auto stock = static_cast<int*>(_stock);
    mut->lock();
    bool ret = true;
    if (*stock - 5 > 0) {
        stock -= 5;
    } else
        ret = false;
    std::cout << "Cook " << (ret ? "worked" : "stock to low") << std::endl;
    mut->unlock();
}

Cook::Cook(void *mut, void *stock)
{
    _mut = mut;
    _stock = stock;

    while (0) {
        std::thread th(work, _mut, _stock);
    }
}

Cook::~Cook(){}


bool Cook::checkWork() {
    auto mut = static_cast<std::mutex*>(_mut);
    auto stock = static_cast<int*>(_stock);
    mut->lock();
    bool ret = true;
    if (*stock - 5 > 0) {
        stock -= 5;
    } else
        ret = false;
    std::cout << "Cook " << (ret ? "worked" : "stock to low") << std::endl;
    mut->unlock();
    return ret;
}