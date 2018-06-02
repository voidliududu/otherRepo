#include <iostream>
#include <cstdio>
#include "Aes.h"

void readHex(char* buffer,int length) {
    for (int i = 0; i < length; i++) {
        scanf("%02X",&buffer[i]);
    }
}


int main() {
//    std::cout << "Hello, World!" << std::endl;

    Aes a;
    int input;
    while(1) {
        cout<<"输入操作：加密（1），解密（2）,退出（0）"<<endl;
        char buffer[16];
        char key[16];
        cin>>input;
        if (input == 1) {
            cout << "输入文本" << endl;
            readHex(buffer, 16);
            cout << "输入密钥" << endl;
            readHex(key, 16);
            a.aes_encrypt(buffer, key);
            cout << "密文" << endl;
            a.print();
        }else if(input == 2) {
            cout << "输入密文"<<endl;
            readHex(buffer,16);
            cout<<"输入密钥"<<endl;
            readHex(key,16);
            a.aes_decrypt(buffer,key);
            cout<<"名文"<<endl;
            a.print();

        }else{
            break;
        }
    }
//    a.initState("abcdefghijklmnop");
//    a.initState("\x19\xa0\x9a\xe9\x3d\xf4\xc6\xf8\xe3\xe2\x8d\x48\xbe\x2b\x2a\x08");

//    a.dump();
//    a.subBytes();
//    a.dump();
//    a.shiftRows();
//    a.dump();
//    a.mixColomns();
//    a.dump();
//    a.test();
//    a.dump();
//
//    a.readKey("\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c");
//    a.makeRoundKey();
//    a.encrypt();
////    for(int i = 0 ; i < 11; i++) {
////        a.dumpkey(i);
////    }
//    a.dump();
//    a.decrypt();
//    a.dump();
    return 0;
}