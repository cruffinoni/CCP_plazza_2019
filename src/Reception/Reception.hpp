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
#include "IPC/IPC.hpp"

namespace Kitchen {
    class Kitchen;
}

namespace Reception {
    class Reception {
        public:
            Reception(uint16_t cooks, float multiplicator, uint16_t refresh);
            ~Reception();

            void addKitchen();

        protected:
        private:
            uint16_t _cooks;
            float _multiplicator;
            uint16_t _refreshStock;
            std::list<IPC::IPC<Reception *, std::shared_ptr<Kitchen::Kitchen>>> _kitchenList;

    };

} // namespace Reception



#endif /* !RECEPTION_HPP_ */