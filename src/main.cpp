/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Plazza/IPC.hpp"
#include "Kitchen/Kitchen.hpp"
#include "Pizza/Pizza.hpp"
#include "Reception/Reception.hpp"

int main(const int ac, const char **av)
{
    //Plazza::IPC<Kitchen, Kitchen> ipc(new Kitchen(10,5,5), new Kitchen(10,5,5));
    //ipc->_cookingTime;
    //ipc.getDescendant()->_cookingTime;


    //Pizza::PMargarita marga(Pizza::PizzaSize::XXL);
    //Cook parent;
    // std::list<Plazza::IPC<Reception, std::shared_ptr<Kitchen::Kitchen>>>
    // std::list<Plazza::IPC<Kitchen::Kitchen, std::shared_ptr<Cook>>>
    //Plazza::IPC<Cook, std::shared_ptr<Kitchen::Kitchen>> ipc(parent);
    //Kitchen::Kitchen kitchen(4, ipc);
    //ipc.setDescendant(kitchen);


    Reception::Reception recp(3, 4, 5);
    for (int i = 0; i < 1; ++i) {
        recp.addKitchen();
        recp.closeKitchen();
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return (0);
}

/* RECEPTION
 * KITCHEN
 * COOK
 */
