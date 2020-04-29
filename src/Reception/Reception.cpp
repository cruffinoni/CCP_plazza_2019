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
    Reception::Reception(uint16_t cooks, float multiplier, uint16_t refresh) :
        _cooks(cooks), _multiplier(multiplier), _refreshStock(refresh)
    {}

    void Reception::addKitchen() {
        Plazza::IPC<Reception *, std::shared_ptr<Kitchen::Kitchen>> ipc(this);
        auto kitchen = std::make_shared<Kitchen::Kitchen>(this->_cooks, ipc);
        ipc.setDescendant(kitchen);
        _kitchenList.emplace_back(ipc);
        this->addOrder(Pizza::pizza_t(Pizza::Americana, Pizza::S), 2);
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
    /*
     * TODO: Faire une fonction de remove dans la reception appelé par la kitchen et
     * check si la commande est complétée ainsi, la remove si c'est le cas
     */

    void Reception::addOrder(Pizza::pizza_t &pizza, uint16_t nb) {
        std::list<std::shared_ptr<Pizza::pizza_t>> list;
        for (uint16_t i = 0; i < nb; ++i)
            list.push_back(std::make_shared<Pizza::pizza_t>(pizza));
        _orders.push_back(list);
    }

    void Reception::addOrder(Pizza::pizza_t &&pizza, uint16_t nb) {
        std::list<std::shared_ptr<Pizza::pizza_t>> list;
        for (uint16_t i = 0; i < nb; ++i)
            list.push_back(std::make_shared<Pizza::pizza_t>(pizza));
        _orders.push_back(list);
        // TODO: Move dans une fonction l'algo de dispatch & le faire pizza/pizza
        for (auto &kitchen : this->_kitchenList) {
            printf("Space available: %zu\n", kitchen->getAvailableSpace());
        }
    }

    void Reception::outputOrders() {
        uint16_t counter;

        for (auto order = _orders.begin(); order != _orders.end();) {
            counter = 0;
            for (auto &pizza : *order) {
                if (pizza->status == Pizza::Status::BAKED)
                    counter++;
                else {
                    counter = -1;
                    break;
                }
            }
            if (counter > 0) {
                std::cout << "order finish : [pizzatype] = " << order->begin()->get()->type << " | [pizzasize] = " << order->begin()->get()->size << " * " << counter << std::endl;
                order = _orders.erase(order);
            } else
                order++;
        }
    }
}


