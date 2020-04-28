/*
** EPITECH PROJECT, 2020
** ipc
** File description:
** IPC
*/

#include "IPC.hpp"

namespace COM
{

    bool askFor(short id, Request req, std::list<assign_t*> list) {
        for (auto it : list) {
            //std::cout <<  id << " | " << it->id << std::endl;
            if(it->id == id) {
                std::cout << (it->Object.getStock())._stock << std::endl;
            }
        }
        return true;
    }
    IPC::IPC(Type type) : _type(type)
    {
    }

    IPC::~IPC()
    {
    }

    void IPC::setStock(Stock &stock) {_stock = stock;}
    Stock &IPC::getStock() {return _stock;}

} // namespace IPC


