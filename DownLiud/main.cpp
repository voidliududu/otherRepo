#include <iostream>
//#include "include/Url.h"

#include "include/Http.h"



class Printer : public EventHandler{
public:
    Printer():EventHandler(){}
    /*
     * @override
     * */
    void onData(const string& chunk){
        cout<<chunk;
    }
    void onEnd(const string& chunk){
        cout<<chunk;
    }
     ~Printer(){
    }
};



using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
//    char user[100];
//    scanf("%s",user);
//    printf(user);
//    string testString = "http://user:pass@baidu.com/path/to/index.html?key=value&key=value";
//    testString = "http://user:pass@cn.bing.com:8080/path.html?value=key&value1=key1";
//    //testString = "http://helloworld.com";
//    //regex url("(\\w+:)//((\\w+:\\w+)@)?([\\w\\.-]*){1}(:(\\d+))?([\\w\\.-%/]*)(\\?(\\w+=\\w+&?)*)*");
//    //regex url("(\\w+:)//((\\w+:\\w+)@)?([\\w\\.-]*)(:(\\d+))?([\\w\\.-%/]*)(\\?(\\w+=\\w+&?)*)*");
//    regex url("(\\w+:)//((\\w+:\\w+)@)?([\\w\\.-]+)(:(\\d+))?([\\w\\./%]+)*(\\?*(\\w+=\\w+&?)+)*");
//    smatch res;
//    regex_search(testString,res,url);
//    //cout<<res.size()<<endl;
//    cout<<res.size();
//    for(int i = 0 ;i < res.size(); i++){
//        cout<<res[i]<<endl;
//    }
    //cout<<regex_match(testString,url);


//    //测试url模块
//    try {
//        //Url host("http://cn.bing.com:8080/path/to/resource.zip?ip=jfjal&hefe=njjshf");
//        Url host("hhhh");
//        host.dump();
//    }catch (UrlException){
//        cerr<<"Url错误";
//    }
    //Url模块测试通过


    //Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8

    try {
        Url res("http://www.baidu.com");
        string Host = "Host";
        Http http(res);
        Printer *e = new Printer();
        http.setReqHeader(Host, res.getHostName());
        http.setReqHeader("Connection", "keep-alive");
        http.setReqHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8");
        http.setEvent(e);
        http.request();
    }catch (ConnectException){
        cerr<<"conenct\n";
    }catch (SocketCreateException){
        cerr<<"socket";
    }

//    char chunk[256];
//    struct sockaddr_in serveraddr;
//    serveraddr.sin_family = AF_INET;
//    serveraddr.sin_port = htons(80);
//    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.2");
//    string header = "GET / HTTP/1.1\r\nHost : 127.0.0.2\r\n\r\n";
//    int client = socket(AF_INET,SOCK_STREAM,0);
//    //cout<<endl<<sizeof(header.c_str());
//    //cout<<header.c_str();
//    //cout<<endl<<sizeof(header.c_str());
//    connect(client,(sockaddr*)&serveraddr,sizeof(serveraddr));
//    send(client,header.c_str(),header.length(),0);
//    recv(client,chunk,sizeof(chunk)-1,0);
//    cout<<chunk;
    return 0;
}