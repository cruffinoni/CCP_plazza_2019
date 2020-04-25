/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <thread>
#include <mutex>
#include <iostream>


class Cook {
    public:
        Cook(void *mut, void *stock);
        ~Cook();

        bool checkWork();


    protected:
    private:
        void *_mut;
        void *_stock;

};

#endif /* !COOK_HPP_ */
