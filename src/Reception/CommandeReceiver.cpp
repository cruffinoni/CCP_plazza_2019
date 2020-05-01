/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** CommandeReceiver
*/

#include "CommandeReceiver.hpp"

namespace Reception
{
    CommandeReceiver::CommandeReceiver() : _status(RUN), _err(NONE)
    {}

    std::string CommandeReceiver::getLine() {
        std::string line;
        getline(std::cin, line);
        return line;
    }

    bool CommandeReceiver::isValide(std::string &str) {
        std::regex cmdReg("^[a-zA-Z]+ (S|M|L|XL|XXL) x[0-9]+");

        if (std::regex_match(str, cmdReg)) {
            return true;
        } else if (str == "exit") {
            _status = EXIT;
            return true;
        } else {
            std::cout << "BAD CMD " << str << std::endl;
            return false;
        }
    }

    void CommandeReceiver::split(std::string &str, char separator) {
        size_t pos = str.find(separator);
        while (pos != std::string::npos) {
                std::string string = str.substr(0, pos);
                if (string.find(separator) != std::string::npos)
                    string.erase(string.find(separator));
                str.erase(0, pos + 1);
                _list.push_back(string);
                pos = str.find(separator);
                while(str.find(' ') == 0)
                    str.erase(0, 1);
        }
        if (str.size() > 0)
        _list.push_back(str);
    }

    std::list<std::string> CommandeReceiver::takeList() {
        auto tmp = _list;
        _list.clear();
        return tmp;
    }

    std::pair<Pizza::pizza_t, uint16_t> CommandeReceiver::getOrder(std::string &cmd) {

        std::regex reg("(^[a-zA-Z]+) (S|M|L|XL|XXL) (x[0-9]+)");
        std::smatch matches;
        std::regex_search(cmd, matches, reg);
        std::string name = matches[1];
        std::string size = matches[2];
        std::string nb = matches[3];
        std::pair<Pizza::pizza_t, uint16_t> pizza = {{getType(name), getSize(size)}, getNb(nb)};
        return pizza;
    }


    void CommandeReceiver::printList() const {
        std::cout << "---------" << std::endl;
        std::cout << "list size :" << _list.size() << std::endl;
        for (auto line : _list)
            std::cout << line << std::endl;
        std::cout << "---------" << std::endl;
    }

    Pizza::PizzaType CommandeReceiver::getType(std::string &type) {
        uint16_t counter = 0x1;
        Pizza::PizzaType pizza = Pizza::PizzaType::None;
        std::transform(type.begin(), type.end(), type.begin(), ::tolower);
        for (auto it : Pizza::PizzaName) {
            if (it == type) {
                pizza = Pizza::PizzaType(counter);
                break;
            }
            counter = counter << 1;
        }
        if (pizza == 0)
            _err = TYPE;
        return pizza;
    }
    Pizza::PizzaSize CommandeReceiver::getSize(std::string &size) {
        uint16_t counter = 0x1;
        Pizza::PizzaSize pSize;
        for (auto it : Pizza::SizeName) {
            if (it == size) {
                pSize = Pizza::PizzaSize(counter);
                break;
            }
            counter = counter << 1;
        }
        return pSize;
    }
    int CommandeReceiver::getNb(std::string &nb){
        nb.erase(0, 1);
        int nbr = std::stoi(nb);
        if (nbr <= 0) {
            _err = VALUE;
            nbr = 0;
        }
        return nbr;
    }


    CommandeReceiver::Error CommandeReceiver::getError() const {return _err;}
    void CommandeReceiver::printError() {
        switch (_err) {
        case TYPE: std::cout << "Invalid Type" << std::endl; break;
        case VALUE: std::cout << "Invalide number" << std::endl; break;
        default:break;
        }
        _err = NONE;
    }
    CommandeReceiver::State CommandeReceiver::getStatus() const {return _status;}

} // namespace Reception


