/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Reception
*/

#include <iostream>
#include "Reception.hpp"
#include "Kitchen/Kitchen.hpp"

namespace Reception {
    Reception::Reception(uint16_t cooks, float multiplier, uint16_t refresh) :
        _cooks(cooks), _multiplier(multiplier), _refreshStock(refresh)
    {}

    void Reception::addKitchen() {
        if (!this->_mutex.try_lock()) {
            std::cerr << "try lock invalid addKitchen" << std::endl;
            return;
        }
        this->_kitchenPool.add(this, this->_cooks);
        this->_mutex.unlock();
        this->addOrder(Pizza::pizza_t(Pizza::Regina, Pizza::S), 3);
    }

    void Reception::closeKitchen(std::shared_ptr<Kitchen::Kitchen> &kitchen) {
        if (!this->_kitchenPool.pop(kitchen))
            std::cerr << "A kitchen cannot be closed" << std::endl;
    }

    void Reception::addOrder(Pizza::pizza_t &pizza, uint16_t nb) {
        std::list<std::shared_ptr<Pizza::pizza_t>> list;
        for (uint16_t i = 0; i < nb; ++i)
            list.push_back(std::make_shared<Pizza::pizza_t>(pizza));
        _orders.push_back(list);
        this->dispatchPizza(list);
    }

    void Reception::addOrder(Pizza::pizza_t &&pizza, uint16_t nb) {
        std::list<std::shared_ptr<Pizza::pizza_t>> list;
        for (uint16_t i = 0; i < nb; ++i)
            list.push_back(std::make_shared<Pizza::pizza_t>(pizza));
        _orders.push_back(list);
        this->dispatchPizza(list);
        // TODO: À mettre dans le fork de l'enfant
        printf("Front: %p\n", this->_kitchenPool.front()->getDescendant().get());
        this->_kitchenPool.front()->getDescendant()->run();
    }

    void Reception::checkCompletedOrders() {
        uint16_t counter;
        Plazza::ScopedLock scopedLock(this->_mutex, "checkCompletedOrders");
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

    void
    Reception::dispatchPizza(std::list<std::shared_ptr<Pizza::pizza_t>> &list) {
        size_t lessBusy;
        std::shared_ptr<Kitchen::Kitchen> kitchen;
        size_t space;
        Plazza::ScopedLock scopedLock(this->_mutex, "dispatchPizza");

        for (auto &pizza : list) {
            lessBusy = 0;
            for (auto &ipc: this->_kitchenPool) {
                space = ipc->getDescendant()->getAvailableSpace();
                if (space > lessBusy) {
                    kitchen = ipc->getDescendant();
                    lessBusy = space;
                }
            }
            if (lessBusy == 0) {
                // TODO: Ouvrir une nouvelle cuisine et recommencer l'attribution de la commande
                //  actuelle ; besoin de remplacer le for (auto) ?
                std::cerr << "No space found for the pizza, cannot dispatch it" << std::endl;
            } else {
                //printf("Space before adding a cmd: %zu\n", space);
                kitchen->addCommand(pizza);
                //printf("Space after: %zu\n", kitchen->getAvailableSpace());
            }
        }
    }

    Reception::~Reception() {
        this->_orders.clear();
    }
}
