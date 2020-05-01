/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_PLAZZA_CHILD_PROCESS_
#define SRC_PLAZZA_CHILD_PROCESS_

#include <sys/types.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <csignal>
#include <list>
#include <string>

namespace Plazza {
    namespace ChildProcess {
        class ForkFailed : public std::exception {
            public:
                ForkFailed() = default;
                const char *what() const noexcept override {
                    static std::string msg = "Fork failed: " + std::string(strerror(errno));
                    return (msg.c_str());
                }
        };

        class ChildProcess {
            public:
                ChildProcess() noexcept = default;
                pid_t create() {
                    this->_id = fork();
                    if (this->_id == -1)
                        throw ForkFailed();
                    return (this->_id);
                }
                ~ChildProcess() {
                    printf("Child %p w/ %u destroyed\n", this, this->_id);
                }
                pid_t operator*() const {
                    return (this->_id);
                }

            private:
                pid_t _id;
        };
    }

    class ChildProcessPool {
        public:
            ChildProcessPool() noexcept = default;
            ~ChildProcessPool() {
                for (auto &child : this->_pool)
                    kill(*child, SIGKILL);
            }
            pid_t add() {
                ChildProcess::ChildProcess child;
                pid_t pid = child.create();
                if (pid != 0)
                    this->_pool.emplace_back(child);
                return (pid);
            }

        private:
            std::list<ChildProcess::ChildProcess> _pool;
    };
}

#endif
