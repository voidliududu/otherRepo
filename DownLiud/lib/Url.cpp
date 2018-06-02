//
// Created by liududu on 17-9-30.
//

#include "../include/Url.h"

void Url::init(){
    this->href = "";
    this->protocol = "";
    this->auth = "";
    this->host = "";
    this->port = -1;
    this->path = "";
    this->queryString = "";
    this->anchor = "";
    this->ip = "";
}
Url::Url() {
   init();
}

/*
 * @param url   url字符串
 * @throw UrlException DnsException
 * */
Url::Url(const string& url) throw(UrlException) {
    //url  http://user:pass@www.example.com/path/to/location?key=value&key=value#anchor
    regex url_reg("(\\w+:)//((\\w+:\\w+)@)?([\\w\\.-]+)(:(\\d+))?([\\w\\./%]+)*(\\?*(\\w+=\\w+&?)+)*");
    smatch result;
    regex_search(url,result,url_reg);
    if(result.empty()){
        throw  UrlException();
    }else{
        this->href = result[0];
        this->protocol = result[1];
        this->auth = result[3];
        this->host = result[4];
        this->port = atoi(result[6].str().c_str());
        this->path = result[7];
        this->queryString = result[8];
        this->anchor = "";
    }
}

Url::Url(const Url& url){
    this->href = url.href;
    this->protocol = url.protocol;
    this->auth = url.auth;
    this->host = url.host;
    this->port = url.port;
    this->path = url.path;
    this->queryString = url.queryString;
    this->anchor = url.anchor;
    this->ip = url.ip;
}

/*
 * 获取ip地址字符串
 * todo 检查host是否是ip
 * */
string Url::getIp() throw(DnsException) {
    if(ip.empty()) {
        char ipaddr[30];
        hostent *hostName = gethostbyname(this->host.c_str());
        if (hostName == NULL) {
            throw DnsException();
        }
        inet_ntop(hostName->h_addrtype, *(hostName->h_addr_list), ipaddr, sizeof(ipaddr));
        this->ip = string(ipaddr);
        return this->ip;
    }else{
        return this->ip;
    }
}

string Url::getHostName() {
    return this->host;
}

string Url::getHref() {
    return this->href;
}

string Url::getProtocol() {
    return this->protocol;
}
/*
 * @return pair<string,string>  first=>username  second=>password
 * */
pair<string,string> Url::getAuth() {
    pair<string,string> m;
    if(this->auth.empty()){
        m.first = "anfha";
        m.second = "downliud";
        return m;
    }
    unsigned long index = this->auth.find(':');
    m.first = this->auth.substr(0,index-1);
    m.second = this->auth.substr(index+1);
    return m;
}

int Url::getPort() {
    return this->port;
}

string Url::getPath() {
    string a = "/";
    return (this->path).empty()?a:this->path;
}

string Url::getQueryString() {
    //string s = this->queryString.length() <= 1?"":this->queryString.substr(1);
    string s = this->queryString;
    return s;
}

/*
 * 调试专用
 * */
void Url::dump() {
    cout<<"href"<<"=>"<<this->getHref()<<endl;
    cout<<"protocol"<<"=>"<<this->getProtocol()<<endl;
    cout<<"host"<<"=>"<<this->getHostName()<<endl;
    cout<<"port"<<"=>"<<this->getPort()<<endl;
    cout<<"path"<<"=>"<<this->getPath()<<endl;
    cout<<"querystring"<<"=>"<<this->getQueryString()<<endl;
    cout<<"ip"<<"=>"<<this->getIp()<<endl;
    cout<<getAuth().first<<getAuth().second<<endl;
}