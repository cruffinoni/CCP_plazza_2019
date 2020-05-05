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
        namespace  Exceptions {
            class AllreadyExisting : public std::exception {
                public:
                    AllreadyExisting() = default;
                    const char *what() const noexcept override {
                        const static std::string msg = "Unable to create file, a file with the same name exist"
                                                        "Error: " + std::string(strerror(errno));
                        return msg.c_str();
                    }
            };
            class FileDeletion : public std::exception {
                public:
                    FileDeletion() = default;
                    const char *what() const noexcept override {
                        const static std::string msg = "File deletion failed"
                                                        "Error: " + std::string(strerror(errno));
                        return msg.c_str();
                    }
            };

        } // namespace  Exceptions

        class MessageQueue {
            public:
                explicit MessageQueue(size_t id) {
                    generateQueue(_ascending, std::string("Reception"), id);
                    generateQueue(_descending, std::string("Kitchen"), id);
                }
                ~MessageQueue(){
                    // std::remove(_ascending.first.c_str());
                    //     // throw Exceptions::FileDeletion();
                    // std::remove(_descending.first.c_str());
                        // throw Exceptions::FileDeletion();
                };

            protected:
            private:
                std::pair<std::string, key_t> _ascending;
                std::pair<std::string, key_t> _descending;

                void generateQueue(std::pair<std::string, key_t> &Queue, const std::string &&prefix, size_t id) {
                    std::default_random_engine rand(time(0));
                    std::uniform_int_distribution<int> range(1,1000);
                    int rd = range(rand);
                    Queue.first = prefix + "_" + std::to_string(id) + "_" + std::to_string(rd);
                    if (access(Queue.first.c_str(), F_OK) != -1)
                        throw Exceptions::AllreadyExisting();
                    std::cout << Queue.first << std::endl;
                    std::ofstream fs(Queue.first);
                    // fs.open(Queue.first);
                    // fs.close();
                    Queue.second = ftok(Queue.first.c_str(), rd);
                }

        };
    } // namespace IPC
} // namespace Plazza



#endif /* !MESSAGEQUEUE_HPP_ */
