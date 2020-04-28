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

namespace Kitchen {
    class Kitchen;
}

namespace Reception {
    class Reception {
        public:
            Reception(uint16_t cooks, float multiplicator, uint16_t refresh);
            ~Reception() = default;

            void addKitchen();
            void closeKitchen();

        private:
            uint16_t _cooks;
            float _multiplicator;
            uint16_t _refreshStock;
            std::list<Plazza::IPC<Reception *, std::shared_ptr<Kitchen::Kitchen>>> _kitchenList;
            static const int DEFAULT_KITCHEN_TIMEOUT = 5;
    };

} // namespace Reception



#endif /* !RECEPTION_HPP_ */
