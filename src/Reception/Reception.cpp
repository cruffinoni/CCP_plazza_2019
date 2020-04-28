/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Reception
*/

#include "Reception.hpp"
#include "Kitchen/Kitchen.hpp"

namespace Reception
{
    Reception::Reception(uint16_t cooks, float multiplicator, uint16_t refresh) :
    _cooks(cooks), _multiplicator(multiplicator), _refreshStock(refresh)
    {}

    Reception::~Reception(){}

    void Reception::addKitchen() {
        IPC::IPC<Reception *, std::shared_ptr<Kitchen::Kitchen>> ipc(this);
        auto kitchen = std::make_shared<Kitchen::Kitchen>(this->_cooks, ipc);
        ipc.setDescendant(kitchen);
        _kitchenList.emplace_back(ipc);
    }
}


