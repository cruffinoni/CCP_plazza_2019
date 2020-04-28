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
        Doe,
        Tomato,
        Gruyere,
        Ham,
        Mushrooms,
        Steak,
        Eggplant,
        Goat_Cheese,
        Chief_Love,
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    typedef std::map<PizzaType, std::pair <std::list<Ingredients>, int>> Data_t;

    static Data_t pizzaList = {
        {Regina, {{Doe, Tomato, Gruyere}, 1}},
        {Margarita, {{Doe, Tomato, Gruyere, Ham}, 2}},
        {Americana, {{Doe, Tomato, Gruyere, Steak}, 2}},
        {Fantasia, {{Doe, Tomato, Eggplant, Goat_Cheese, Chief_Love}, 4}}
    };

    enum Status {
        WAITING,
        COOKING,
        BAKED
    };

    class Pizza {
        public:
            Pizza(PizzaType type, PizzaSize size);
            ~Pizza();


            PizzaType getType() const;
            PizzaSize getSize() const;
            std::list<Ingredients> getIngredientsList() const;
            Status getStatus() const;
            int getMutiplicator() const;

            void startCooking();
            void isBaked();

        protected:
        private:
            PizzaType _type;
            PizzaSize _size;
            std::list<Ingredients> _ingre;
            int _multi;
            Status _status;

    };

} // namespace pizza


#endif /* !APIZZA_HPP_ */
