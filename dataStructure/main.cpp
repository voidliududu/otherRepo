#include "Graph/Graph.h"

using namespace std;
int main() {
    Graph g(10,25);
    //g.setChar(0,3,"█");
    int data[] = {1,2,3,4,5,6,7};
    g.drawData(data,7);
    g.flush();
    return 0;
}





























/* std::cout << "Hello, World!" << std::endl;
    LinkList<int>* l = new LinkList<int>();
    l->insert(1,3);
    l->drop(1);
    cout<<l->find(1,4);
    node<int>* t = l->search(2);
    t->setData(5);
    l->dump();*/
//    LinkList<City> cityList;
//    cityList.drop(1);
//    cityList.dump();
//    City city;
//    cin>>city;
//    City city2;
//    cin>>city2;
//    cout<<(city == city2);

//    City m("henan");
//    LinkList<City> list;
//    node<City>* t = list.search(m);
//    City& tt = t->getData();
//    cout<<tt;
//    list.dump();
  //  LinkList<int> list;
    //list.append(5);
    //list.dump();
//    LinkList<int> list;
//    node<int>* t = list.search(9);
//    int& a = t->getData();
//    a = 5;
//    list.dump();