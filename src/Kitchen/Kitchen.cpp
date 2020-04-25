/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

void *starter(void *a, void *b)
{
    auto test = static_cast<std::mutex*>(b);
    test->lock();
    auto *_a = static_cast<unsigned long long *>(a);
    printf("Start: %llu\n", *_a);
    for (unsigned long long k = (*_a) + 100000; (*_a) < k;)
        *_a = *_a + 1;
    test->unlock();
    return (nullptr);
}

Kitchen::Kitchen(unsigned short nb, float timer, unsigned int refresh) :
 _cookingTime(timer), _stockRefresh(refresh)
{
    // unsigned long long a = 0;
    // for (int i = 0; i < 50; ++i)
    //     _cooksList.emplace_back(std::thread(starter, &a, &_mut));
    // for (auto &it : _cooksList)
    //     it.join();

    // std::cout << a << std::endl;
    int stock = 86;
    for (int i = 0; i < nb; ++i)
        _cooksList.emplace_back(new Cook(&_mut, &stock));
    for (auto &it :_cooksList) {
        it->checkWork();
        
    }

}

Kitchen::~Kitchen()
{
}
