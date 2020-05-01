/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** CommandeReceiver
*/

#ifndef COMMANDERECEIVER_HPP_
#define COMMANDERECEIVER_HPP_

#include <iostream>
#include <regex>
#include "Pizza/Pizza.hpp"

namespace Reception
{
    class CommandeReceiver {
        public:
            CommandeReceiver();
            ~CommandeReceiver() = default;

            enum State {
                EXIT,
                RUN
            };
            enum Error {
                NONE,
                TYPE,
                VALUE
            };

            std::string getLine();
            bool isValide(std::string &str);
            void split(std::string &str, char separator);
            std::list<std::string> takeList();
            std::pair<Pizza::pizza_t, uint16_t> getOrder(std::string &cmd);

            State getStatus() const;

            void printList() const; //to remove

            Pizza::PizzaType getType(std::string &type);
            Pizza::PizzaSize getSize(std::string &size);
            int getNb(std::string &nb);

            Error getError() const;
            void printError();

        protected:
        private:
            State _status;
            std::list<std::string> _list;
            Error _err;
    };
} // namespace Reception


#endif /* !COMMANDERECEIVER_HPP_ */
