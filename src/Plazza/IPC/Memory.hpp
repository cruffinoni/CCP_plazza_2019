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
    namespace IPC {
        template <class A, class D>
        class Memory {
            public:
                explicit Memory(A parent) : _ascendant(parent) {}
                Memory(A parent, D child) : _ascendant(parent), _descendant(child) {}
                ~Memory() = default;

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
        class MemoryPool {
        public:
            typedef Memory<A, std::shared_ptr<D>> MemoryPool_t;

            MemoryPool() = default;
            template <typename ...variadic>
            explicit MemoryPool(uint16_t instances, A parent, variadic&&... args) {
                for (uint16_t i = 0; i < instances; ++i)
                    this->emplace_back(parent, args...);
            }
            ~MemoryPool() {
                for (auto &i: this->_pool)
                    i->getDescendant().reset(); // Force the deletion of every shared_ptr
                this->_pool.clear();
            }

            template <typename ...variadic>
            void emplace_back(A parent, variadic &&... args) {
                auto ipc = std::make_shared<MemoryPool_t>(parent);
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

            std::shared_ptr<MemoryPool_t> &back() {
                return (this->_pool.back());
            }
            std::shared_ptr<MemoryPool_t> &front() {
                return (this->_pool.front());
            }

            auto begin() {
                return (this->_pool.begin());
            }
            auto end() {
                return (this->_pool.end());
            }

        private:
            std::list<std::shared_ptr<MemoryPool_t>> _pool;
    };
    }
}

#endif /* !IPC_HPP_ */
