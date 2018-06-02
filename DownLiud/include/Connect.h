//
// Created by liududu on 17-11-17.
//

#ifndef DOWNLIUD_CONNECT_H
#define DOWNLIUD_CONNECT_H

#define PROTOCOL_HTTP 1
#define PROTOCOL_FTP 2
#define DEFAULT_PROTOCOL PROTOCOL_HTTP

#include <string>
using namespace std;
class Connect {
protected:
    string protocol;        //协议
    string auth;            //用户
    string host;            //主机ip
    int    port;            //端口
    string path;            //路径
    string queryString;     //查询字符串
    string ip;
    Connect* next;
public:
    /**
     * 用url得到connect对象
     * */
    Connect(string url);
    /**
     * 将Connect对象转化为url
     */
    string toUrl();
    /**
     * 断开连接
     * */
    virtual void disconnect();
    /**
     * 初始化连接
     * */
    virtual void connect();
    /**
     * 执行操作
     * */
    virtual void exec();
};


#endif //DOWNLIUD_CONNECT_H
