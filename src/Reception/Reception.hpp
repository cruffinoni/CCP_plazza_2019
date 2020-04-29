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

namespace Kitchen {
    class Kitchen;
}

namespace Reception {
    class Reception {
        public:
            Reception(uint16_t cooks, float multiplier, uint16_t refresh);
            ~Reception() = default;

            void addKitchen();
            void closeKitchen();

            void addOrder(Pizza::pizza_t &pizza, uint16_t nb);
            void addOrder(Pizza::pizza_t &&pizza, uint16_t nb);
            void outputOrders();

        private:
            uint16_t _cooks;
            float _multiplier;
            uint16_t _refreshStock;
            std::list<Plazza::IPC<Reception *, std::shared_ptr<Kitchen::Kitchen>>> _kitchenList;
            std::list<std::list<std::shared_ptr<Pizza::pizza_t>>> _orders;
            static const int DEFAULT_KITCHEN_TIMEOUT = 5;
    };
}

#endif /* !RECEPTION_HPP_ */
