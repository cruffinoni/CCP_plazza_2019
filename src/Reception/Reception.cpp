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

    void Reception::closeKitchen() {
        std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();

        for (auto it = _kitchenList.begin(); it != _kitchenList.end();) {
            auto delta = (time - it->getDescendant()->getTime());
            if (std::chrono::duration_cast<std::chrono::seconds>(delta).count() > DEFAULT_KITCHEN_TIMEOUT) {
                std::cout << "close Kitchen" << std::endl;
                it = _kitchenList.erase(it);
            } else
                ++it;
        }
    }
}


