//
// Created by liududu on 17-10-25.
//

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "city.h"
#include "LinkList.h"

/**
 * 给定城市名称，输出坐标
 * */
void findCity(LinkList<City>& list,string cityName){
    City m(cityName);
    node<City>* city = list.search(m);
    City cit = city->getData();
    cout<<cit;
}

/**
 * 获取两坐标的距离
 * */
double getDistance(float x1, float y1,float x2,float y2){
    float X = abs(x1 - x2);
    float Y = abs(y1 -y2);
    return sqrt(X*X + Y*Y);
}
/**
 * 给定坐标，返回指定距离内的城市
 * */
void searchByXY(LinkList<City>& list,float x,float y,double d){
    int length = list.length();
    LinkList<City> result;
    node<City> * city ;
    City m;
    for(int i = 1;i <= length; i++){
        city = list.searchById(i);
        m = city->getData();
        if(getDistance(m.getX(),m.getY(),x,y) <= d)
            result.append(m);
    }
    result.dump();
}

string getCommand(){
    string command;
    cout<<"city>>";
    cin>>command;
    return command;
}
int main(){
    LinkList<City> cityList;
    float x,y;
    double d;
    string command = getCommand();
    string cityname;
    while(true){
        if(command == "findCityByName"){
            cout<<"请输入城市名";
            cin>>cityname;
            findCity(cityList,cityname);
        }else if(command == "getNearByCitys"){
            cout<<"请输入坐标x\n";
            cin>>x;
            cout<<"请输入坐标y\n";
            cin>>y;
            cout<<"请输入距离\n";
            cin>>d;
            searchByXY(cityList,x,y,d);
        }else if(command == "exit"){
            exit(0);
        }
        command = getCommand();
    }
}