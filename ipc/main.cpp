/*
** EPITECH PROJECT, 2020
** ipc
** File description:
** main
*/

#include "IPC.hpp"
#include <list>

    static short idIncre;

int main(void) {

    idIncre = 0;

    COM::Stock stock1;
    COM::Stock stock2;
    stock1._stock = 15;
    stock2._stock = 46;

    std::cout << "ID_Incre init :" << idIncre << std::endl;

    COM::assign_t kitchen{idIncre, COM::IPC(COM::Type::KITCHEN)};
    std::cout << "ID[" << idIncre << "] assign to kitchen" << std::endl;
    kitchen.Object.setStock(stock1);
    std::cout << kitchen.Object.getStock()._stock << std::endl;
    idIncre++;

    COM::assign_t cook{idIncre, COM::IPC(COM::Type::COOK)};
    std::cout << "ID[" << idIncre << "] assign to cook" << std::endl;
    idIncre++;

    COM::list.push_back(&kitchen);
    COM::list.push_back(&cook);

    kitchen.Object.setStock(stock2);

    COM::askFor(0, COM::Request::GET_STOCK, COM::list);
    std::cout << COM::list.size() << std::endl;

    return 0;
}