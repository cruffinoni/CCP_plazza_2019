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
#include <sys/msg.h>
#include <array>

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
                explicit MessageQueue(const size_t id);
                ~MessageQueue();

                typedef struct buff_s {
                    long type;
                    char text[100];
                } buff_t;
                enum Destination {
                    RECEPTION,
                    KITCHEN
                };

                void sendMsg(std::string &msg, Destination dest);
                std::string &receivMsg();

            private:
                typedef std::pair<std::string, key_t> queue_t;
                std::array<queue_t, 2> _list;

                static void generateQueue(queue_t &queue, const std::string &&prefix, const size_t id);
        };
    } // namespace IPC
} // namespace Plazza


#endif /* !MESSAGEQUEUE_HPP_ */
