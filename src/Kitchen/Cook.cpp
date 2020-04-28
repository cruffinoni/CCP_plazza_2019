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

void work(Cook *work) {
    printf("Inside a thread: %p\n", &work->_thread);
    do {
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::seconds(4));
        //printf("Slept for 4sec\n");
    } while (work->_state == Cook::PENDING);
}

Cook::Cook(const IPC::IPC<Kitchen::Kitchen *, std::shared_ptr<Cook>> &&ipc) : _IPC(ipc) {
    this->_state = PENDING;
    //printf("Test: %p\n", &this->_thread);
    this->_timer = std::chrono::system_clock::now();
    //this->_thread = std::make_shared<std::thread>(work, this);
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
