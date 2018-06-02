//
// Created by liududu on 17-10-24.
//
#define CITY
#include <iostream>
using namespace std;
class City{
    friend istream& operator >>(istream& in,City& city);
    friend ostream&operator <<(ostream& out,City& city);
private:
    string name;
    float x;
    float y;
public:
    /**
     * 默认构造函数
     * */
    City(){
        name = "0";
        x = 0;
        y = 0;
    }
    City(string name){
        this->name = name;
        x = 0;
        y = 0;
    }
    /**
     * 获取城市名
     * */
    string getName(){
        return name;
    }
    /**
     * 获取x坐标
     * */
    float getX(){
        return x;
    }
    /**
     * 获取y
     * */
    float getY(){
        return y;
    }
    /**
     * 根据城市名判断城市是否相同
     * */
    bool operator == (const City& city){
        return this->name == city.name;
    }
    bool operator != (const City& city){
        return this->name != city.name;
    }
    /**
     * 重载流操作符实现城市信息的输入与输出
     * */

};
istream& operator >>(istream& in,City& city){
    cout<<"=请输入城市名称=>"<<endl;
    in>>city.name;
    cout<<"=请输入x=>"<<endl;
    in>>city.x;
    cout<<"=请输入y=>"<<endl;
    in>>city.y;
}
ostream&operator <<(ostream& out,City& city){
    out<<"城市名："<<city.name<<endl;
    out<<"x:"<<city.x<<endl;
    out<<"y:"<<city.y<<endl;
}

//int main(){
//    LinkList<City> cityList;
//    /*City t;
//    cin>>t;
//    cout<<t;*/
//}
