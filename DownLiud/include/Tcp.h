//
// Created by liududu on 17-11-17.
//

#ifndef DOWNLIUD_TCP_H
#define DOWNLIUD_TCP_H


#include "Connect.h"

class Tcp {
private:
    int fd;
public:
    /**
     * 由Connect创建tcp套接字
     * @param c  Connect对象
     * */
    Tcp(Connect c);
    /**
     * 从tcp套接字中读入信息
     * @param buffer 字符缓冲区指针
     * @param size  字符缓冲区大小
     * */
    bool tcpRead(char* buffer,int size);
    /**
     * 向tcp套接字中写入信息
     * @param buffer 字符缓冲区指针
     * @param size  字符缓冲区大小
     * */
    bool tcpWrite(char* buffer,int size);
    /**
     * 关闭套接字，释放资源
     * */
    ~Tcp();
};


#endif //DOWNLIUD_TCP_H
