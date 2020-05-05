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
        //this->_mutex.try_lock();
        this->_kitchenPool.emplace_back(this, this->_cooks);
        //this->_mutex.unlock();
        try {
            if (this->_childPool.add() == 0) {
                printf("(Child created) This: %p\n", this);
                this->_kitchenPool.back()->getDescendant()->run();
                exit(0);
            }
        } catch (const Plazza::ChildProcess::ForkFailed &e) {
            std::cerr << e.what() << std::endl;
        }
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
        //printf("Front: %p\n", this->_kitchenPool.front()->getDescendant().get());
    }

    void Reception::checkCompletedOrders() {
        Plazza::ScopedLock scopedLock(this->_mutex, "checkCompletedOrders");
        bool completed;

        for (auto orders = _orders.begin(); orders != _orders.end(); ++orders) {
            completed = true;
            //printf("order: %p ->\n", &*orders);
            for (auto &pizza : *orders) {
                //printf("Pizza COMPLETED %p & %i?\n", pizza.get(), pizza->status);
                if (pizza->status != Pizza::Status::BAKED)
                    completed = false;
            }
            if (completed) {
                std::cout << "order finish : [pizzatype] = " << orders->begin()->get()->type << " | [pizzasize] = " << orders->begin()->get()->size << std::endl;
                this->_orders.erase(orders);
                return;
            }
        }
    }

    void
    Reception::dispatchPizza(std::list<std::shared_ptr<Pizza::pizza_t>> &list) {
        size_t lessBusy;
        std::shared_ptr<Kitchen::Kitchen> kitchen;
        size_t space;
        Plazza::ScopedLock scopedLock(this->_mutex, "dispatchPizza");
        for (auto pizza = list.begin(); pizza != list.end(); ++pizza) {
            lessBusy = 0;
            for (auto &ipc: this->_kitchenPool) {
                space = ipc->getDescendant()->getAvailableSpace();
                if (space > lessBusy) {
                    kitchen = ipc->getDescendant();
                    lessBusy = space;
                }
            }
            printf("Less busy: %zu\n", lessBusy);
            if (lessBusy == 0) {
                std::cerr << "No space found for the pizza, trying again..." << std::endl;
                this->addKitchen();
                --pizza;
            } else {
                std::cout << "Adding pizza " << pizza->get() << std::endl;
                kitchen->addCommand(*pizza);
            }
        }
    }
}
