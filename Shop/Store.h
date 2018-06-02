//
// Created by liududu on 17-10-7.
//

#ifndef SHOP_STORE_H
#define SHOP_STORE_H


#include "Items.h"

class Store {
private:
    Item* first;
    Item* last;
    Item* peer;
    int count;
    double total;
    Item* find(string id);
public:
    Store();
    Item* add(Item*);
    //Item* add(string id,double count);
    void list();
    double getTotal();
    double _getTotal();
    void print();
    Item* drop(string id);
    Item* sell(string id);
};


#endif //SHOP_STORE_H
