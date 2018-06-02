//
// Created by liududu on 17-9-30.
//

#ifndef DOWNLIUD_URL_H
#define DOWNLIUD_URL_H

#include <string>
#include <regex>
#include <map>
#include <iostream>

#include <netdb.h>
#include <arpa/inet.h>

#include "exception.h"
using namespace std;
/*
 * url处理类，同时实现dns解析
 *
 * */

class Url {
protected:
    string href;            //原始url
    string protocol;        //协议
    string auth;            //用户
    string host;            //主机ip
    int    port;            //端口
    string path;            //路径
    string queryString;     //查询字符串
    string anchor;          //锚点
    string ip;
public:
    /**
     * 创建空url
     * */
    Url();
    /**
     * 由url字符串创建url对象
     * @param const string
     * @throw UrlException
     * */
    explicit Url(const string &) throw(UrlException) ;
    /**
     * 拷贝构造函数
     * */
    Url(const Url&);
    /**
     * 初始化url对象
     * */
    void init();
    /**
     * 获取原始url
     * @return string
     * */
    string getHref();
    /**
     * 获取协议类型
     *
     * */
    string getProtocol();
    /**
     * 获取认证信息
     * */
    pair<string,string> getAuth();
    /**
     * 获取主机名
     * */
    string getHostName();
    /**
     * 获取端口号
     * */
    int getPort();
    /**
     * 获取路径
     * */
    string getPath();
    /**
     * 获取querystring
     * */
    string getQueryString();
    /**
     * 由域名获取ip
     * */
    string getIp() throw(DnsException) ;
    void dump();
};


#endif //DOWNLIUD_URL_H
