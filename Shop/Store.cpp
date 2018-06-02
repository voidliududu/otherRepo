//
// Created by liududu on 17-10-7.
//

#include <iostream>
#include "Store.h"

Store::Store() {
    first = NULL;
    last = NULL;
    count = 0;
    total = 0;
}

Item* Store::add(Item * item) {
    Item* i;
    if(last == NULL){
        first = item;
        last = item;
        count ++;
    }else{
        i = find(item->id);
        if(i != NULL){
            i->num = i->num + item->num;
            delete item;
        }else{
            last->next = item;
            last = last->next;
            count ++;
        }
    }
}

Item* Store::find(string id) {
    Item* item = first;
    while(item != NULL){
        if(item->id == id)
            return item;
        peer = item;
        item = item->next;
    }
    return NULL;
}

void Store::list(){
    Item* item = first;
    while(item != NULL){
        item->display();
        item = item->next;
    }
}

Item* Store::drop(string id){
    Item *item = find(id);
    if(item == NULL) {
        cout << "不存在的\n";
        return NULL;
    }
    else{
        if(item == first){
            first = NULL;
            last = NULL;
        } else {
            peer->next = item->next;
        }
        return item;
    }
}

Item* Store::sell(string id){
    Item* item = find(id);
    if(item != NULL)
        return item->sold();
    return NULL;
}

void Store::print() {
    cout<<"******************************\n";
    cout<<"名称       数量*单价     合计\n";
    cout<<"******************************\n";
    Item* item = first;
    while(item != NULL){
        item->print();
        item = item->next;
    }
    cout<<"******************************\n";
    cout<<"总计：               "<<this->getTotal()<<endl;
}

double Store::getTotal(){
    total = 0;
    Item* item = first;
    while(item != NULL){
        total = total +  item->getPrice() * item->num;
        item = item->next;
    }
    return total;
}
double Store::_getTotal(){
    return total;
}
//Item* Store::sell(string id) {
//    Item* item = find(id);
//    if(item == NULL){
//        cout<<"该商品不存在";
//    }else{
//        item->sold();
//    }
//}