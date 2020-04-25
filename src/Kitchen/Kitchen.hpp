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
#include <iostream>
#include <memory>
#include "Cook.hpp"

class Kitchen {
    public:
        Kitchen(unsigned short cooks, float timer, unsigned int refresh);
        ~Kitchen();

    protected:
    private:
        float _cookingTime;
        unsigned int _stockRefresh;
        std::list<std::shared_ptr<Cook>> _cooksList;
        std::mutex _mut;


};

#endif /* !KITCHEN_HPP_ */
