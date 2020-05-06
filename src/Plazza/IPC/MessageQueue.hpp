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
            class NoMessageLeft : public std::exception {
                public:
                    NoMessageLeft() = default;
                    const char *what() const noexcept override {
                        const static std::string msg = "There is no message left in this queue";
                        return msg.c_str();
                    }
            };
            class QueueError : public std::exception {
                public:
                    QueueError() = delete;
                    explicit QueueError(const std::string &syscallName) {
                        this->_sysName = syscallName;
                    };
                    const char *what() const noexcept override {
                        const static std::string msg = "An error occured in the system call " + this->_sysName +
                                                        " | Error: " + std::string(strerror(errno));
                        return msg.c_str();
                    }

                private:
                    std::string _sysName;
            };
        }

        namespace MessageQueue {
            class Queue {
                public:
                    explicit Queue(const size_t id);
                    ~Queue();

                    static const int MAX_TEXT_LENGTH = 0xFF;
                    typedef struct buff_s {
                        long mtype = 1;
                        char mtext[MAX_TEXT_LENGTH]{0};
                    } buff_t;

                    enum queue_e {
                        ASCENDANT,
                        DESCENDANT
                    };

                    void send(const std::string &msg, const queue_e type);
                    std::string read(const queue_e type);

                private:
                    typedef std::pair<std::string, key_t> queue_t;
                    std::array<queue_t, 2> _list;

                    static void generateQueue(queue_t &queue, const std::string &&prefix, const size_t id);
            };

            class Parser {
                public:
                    Parser() = default;
            };
        }
    } // namespace IPC
} // namespace Plazza


#endif /* !MESSAGEQUEUE_HPP_ */
