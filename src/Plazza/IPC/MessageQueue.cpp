/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** MessageQueue
*/

#include <unistd.h>
#include <chrono>
#include "MessageQueue.hpp"

Plazza::IPC::MessageQueue::MessageQueue(const size_t id) {
    generateQueue(_list[0], "Reception", id);
    generateQueue(_list[1], "Kitchen", id);
}

Plazza::IPC::MessageQueue::~MessageQueue() {
    for (auto &i: this->_list)
        std::remove(i.first.c_str());
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

void Plazza::IPC::MessageQueue::send(const std::string &msg, const queue_e dest) {
    buff_t buffer;

    strcpy(buffer.mtext, msg.c_str());
    int msgid = msgget(this->_list[dest].second, IPC_CREAT | 0660);
    if (msgsnd(msgid, &buffer, MAX_TEXT_LENGTH, 0) == -1)
        printf("Err: %s\n", strerror(errno));
}

std::string Plazza::IPC::MessageQueue::read(const queue_e dest) {
    int msgid = msgget(this->_list[dest].second, IPC_CREAT | 0660);
    buff_t buffer;

    if (msgrcv(msgid, &buffer, MAX_TEXT_LENGTH, 0, 0) == -1)
        printf("Err: %s\n", strerror(errno));
    return (std::string(buffer.mtext));
}
