/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <list>
#include <cstdint>
#include "Plazza/IPC.hpp"
#include "Pizza/Pizza.hpp"
#include "Plazza/Mutex.hpp"
#include "Plazza/ChildProcess.hpp"

namespace Kitchen {
    class Kitchen;
}

namespace Reception {
    class Reception {
        public:
            typedef Plazza::IPC<Reception *, std::shared_ptr<Kitchen::Kitchen>> ReceptionIPC_t;
            typedef std::shared_ptr<ReceptionIPC_t> SharedReceptionIPC_t;
            Reception(uint16_t cooks, float multiplier, uint16_t refresh);
            ~Reception() = default;

            void addKitchen();
            void closeKitchen(std::shared_ptr<Kitchen::Kitchen> &kitchen);

            void addOrder(Pizza::pizza_t &pizza, uint16_t nb);
            void addOrder(Pizza::pizza_t &&pizza, uint16_t nb);
            void checkCompletedOrders();
            //void completePizza(std::shared_ptr<Pizza::pizza_t> baked);

        private:
            void dispatchPizza(std::list<std::shared_ptr<Pizza::pizza_t>> &order);

            uint16_t _cooks;
            float _multiplier;
            uint16_t _refreshStock;
            Plazza::Mutex _mutex;

            std::list<std::list<std::shared_ptr<Pizza::pizza_t>>> _orders;
            Plazza::ChildProcessPool _childPool;
            Plazza::IPCPool<Reception *, Kitchen::Kitchen> _kitchenPool;
            static const int DEFAULT_KITCHEN_TIMEOUT = 5;
    };
}

#endif /* !RECEPTION_HPP_ */
