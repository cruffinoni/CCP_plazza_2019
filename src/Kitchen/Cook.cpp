/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include "Cook.hpp"

//void work(void *_mut, void *_stock) {
//    auto mut = static_cast<std::mutex*>(_mut);
//    auto stock = static_cast<int*>(_stock);
//    mut->lock();
//    bool ret = true;
//    if (stock - 5 > 0) {
//        stock -= 5;
//    } else
//        ret = false;
//    std::cout << "Cook " << (ret ? "worked" : "stock to low") << std::endl;
//    mut->unlock();
//}

Cook::Cook(const IPC::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> &&ipc) : _IPC(ipc) {
    this->_state = PENDING;
    this->_timer = std::chrono::system_clock::now();
}

//bool Cook::checkWork() {
//    auto mut = static_cast<std::mutex*>(_mut);
//    auto stock = static_cast<int*>(_stock);
//    mut->lock();
//    bool ret = true;
//    if (*stock - 5 > 0) {
//        stock -= 5;
//    } else
//        ret = false;
//    std::cout << "Cook " << (ret ? "worked" : "stock to low") << std::endl;
//    mut->unlock();
//    return ret;
//}
