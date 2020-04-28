/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <list>
#include <thread>
#include <mutex>
#include <memory>
#include <cstddef>
#include <chrono>
#include "Plazza/IPC.hpp"
#include "Plazza/Mutex.hpp"
#include "Kitchen/Cook.hpp"
#include "Pizza/Pizza.hpp"
#include "Reception/Reception.hpp"

namespace Kitchen {
    class Stock {
        public:
            Stock();
            void refresh();
            void withdrawStock(std::list<Pizza::Ingredients> &list);

            bool operator==(std::list<Pizza::Ingredients> &list);
            bool operator!=(std::list<Pizza::Ingredients> &list);
            ~Stock();

        private:
            std::map<Pizza::Ingredients, size_t> _food;
            static const size_t DEFAULT_INGREDIENT_QUANTITY = 5;
    };

    class Kitchen {
        public:
            Kitchen(uint16_t cooks, const Plazza::IPC<Reception::Reception *, std::shared_ptr<Kitchen>> &ipc);
            ~Kitchen();

            std::chrono::time_point<std::chrono::system_clock> getTime() const;
            void refreshStock();
            void withdrawStock(std::list<Pizza::Ingredients> &list);

        private:
            const Plazza::IPC<Reception::Reception *, std::shared_ptr<Kitchen>> _ipc;
            std::list<Plazza::IPC<Kitchen *, std::shared_ptr<Cook>>> _cooksList;
            Plazza::Mutex _mutex;
            Stock _stock;
            std::chrono::time_point<std::chrono::system_clock> _timer;
    };

}

#endif /* !KITCHEN_HPP_ */
