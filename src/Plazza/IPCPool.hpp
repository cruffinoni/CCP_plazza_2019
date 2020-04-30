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
#include <functional>
#include "IPC.hpp"

namespace Plazza {
    template <class A, class D>
    class IPCPool {
        public:
            typedef IPC<A, std::shared_ptr<D>> IPCPool_t;

            IPCPool() = default;
            template <typename ...variadic>
            explicit IPCPool(uint16_t instances, A parent, variadic&&... args) {
                for (uint16_t i = 0; i < instances; ++i)
                    this->add(parent, args...);
            }
            ~IPCPool() {
                for (auto &i: this->_pool)
                    i->getDescendant().reset(); // Force the deletion of every shared_ptr
                this->_pool.clear();
            }

            template <typename ...variadic>
            void add(A parent, variadic &&... args) {
                auto ipc = std::make_shared<IPCPool_t>(parent);
                std::shared_ptr<D> descendant = std::make_shared<D>(std::forward<variadic>(args)..., ipc);
                ipc->setDescendant(descendant);
                this->_pool.emplace_back(ipc);
            }

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
