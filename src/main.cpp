/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Plazza/IPC/Memory.hpp"
#include "Kitchen/Kitchen.hpp"
#include "Pizza/Pizza.hpp"
#include "Reception/Reception.hpp"
#include "Reception/CommandeReceiver.hpp"
#include "Plazza/IPC/FIFO.hpp"
#include "Plazza/IPC/MessageQueue.hpp"

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
    //printf("Core program -> %i\n", getpid());

    //Reception::Reception recp(2, 4, 5);
    //// for (int i = 0; i < 1; ++i) {
    ////     recp.addKitchen();
    //// }
    //
    //Reception::CommandeReceiver cmd;
    //
    //while(cmd.getStatus()) {
    //    std::string line = cmd.getLine();
    //    cmd.split(line, ';');
    //    auto list = cmd.takeList();
    //    for (auto act : list) {
    //        if (cmd.isValide(act)) {
    //            if (cmd.getStatus() == Reception::CommandeReceiver::EXIT)
    //                break;
    //            auto order = cmd.getOrder(act);
    //            if (cmd.getError())
    //                cmd.printError();
    //            else
    //                recp.addOrder(order.first, order.second);
    //        }
    //
    //    }
    //}
    // Reception::Reception reception(2, 4, 5);
    // for (int i = 0; i < 1; ++i) {
    //     reception.addKitchen();
    //     reception.addOrder(Pizza::pizza_t(Pizza::Regina, Pizza::S), 3);
    // }
    Plazza::IPC::MessageQueue test(10);
    test.send("Hello world", Plazza::IPC::MessageQueue::ASCENDANT);
    auto rtn = test.read(Plazza::IPC::MessageQueue::ASCENDANT);
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "READ: " << rtn << std::endl;
    return (0);
}
