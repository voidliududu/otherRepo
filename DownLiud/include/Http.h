//
// Created by liududu on 17-9-30.
//

#ifndef DOWNLIUD_HTTP_H
#define DOWNLIUD_HTTP_H

#include <map>
#include <string>

#include "exception.h"
#include "Url.h"

//设置数据块的最大容量
#define MAX_CHUNK 256


using namespace std;

class EventHandler;

class Http {
private:
    string makeReqHeader();
    stringstream _getStatus(int fd);
    stringstream _getResHeader(int);
protected:
    map<string,string> req;
    map<string,string> res;
    string requestBody;
    string  method;
    string host;
    int port;
    string path;
    HttpEventHandler* e;
    int status;
public:
    Http();
    Http(Url&) throw(ProtocolException) ;
    map<string,string> getReqHeader();
    map<string,string> getResHeader();
    bool setReqHeader(string,string);
    bool setMethod(string&);
    bool setPath(string&);
    bool setBody(string&);
    bool setPort(int);
    bool setHost(string&);
    bool setEvent(HttpEventHandler* e);
    int getStatus();
    bool onData();
    bool onEnd();
    bool request();
};

class HttpEventHandler{
public:
    HttpEventHandler() {}
    virtual void onData(const string& chunk) = 0;
    virtual void onEnd(const string& chunk) = 0;
    ~EventHandler() {}
};

#endif //DOWNLIUD_HTTP_H
