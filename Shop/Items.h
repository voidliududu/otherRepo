//
// Created by liududu on 17-10-7.
//

#ifndef SHOP_ITEMS_H
#define SHOP_ITEMS_H

#include <string>

using namespace std;

//商品类
class Item{
protected:
    string id;
    string name;
    string type;
    double price;
    string measure;
    double num;
    Item* next;
    //Item* createItem(double num);
public:
    friend class Store;
    Item(string id,string name,string type,double price,string measure,
    double num):id(id),name(name),type(type),price(price),measure(measure),num(num){next = NULL;}
    Item() = default;
    Item(const Item&, double num);
    virtual double getPrice();
    virtual void display();
    virtual Item* sold();
    virtual void print();
};

//打折商品类
class DicItem :public Item{
private:
    double dicPrice;
public:
    DicItem(string id,string name,string type,double price,string measure,
            double num,double dicprice):
            Item(id,name,type,price,measure,num),dicPrice(dicprice){next = NULL;}
    //DicItem() = default;
    DicItem(const DicItem&,double num);
    virtual double getPrice();
    virtual void display();
    virtual Item* sold();
    virtual void print();
};
#endif //SHOP_ITEMS_H
