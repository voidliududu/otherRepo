//
// Created by liududu on 17-10-7.
//

#include <iostream>
#include "Items.h"

/**
 * 打印星星辅助的函数^_^
 *@param void
 *@return void
 * */
void printStar(){
    cout<<"************************************************************************************\n";
}
/**
 * 构造函数
 * @param item 商品对象的引用
 * @param num 商品的量
 * @return item
 * */
Item::Item(const Item &item,double num) {
    this->id = item.id;
    this->name = item.name;
    this->type = item.type;
    this->price = item.price;
    this->measure = item.measure;
    this->num = num;
    this->next = nullptr;
}

/**
 * 展示商品
 *
 * */
void Item::display(){
    printStar();
    cout<<"商品编号:"<<this->id<<"    ";
    cout<<"名称:"<<this->name<<"    ";
    cout<<"价格:"<<this->price<<"元每"<<this->measure<<"    ";
    cout<<"类型："<<this->type<<"    ";
    cout<<"数量:"<<this->num<<this->measure<<endl;
    printStar();
}
/**
 * 获取价格
 * @return double 价格
 * */
double Item::getPrice() {
    return price;
}
/**
 * 在购物小票中打印商品
 * */
void Item::print() {
    printf("%-8s  %.2f*%.2f  %.2f\n",this->name.c_str(),this->price,this->num,price*num);
}
/**
 * 售卖
 * @return Item* 取出的商品
 * */
//TODO 输入检查
Item* Item::sold() {
    cout<<"==请输入"<<this->name<<"的量(单位："<<this->measure<<")>";
    double count;
    cin>>count;
    cin.clear();
    cin.ignore(1024,'\n');
    if(type == "散装品"){
        if(count > 0) {
            if(this->num >= count) {
                this->num = this->num - count;
                return new Item(*this, count);
            }else{
                cout<<"库存不足"<<endl;
                return NULL;
            }
        }else{
            cout<<"输入有误"<<endl;
            return NULL;
        }
    }else{
        if(count == int(count) && count > 0){
            if(this->num >= count) {
                this->num = this->num - count;
                return new Item(*this, count);
            }else{
                cout<<"库存不足"<<endl;
                return NULL;
            }
        }else{
            cout<<"输入有误"<<endl;
            return NULL;
        }
    }
}

/**
 * 折扣品的构造函数
 * */
DicItem::DicItem(const DicItem& item,double num) {
    this->id = item.id;
    this->name = item.name;
    this->type = item.type;
    this->price = item.price;
    this->measure = item.measure;
    this->dicPrice = item.dicPrice;
    this->num = num;
    this->next = nullptr;
}

double DicItem::getPrice() {
    return dicPrice;
}

void DicItem::display(){
    printStar();
    cout<<"商品编号:"<<this->id<<"    ";
    cout<<"名称:"<<this->name<<"    ";
    cout<<"原价:"<<this->price<<"元每"<<this->measure<<"    ";
    cout<<"现价:"<<this->dicPrice<<"元每"<<this->measure<<"    ";
    cout<<"类型："<<this->type<<"    ";
    cout<<"数量:"<<this->num<<this->measure<<endl;
    printStar();
}


Item* DicItem::sold() {
    cout<<"==请输入"<<this->name<<"的量(单位："<<this->measure<<")>";
    double count;
    cin>>count;
    cin.clear();
    cin.ignore(1024,'\n');
    if(type == "散装品"){
        if(count > 0) {
            if(this->num >= count) {
                this->num = this->num - count;
                return new DicItem(*this, count);
            }else{
                cout<<"库存不足"<<endl;
                return NULL;
            }
        }else{
            cout<<"输入有误"<<endl;
            return NULL;
        }
    }else{
        if(count == int(count) && count > 0){
            if(this->num >= count) {
                this->num = this->num - count;
                return new DicItem(*this, count);
            }else{
                cout<<"库存不足"<<endl;
                return NULL;
            }
        }else{
            cout<<"输入有误"<<endl;
            return NULL;
        }
    }
}

void DicItem::print() {
    printf("%-8s  %.2f*%.2f  %.2f\n",this->name.c_str(),this->dicPrice,this->num,dicPrice*num);
}