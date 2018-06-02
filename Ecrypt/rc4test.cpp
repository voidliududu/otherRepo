//
// Created by liududu on 18-5-22.
//

#include "rc4.h"

void printString(unsigned char* t, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x ",t[i]);
    }
    printf("\n");
}

void readHex(unsigned char* buffer,int length) {
    for (int i = 0; i < length; i++) {
        scanf("%02X",&buffer[i]);
    }
}

int main(void) {
    unsigned char key[256];
    unsigned char text[1024];
    int keylength, length;

    cout<<"请输入密钥长度"<<endl;
    cin>>keylength;
    cout<<"请输入密钥"<<endl;
    readHex(key,keylength);
    cout<<"请输入文本长度"<<endl;
    cin>>length;
    cout<<"请输入文本"<<endl;
    readHex(text,length);
    cout<<"输入的文本"<<endl;
    printString(text,length);
    cout<<"加密结果"<<endl;
    Rc4 rc4;
    rc4.rc4_encrypt(text,length,key,keylength);
    printString(text,length);
    rc4.rc4_decrypt(text,length,key,keylength);
    cout<<"解密结果"<<endl;
    printString(text,length);
}
