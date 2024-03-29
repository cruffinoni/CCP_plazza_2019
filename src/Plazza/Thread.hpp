/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_PLAZZA_THREAD_
#define SRC_PLAZZA_THREAD_

#include <thread>

namespace Plazza {
    class Thread {
        public:
            template<class func, typename ...variadic>
            explicit Thread(func &&fn, variadic &&... args) {
                this->_thread = std::make_shared<std::thread>(fn, std::forward<variadic>(args)...);
            }
            Thread() = delete;

            ~Thread() {
                if (this->_thread->joinable())
                    this->_thread->join();
            }
        private:
            std::shared_ptr<std::thread> _thread;
    };
}

#endif
