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
}

#endif /* !IPC_HPP_ */
