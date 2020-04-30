/*
** EPITECH PROJECT, 2018
** CCP_plazza_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_PLAZZA_IPCPOOL_
#define SRC_PLAZZA_IPCPOOL_

#include <list>
#include <memory>
#include "IPC.hpp"

namespace Plazza {
    template <class A, class D>
    class IPCPool {
        public:
            IPCPool() = default;
            IPCPool(uint16_t instance) {
                for (uint16_t i = 0; i < instance; ++i) {

                }
            }
            ~IPCPool() = default;
            typedef IPC<A, std::shared_ptr<D>> IPCPool_t;

            void add(std::shared_ptr<IPCPool_t> &ipc) {
                this->_pool.emplace_back(ipc);
            };

            void add(std::shared_ptr<IPCPool_t> &&ipc) {
                this->_pool.emplace_back(ipc);
            };

            bool pop(std::shared_ptr<D> &descendant) {
                for (auto i = this->_pool.begin(); i != this->_pool.end(); ++i) {
                    if (i->get()->getDescendant() == descendant) {
                        i->get()->getDescendant().reset();
                        this->_pool.erase(i);
                        return (true);
                    }
                }
                return (false);
            }

            std::shared_ptr<IPCPool_t> &back() {
                return (this->_pool.back());
            }

            std::shared_ptr<IPCPool_t> &front() {
                return (this->_pool.front());
            }

            auto begin() {
                return (this->_pool.begin());
            }

            auto end() {
                return (this->_pool.end());
            }

        private:
            std::list<std::shared_ptr<IPCPool_t>> _pool;
    };
}

#endif
