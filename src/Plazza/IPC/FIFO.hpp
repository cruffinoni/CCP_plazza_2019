/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_IPC_FIFO
#define SRC_IPC_FIFO

#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <limits.h>

namespace Plazza {
    namespace IPC {
        namespace Exceptions {
            class UnableFifoCreation : public std::exception {
                public:
                    UnableFifoCreation() = default;
                    const char *what() const noexcept override {
                        const static std::string msg = "Unable to create the fifo file. "
                                                       "Error: " + std::string(strerror(errno));
                        return (msg.c_str());
                    }
            };

            class InvalidRead : public std::exception {
                public:
                    InvalidRead() = default;
                    const char *what() const noexcept override {
                        const static std::string msg = "Invalid write return value. "
                                                       "Error: " + std::string(strerror(errno));
                        return (msg.c_str());
                    }
            };
        }

        class Fifo {
            public:
                explicit Fifo(const std::string &path) {
                    this->_path = path;
                    this->_fd = mkfifo(path.c_str(), 0666);
                    if (this->_fd == -1)
                        throw Exceptions::UnableFifoCreation();
                }
                ~Fifo() {
                    close(this->_fd);
                }


            private:
                int _fd;
                std::string _path;
        };
    }
}

#endif
