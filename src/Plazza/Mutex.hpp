/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_PLAZZA_MUTEX_
#define SRC_PLAZZA_MUTEX_

#include <mutex>

namespace Plazza {
    class Mutex {
        public:
            Mutex() : _mutex() {}

            void lock() {
                this->_mutex.lock();
            };

            bool try_lock() {
                return (this->_mutex.try_lock());
            };

            void unlock() {
                this->_mutex.unlock();
            };

        private:
            std::mutex _mutex;
    };

    class ScopedLock {
        public:
            explicit ScopedLock(Mutex &mutex, __attribute__ ((unused)) const std::string &location) : _mutex(mutex) {
                this->_mutex.try_lock();
            }

            ~ScopedLock() {
                _mutex.unlock();
            }
        private:
            Mutex &_mutex;
    };
}

#endif
