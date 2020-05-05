/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** MessageQueue
*/

#ifndef MESSAGEQUEUE_HPP_
#define MESSAGEQUEUE_HPP_

#include <iostream>
#include <fstream>
#include <random>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>

namespace Plazza {
    namespace IPC {
        namespace Exceptions {
            class AlreadyExisting : public std::exception {
                public:
                    AlreadyExisting() = default;
                    const char *what() const noexcept override {
                        const static std::string msg = "Unable to create file, a file with the same name exist "
                                                        "Error: " + std::string(strerror(errno));
                        return msg.c_str();
                    }
            };
            class FileDeletion : public std::exception {
                public:
                    FileDeletion() = default;
                    const char *what() const noexcept override {
                        const static std::string msg = "File deletion failed "
                                                        "Error: " + std::string(strerror(errno));
                        return msg.c_str();
                    }
            };
        }

        class MessageQueue {
            public:
                explicit MessageQueue(size_t id) {
                    generateQueue(_ascendant, "Reception", id);
                    generateQueue(_descendant, "Kitchen", id);
                }
                ~MessageQueue(){
                     std::remove(_ascendant.first.c_str());
                     std::remove(_descendant.first.c_str());
                };

            private:
                typedef std::pair<std::string, key_t> queue_t;
                queue_t _ascendant;
                queue_t _descendant;

                static void generateQueue(queue_t &queue, const std::string &&prefix,
                    size_t id) {
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
        };
    } // namespace IPC
} // namespace Plazza


#endif /* !MESSAGEQUEUE_HPP_ */
