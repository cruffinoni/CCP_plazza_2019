/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** APizza
*/

#include "APizza.hpp"

namespace Pizza
{
    APizza::APizza(PizzaType type, PizzaSize size, std::map<Ingredients, int> pizza, int timer) :
     _type(type), _size(size), _pizza(pizza), _multi(timer), _status(WAITING)
    {
    }

    APizza::~APizza(){}

    PizzaType APizza::getType() const {return _type;}
    PizzaSize APizza::getSize() const {return _size;}
    std::map<Ingredients, int> APizza::getIngredientsList() const {return _pizza;}
    Status APizza::getStatus() const {return _status;}
    int APizza::getMutiplicator() const {return _multi;}

    void APizza::startCooking() {_status = COOKING;}
    void APizza::isBaked() {_status = BAKED;}


    //###################################################

    PMargarita::PMargarita(PizzaSize size) : APizza(PizzaType::Margarita, size, _margarita, 1) {}

    PRegina::PRegina(PizzaSize size) : APizza(PizzaType::Regina, size, _regina, 2) {}

    PAmericana::PAmericana(PizzaSize size) : APizza(PizzaType::Americana, size, _americana, 2) {}

    PFantasia::PFantasia(PizzaSize size) : APizza(PizzaType::Fantasia, size, _fantasia, 4) {}

} // namespace Pizza

