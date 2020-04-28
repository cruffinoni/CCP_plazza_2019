/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "IPC/IPC.hpp"
#include "Kitchen/Kitchen.hpp"
#include "Pizza/Pizza.hpp"
#include "Reception/Reception.hpp"

int main(const int ac, const char **av)
{
    //IPC::IPC<Kitchen, Kitchen> ipc(new Kitchen(10,5,5), new Kitchen(10,5,5));
    //ipc->_cookingTime;
    //ipc.getDescendant()->_cookingTime;


    //Pizza::PMargarita marga(Pizza::PizzaSize::XXL);
    //Cook parent;
    // std::list<IPC::IPC<Reception, std::shared_ptr<Kitchen::Kitchen>>>
    // std::list<IPC::IPC<Kitchen::Kitchen, std::shared_ptr<Cook>>>
    //IPC::IPC<Cook, std::shared_ptr<Kitchen::Kitchen>> ipc(parent);
    //Kitchen::Kitchen kitchen(4, ipc);
    //ipc.setDescendant(kitchen);



    Reception::Reception recp(3, 4, 5);
    for (int i = 0; i < 3; ++i)
        recp.addKitchen();
    while(1) {
        recp.closeKitchen();
    }
    return (0);
}

/* RECEPTION
 * KITCHEN
 * COOK
 */
