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

namespace IPC {
    template <class A, class D>
    class IPC {
        public:
            IPC(A parent, D child);
            ~IPC() = default;

            A getAscendant() const;
            D getDescendant() const;

            D operator->();

        private:
            A _ascendant;
            D _descendant;
    };
} // namespace IPC

#endif /* !IPC_HPP_ */
