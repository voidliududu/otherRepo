//
// Created by liududu on 18-5-22.
//

#ifndef ECRYPT_RC4_H
#define ECRYPT_RC4_H

#include <iostream>
#include <cstring>
using namespace std;

class Rc4{
private:
    unsigned char sbox[256];
    unsigned char k[256];
    int currenti;
    int currentj;
public:
    void setkey(unsigned char* key, int length) {
        for (int i = 0; i < 256; i++) {
            k[i] = key[i%length];
        }
    }

    void initSbox() {
        currentj = 0;
        currenti = 0;
        for (int i = 0; i < 256; i++) {
            sbox[i] = i;
        }
        int j = 0;
        unsigned char temp = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + sbox[i] + k[i]) % 256;
            temp = sbox[j];
            sbox[j] = sbox[i];
            sbox[i] = temp;
        }
    }
    unsigned char getk(void) {
        unsigned char temp = 0;
        int t = 0;
        currenti = (currenti + 1) % 256;
        currentj = (currentj + sbox[currenti]) % 256;
        temp = sbox[currenti];
        sbox[currenti] = sbox[currentj];
        sbox[currentj] = temp;
        t = (sbox[currenti] + sbox[currentj]) % 256;
        return sbox[t];
    }

    void encrypt(unsigned char *str, int length,unsigned char* result){
        for (int i = 0; i < length; i++) {
            result[i] = str[i] ^ getk();
        }
    }

    void decrypt(unsigned char* str,int length, unsigned char* result) {
        for (int i = 0; i < length; i++) {
            result[i] = str[i] ^ getk();
        }
    }


    void rc4_encrypt(unsigned char * str, int length, unsigned char * key, int keylength) {
        setkey(key,keylength);
        initSbox();
        encrypt(str,length,str);
    }

    void rc4_decrypt(unsigned char * str, int length, unsigned char * key, int keylength) {
        rc4_encrypt(str,length,key,keylength);
    }
};

#endif //ECRYPT_RC4_H
