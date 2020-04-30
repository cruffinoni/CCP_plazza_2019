/*
** EPITECH PROJECT, 2020
** ipc
** File description:
** IPC
*/

#ifndef IPC_HPP_
#define IPC_HPP_

#include <list>
#include <memory>
#include <iostream>

namespace Plazza {
    template <class A, class D>
    class IPC {
        public:
            explicit IPC(A parent) : _ascendant(parent) {}
            IPC(A parent, D child) : _ascendant(parent), _descendant(child) {}
            ~IPC() = default;

            A &getAscendant() {
                return (this->_ascendant);
            }

            D &getDescendant() {
                return (this->_descendant);
            }

            void setDescendant(D &a)  {
                this->_descendant = a;
            }

            D operator->()  {
                return (this->getDescendant());
            }

        private:
            A _ascendant;
            D _descendant;
    };

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

#endif /* !IPC_HPP_ */
