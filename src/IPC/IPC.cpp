/*
** EPITECH PROJECT, 2020
** ipc
** File description:
** IPC
*/

#include "IPC.hpp"

template<class A, class D>
IPC::IPC<A, D>::IPC(A parent, D child) : _ascendant(parent), _descendant(child) {
}

template<class A, class D>
A IPC::IPC<A, D>::getAscendant() const {
    return (this->_ascendant);
}

template<class A, class D>
D IPC::IPC<A, D>::getDescendant() const {
    return (this->_descendant);
}

template<class A, class D>
D IPC::IPC<A, D>::operator->() {
    return (this->getDescendant());
}
