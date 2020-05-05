/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** MessageQueue
*/

#include "MessageQueue.hpp"



Plazza::IPC::MessageQueue::MessageQueue(const size_t id) {
    generateQueue(_ascendant, "Reception", id);
    generateQueue(_descendant, "Kitchen", id);
}

Plazza::IPC::MessageQueue::~MessageQueue() {
    std::remove(_ascendant.first.c_str());
    std::remove(_descendant.first.c_str());
}

void Plazza::IPC::MessageQueue::generateQueue(queue_t &queue, const std::string &&prefix, const size_t id) {
    std::mt19937 rand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> range(1,1000);
    int rd = range(rand);

    queue.first = "./communication/" + prefix + "_" + std::to_string(id) + "_" + std::to_string(rd);
    if (access(queue.first.c_str(), F_OK) != -1)
        throw Exceptions::AlreadyExisting();
    std::cout << queue.first << std::endl;
    std::ofstream fs(queue.first);
    queue.second = ftok(queue.first.c_str(), rd);
}