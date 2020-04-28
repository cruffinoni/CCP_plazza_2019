/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** APizza
*/

#include "APizza.hpp"

namespace Pizza
{
    Pizza::Pizza(PizzaType type, PizzaSize size) :
     _type(type), _size(size), _ingre(pizzaList[type].first), _multi(pizzaList[type].second), _status(WAITING)
    {
    }

    Pizza::~Pizza(){}

    PizzaType Pizza::getType() const {return _type;}
    PizzaSize Pizza::getSize() const {return _size;}
    std::list<Ingredients> Pizza::getIngredientsList() const {return _ingre;}
    Status Pizza::getStatus() const {return _status;}
    int Pizza::getMutiplicator() const {return _multi;}

    void Pizza::startCooking() {_status = COOKING;}
    void Pizza::isBaked() {_status = BAKED;}


    //###################################################

} // namespace Pizza

