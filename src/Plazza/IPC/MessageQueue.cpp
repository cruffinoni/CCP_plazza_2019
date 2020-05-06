/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** MessageQueue
*/

#include <unistd.h>
#include <chrono>
#include "MessageQueue.hpp"

Plazza::IPC::MessageQueue::Queue::Queue(const size_t id) {
    generateQueue(_list[0], "Reception", id);
    generateQueue(_list[1], "Kitchen", id);
}

Plazza::IPC::MessageQueue::Queue::~Queue() {
    for (auto &i: this->_list)
        std::remove(i.first.c_str());
}

void Plazza::IPC::MessageQueue::Queue::generateQueue(queue_t &queue, const std::string &&prefix, const size_t id) {
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

void Plazza::IPC::MessageQueue::Queue::send(const std::string &msg, const queue_e type) {
    buff_t buffer;

    strcpy(buffer.mtext, msg.c_str());
    int msgid = msgget(this->_list[type].second, IPC_CREAT | 0660);
    if (msgsnd(msgid, &buffer, MAX_TEXT_LENGTH, 0) == -1)
        throw Exceptions::QueueError("msgsnd");
}

std::string Plazza::IPC::MessageQueue::Queue::read(const queue_e type) {
    int msgid = msgget(this->_list[type].second, IPC_CREAT | 0660);
    buff_t buffer;

    if (msgrcv(msgid, &buffer, MAX_TEXT_LENGTH, 0, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            errno = 0;
            throw Exceptions::NoMessageLeft();
        } else
            throw Exceptions::QueueError("msgrcv");
    }
    return (std::string(buffer.mtext));
}
