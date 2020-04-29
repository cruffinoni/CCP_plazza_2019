/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** APizza
*/

#ifndef APIZZA_HPP_
#define APIZZA_HPP_

#include <map>
#include <list>

namespace Pizza {
    enum Ingredients {
        Ingredient_None,

        Doe,
        Tomato,
        Gruyere,
        Ham,
        Mushrooms,
        Steak,
        Eggplant,
        Goat_Cheese,
        Chief_Love,

        Invalid
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    enum PizzaType {
        None = 0,
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    static std::map<PizzaType, std::pair<std::list<Ingredients>, int>> PizzaList = {
        {Regina, {{Doe, Tomato, Gruyere}, 1}},
        {Margarita, {{Doe, Tomato, Gruyere, Ham}, 2}},
        {Americana, {{Doe, Tomato, Gruyere, Steak}, 2}},
        {Fantasia, {{Doe, Tomato, Eggplant, Goat_Cheese, Chief_Love}, 4}}
    };

    struct pizza_t {
        PizzaType pizza;
        PizzaSize size;
    };
}


#endif /* !APIZZA_HPP_ */
