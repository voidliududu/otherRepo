//
// Created by liududu on 17-10-7.
//

#include <iostream>
#include "Seller.h"
Seller::Seller() {
    Item* i = new DicItem("001","巨佬","散装品",12.8,"斤",300,10.8);
    shop.add(i);
    i = new Item("002","小弟弟","独立包装",18.3,"只",600);
    shop.add(i);
    i = new Item("003","大哥哥","散装品",21,"斤",300);
    shop.add(i);
    i = new Item("004","男神","独立包装",22,"枚",30);
    shop.add(i);
    i = new Item("005","小姐姐","独立包装",50,"个",3);
    shop.add(i);
    i = new DicItem("006","小哥哥","散装品",30,"斤",300,25);
    shop.add(i);
    i = new Item("007","大姐姐","独立包装",21,"位",300);
    shop.add(i);
    i = new Item("008","apache","散装品",28,"斤",300);
    shop.add(i);
    i = new Item("002","mysql","散装品",21,"斤",300);
    shop.add(i);
    i = new DicItem("010","java","散装品",21,"斤",300,18);
    shop.add(i);
}

void Seller::println(const string& word){
    cout<<word<<endl;
}

string Seller::getCommand(){
    string command;
    cout<<"shop>>";
    cin>>command;
    cin.clear();
    cin.ignore(1024,'\n');
    return command;
}

bool Seller::judgeCommand(string command) {
    if(command == "help")
        this->help();
    else if(command == "list")
        this->list();
    else if(command == "buy")
        this->buy();
    else if(command == "cart")
        this->listCart();
    else if(command == "drop")
        this->drop();
    else if(command == "pay")
        this->pay();
    else if(command == "discount")
        this->showDiscount();
    else if(command == "version")
        this->version();
    else if(command == "exit"){
        cout<<"再见"<<endl;
        exit(0);
    }
    else {
        println("未识别的命令");
        return false;
    }
}

void Seller::greeting(){
    println("欢迎使用超市购物系统");
    println("输入help获取帮助");
}

void Seller::help(){
    println("使用帮助");
    println("在提示符shop>>后输入命令执行操作");
    println("help      显示这份帮助");
    println("discount  显示打折信息");
    println("list      列出所有商品");
    println("buy       购买");
    println("cart      显示当前购买");
    println("drop      丢弃已购买的一件商品");
    println("pay       付款并结束购物");
    println("version   显示作者和版本信息");
    println("exit      退出");
}

void Seller::showDiscount(){
    cout<<"暂不打折"<<endl;
}
void Seller::onSell(){
    greeting();
    while(true){
        //cin.ignore();
        judgeCommand(getCommand());
    }
}

void Seller::list(){
    shop.list();
}

void Seller::buy() {
    cout<<"==请输入您要购买的商品的编号>";
    string id;
    cin.clear();
    cin>>id;
    Item* item = shop.sell(id);
    if(item != NULL) {
        cart.add(item);
        cout << "购买成功，可在购物车中查看\n";
    }
    else
        cout<<"怕是买不了呦\n";
}

void Seller::listCart(){
    cart.list();
}

void Seller::drop(){
    cout<<"==请输入您要放弃购买的商品编号>";
    string id;
    cin>>id;
    cin.clear();
    cin.ignore(1024,'\n');
    Item* item = cart.drop(id);
    if(item != NULL) {
        shop.add(item);
        cout<<"已从购物车移除\n";
    }
}

void Seller::printHead(){
    char t[255];
    time_t ti = time(NULL);
    cout<<"\n**********程序部超市************\n";
    strftime(t, sizeof(t), "%Y/%m/%d %X",localtime(&ti));
    cout<<t<<endl;
}

void Seller::printTail(){
    cout<<"******************************\n";
    cout<<"应付:               "<<discount(cart._getTotal())<<endl;
    cout<<"实付:               "<<this->payment<<endl;
    cout<<"找零:               "<<this->payment - cart._getTotal();
    cout<<"\n******************************\n";
    cout<<"**********谢谢惠顾!*************\n";
}
void Seller::print(){
    printHead();
    cart.print();
    printTail();
}

void Seller::getPay(){
    double pay = 0;
    cout<<"您的消费为："<<cart._getTotal()<<"元"<<endl;
    cout<<"==请输入付款金额>";
    cin>>pay;
    cin.clear();
    cin.ignore(1024,'\n');
    if(pay == 0){
        cout<<"输入有误\n";
        return getPay();
    }
    if(pay <= cart._getTotal()){
        cout<<"输入金额不足\n";
        return getPay();
    }
    this->payment = pay;
}

void Seller::pay(){
    if(cart.getTotal() == 0){
        cout<<"你还没有购物"<<endl;
        return;
    }
    getPay();
    print();
    exit(0);
}

double Seller::discount(double total) {
    return total;
}

void Seller::version() {
    cout<<"Author: 刘都都"<<endl;
    cout<<"License: GPL"<<endl;
}