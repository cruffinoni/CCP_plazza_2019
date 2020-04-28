/*
** EPITECH PROJECT, 2020
** ipc
** File description:
** IPC
*/

#ifndef IPC_HPP_
#define IPC_HPP_

#include <list>
#include <iostream>

namespace COM {



    enum Type {
        RECEP,
        KITCHEN,
        COOK
    };


    class Stock {
        public:
            int _stock = 10;
    };

    class IPC {
        public:
            IPC(Type type);
            ~IPC();

            void setStock(Stock &stock);
            Stock &getStock();


        protected:
        private:
            Type _type;
            Stock _stock;
    };

    typedef struct assign_s {
        short id;
        IPC Object;
    }assign_t;
    enum Request{
        GET_STOCK
    };

    static std::list<assign_t *> list;
    bool askFor(short id, Request req, std::list<assign_t *>);
} // namespace IPC



#endif /* !IPC_HPP_ */
