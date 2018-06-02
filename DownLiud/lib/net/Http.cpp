//
// Created by liududu on 17-9-30.
//

/*
 * 这是一个坑爹的库,我费尽九牛二虎之力才实现了基本功能
 * 其中经历的摸打滚爬足够我写好几篇文章装逼了。
 * mmp，第216行的傻逼错误浪费了我两天时间
 *
 * */



#include <sstream>

#include <unistd.h>

#include "../../include/Http.h"

Http::Http() {
    req = map<string,string>();
    res = map<string,string>();
    requestBody = "";
    method = "GET";
    host = "";
    port = 80;
    path = "/";
}

Http::Http(Url &url) throw(ProtocolException) {
    if(url.getProtocol() != "http:"){
        throw ProtocolException();
    }
    this->req = map<string,string>();
    this->res = map<string,string>();
    this->host = url.getIp();
    this->port = (url.getPort() == 0)?80:url.getPort();
    this->path = url.getPath() + url.getQueryString();
    this->requestBody = "";
    this->method = "GET";
}
/*
 * 获取请求头
 * */
map<string,string> Http::getReqHeader() {
    return this->req;
}
/*
 * 获取响应头
 * */
map<string,string> Http::getResHeader() {
    return this->res;
}
/*
 * 设置请求头
 * */
bool Http::setReqHeader(string key, string value) {
    this->req[key] = value;
    return true;
}
/*
 * 设置请求方法
 * */
bool Http::setMethod(string &method) {
    this->method = method;
    return true;
}

bool Http::setPath(string &path) {
    this->path = path;
    return true;
}
/*
 * 设置请求体
 * */
bool Http::setBody(string &queryString) {
    this->requestBody = queryString;
    return true;
}
/*
 * 设置通讯端口
 * */
bool Http::setPort(int port) {
    this->port = port;
    return true;
}
/*
 * 设置远程主机
 * */
bool Http::setHost(string &host) {
    this->host = host;
    return true;
}

bool Http::setEvent(HttpEventHandler *e) {
    this->e = e;
}

/*
 * 根据req生成请求头
 * */
string Http::makeReqHeader() {
    string firstline = this->method
                       + " "
                       + this->path
                       + " "
                       + "HTTP/1.1" + "\r\n";
    string requestHeader;
    map<string,string>::iterator header = this->req.begin();
    while(header != req.end()){
        requestHeader.append(header->first + " : " + header->second + "\r\n");
        header++;
    }
    return firstline + requestHeader + "\r\n";
}
stringstream Http::_getStatus(int fd) {
    char buffer[MAX_CHUNK];
    int status;
    ssize_t realSize;
    string version;
    realSize = recv(fd,buffer,sizeof(buffer)-1,0);
    if(sizeof(buffer) - 1 != realSize){
        if(realSize < 0)
            throw ConnectException();
        else
            buffer[realSize] = '\0';
    }
    stringstream response;
    response<<buffer;
    response.getline(buffer,sizeof(buffer));
    stringstream head;
    head<<buffer;
    head>>version>>status;
    this->status = status;
    return response;
}

stringstream Http::_getResHeader(int fd) {
    char buffer[MAX_CHUNK];
    int status;
    ssize_t realSize;
    string version;
    realSize = recv(fd,buffer,sizeof(buffer)-1,0);
    if(sizeof(buffer) - 1 != realSize){
        if(realSize < 0)
            throw ConnectException();
        else
            buffer[realSize] = '\0';
    }
    stringstream response;
    response<<buffer;
    response.getline(buffer,sizeof(buffer));
    stringstream head;
    head<<buffer;
    head>>version>>status;
    this->status = status;
    string line;
    unsigned long index;
    while(line != "\r"){
        if(!response.eof()) {
            response.getline(buffer, sizeof(buffer));
            line = string(buffer);
            index = line.find(':');
            this->res[line.substr(0,index - 1)] = line.substr(index+1);
        }else{
            realSize = recv(fd,buffer,sizeof(buffer)-1,0);
            if(sizeof(buffer) - 1 != realSize){
                if(realSize < 0)
                    throw ConnectException();
                else
                buffer[realSize] = '\0';
            }
            response.clear();
            response<<buffer;
        }
    }
    return response;
}
/*
 * 获取响应状态码
 * */
int Http::getStatus() {
    return this->status;
}

bool Http::onData() {

}

bool Http::onEnd() {

}
/*
 * TODO stringstream的处理
 * */
bool Http::request() {
    string Header = this->makeReqHeader() + this->requestBody;
    //cout<<Header;
    char chunk[MAX_CHUNK];
    ssize_t realSize;             //接收到数据的真实容量
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons((uint16_t)(this->port));
    //server_addr.sin_port = htons(80);
    //cout<<this->host;
    server_addr.sin_addr.s_addr = inet_addr(this->host.c_str());
    //server_addr.sin_addr.s_addr = inet_addr("127.0.0.2");
    //创建套接字
    int client = socket(AF_INET,SOCK_STREAM,0);
    if(client < 0)
        throw SocketCreateException();
    //连接服务器
    if(connect(client,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
        throw ConnectException();
    //发送http请求头
    if(send(client,Header.c_str(),Header.length(),0) <= 0){
        cout<<"fasongshibai";
    }
//    recv(client,chunk, sizeof(chunk),0);
//    cout<<chunk;
    //获取响应头并处理
    //stringstream response = this->_getStatus(client);
    stringstream response = this->_getResHeader(client);
    //处理除响应头之外的数据
    response.getline(chunk,sizeof(chunk),ios::end);
    e->onData(string(chunk));
    //接收数据块并触发相应事件
    do{
        realSize = recv(client,chunk,sizeof(chunk) - 1,0);
        if(realSize != sizeof(chunk) -1){
            if(realSize < 0)
                throw ConnectException();
            if(realSize == 0)
                break;
            chunk[realSize] = '\0';
            e->onEnd(string(chunk));
        }else{
            chunk[MAX_CHUNK - 1] = '\0';
            e->onData(string(chunk));
        }
    }while(realSize == sizeof(chunk) - 1);
    //关闭套接字
    close(client);
}
