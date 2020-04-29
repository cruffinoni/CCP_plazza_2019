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

    void Reception::addKitchen() {
        Plazza::IPC<Reception *, std::shared_ptr<Kitchen::Kitchen>> ipc(this);
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

    void Reception::addOrder(Pizza::pizza_t pizza, uint16_t nb) {
        std::list<Pizza::pizza_t> list;
        for (uint16_t i = 0; i < nb; ++i)
            list.push_back(pizza);
        _orders.push_back(list);
    }

    void Reception::updateOrders(Pizza::pizza_t pizza) {
        for (auto it : _orders) {
            for (auto i : it) {
                if (pizza == i && i.status != Pizza::Status::BAKED) {
                    i.status = Pizza::Status::BAKED;
                    return;
                }
            }
        }
    }

    void Reception::outputOrders() {
        uint16_t counter;
        for (auto it = _orders.begin(); it != _orders.end();) {
            counter = 0;
            for (auto i : *it) {
                if (i.status == Pizza::Status::BAKED)
                    counter++;
                else {
                    counter = -1;
                    break;
                }
            }
            if (counter > 0) {
                std::cout << "order finish : [pizzatype] = " << it->begin()->pizza << " | [pizzasize] = " << it->begin()->size << " * " << counter << std::endl;
                it = _orders.erase(it);
            } else
                it++;
        }
    }
}


