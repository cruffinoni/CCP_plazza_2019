/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** APizza
*/

#ifndef APIZZA_HPP_
#define APIZZA_HPP_

#include <map>

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
        Chief_Love, // ps je crois qu'on se fait troll mais bon j'ai laissé
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

    static std::map<Ingredients, int> _regina = {
        {Doe, 1},
        {Tomato, 1},
        {Gruyere, 1}
    };

    static std::map<Ingredients, int> _margarita = {
        {Doe, 1},
        {Tomato, 1},
        {Gruyere, 1},
        {Ham, 1},
        {Mushrooms, 1}
    };

    static std::map<Ingredients, int> _americana = {
        {Doe, 1},
        {Tomato, 1},
        {Gruyere, 1},
        {Steak, 1}
    };

    static std::map<Ingredients, int> _fantasia = {
        {Doe, 1},
        {Tomato, 1},
        {Eggplant, 1},
        {Goat_Cheese, 1},
        {Chief_Love, 1}
    };

    enum Status {
        WAITING,
        COOKING,
        BAKED
    };

    class APizza {
        public:
            APizza(PizzaType type, PizzaSize size, std::map<Ingredients, int> pizza, int timer);
            ~APizza();


            PizzaType getType() const;
            PizzaSize getSize() const;
            std::map<Ingredients, int> getIngredientsList() const;
            Status getStatus() const;
            int getMutiplicator() const;

            void startCooking();
            void isBaked();

        protected:
        private:
            PizzaType _type;
            PizzaSize _size;
            std::map<Ingredients, int> _pizza;
            int _multi;
            Status _status;

    };

    class PMargarita : public APizza {
        public:
            PMargarita(PizzaSize size);
    };

    class PRegina : public APizza {
        public:
            PRegina(PizzaSize size);
    };

    class PAmericana : public APizza {
        public:
            PAmericana(PizzaSize size);
    };

    class PFantasia : public APizza {
        public:
            PFantasia(PizzaSize size);
    };

} // namespace pizza


#endif /* !APIZZA_HPP_ */
