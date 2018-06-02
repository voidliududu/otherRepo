//
// Created by liududu on 17-10-7.
//

#ifndef SHOP_SELLER_H
#define SHOP_SELLER_H


#include "Store.h"
//#include "ShopCart.h"

class Seller {
private:
    Store shop;
    Store cart;
    double payment;
    void println(const string&);
    string getCommand();
    bool judgeCommand(string command);
    void list();
    void buy();
    void listCart();
    void drop();
    void print();
    void printHead();
    void printTail();
    void getPay();
    void pay();
    double discount(double total);
    void showDiscount();
    void version();
public:
    Seller();
    void greeting();             //输出问候信息
    void help();               //输出帮助信息
    void init();                //初始化商店
    void onSell();               //进入交互模式，开始出售

};


#endif //SHOP_SELLER_H
