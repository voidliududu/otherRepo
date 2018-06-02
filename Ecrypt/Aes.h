//
// Created by liududu on 18-5-21.
//

#ifndef ECRYPT_AES_H
#define ECRYPT_AES_H

#include <iostream>
#include <cstring>

using namespace std;

#define chunk_size 16
#define size 4

class Aes {
public:
    //储存状态
    unsigned char state[4][4];
    //储存轮密钥
    unsigned char roundkey[11][4][4];
    //字节替换
    void subBytes(void);
    //行移位
    void shiftRows(void);
    //列混合
    void mixColomns(void);
    //轮密钥加
    void addRoundKey(int i);

    static int sbox[256];
    static unsigned char mbox[4][4];
    static int rsbox[256];
    static unsigned char rmbox[4][4];
    static char RC[10];

    Aes(char *state);

    Aes();

    void initState(char *ch);
    void generateKey(int i);
    void readKey(char *ch);
    void T(unsigned char * t);
    void makeRoundKey(void);

    char* encrypt(void);
    char* decrypt(void);

    char get(int x, int y);
    void test();
    void dump();
    void dumpkey(int i);
    void rshiftRows();
    void rsubBytes(void);
    void rmixColomns(void);
    void aes_encrypt(char * text, char *key);
    void aes_decrypt(char* text, char *key);
    void print();

    unsigned char XTIME(unsigned char x)
    {
        return ((x << 1) ^ ((x & 0x80) ? 0x1b : 0x00));
    }
    unsigned char multiply(unsigned char a, unsigned char b)
    {
        unsigned char temp[8] = { a };
        unsigned char tempmultiply = 0x00;
        int i = 0;
        for (i = 1; i < 8; i++)
        {
            temp[i] = XTIME(temp[i - 1]);
        }
        tempmultiply = (b & 0x01) * a;
        for (i = 1; i <= 7; i++)
        {
            tempmultiply ^= (((b >> i) & 0x01) * temp[i]);
        }
        return tempmultiply;
    }

};

Aes::Aes() {
    memset(state, 0, 16);
}

void Aes::initState(char *ch) {
    memcpy(state, ch, 16);
    unsigned char m = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i; j++) {
            m = state[i][j];
            state[i][j] = state[j][i];
            state[j][i] = m;
        }
    }
}

int Aes::sbox[256] = {
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

int Aes::rsbox[256] = {
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};
unsigned char Aes::mbox[4][4] = {
        '\02','\03','\01','\01',
        '\01','\02','\03','\01',
        '\01','\01','\02','\03',
        '\03','\01','\01','\02'
};

unsigned char Aes::rmbox[4][4] = {
        '\x0e','\x0b','\x0d','\x09',
        '\x09','\x0e','\x0b','\x0d',
        '\x0d','\x09','\x0e','\x0b',
        '\x0b','\x0d','\x09','\x0e'
};
char Aes::RC[10] = {'\x01','\x02','\x04','\x08','\x10','\x20','\x40','\x80','\x1b','\x36'};

void Aes::subBytes() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            state[i][j] = (unsigned char) sbox[state[i][j]];
        }
    }
}

void Aes::rsubBytes() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            state[i][j] = (unsigned char) rsbox[state[i][j]];
        }
    }
}
void Aes::shiftRows() {
    unsigned char temp = 0;
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;

}

void Aes::rshiftRows() {
    unsigned char temp = 0;
    temp = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = temp;

    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    temp = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp;
}

void Aes::mixColomns() {
    unsigned char result[4][4];
    memset(result,0,16);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
//                result[i][j] ^= (mbox[i][k] * state[k][j])^'\x1b';
                result[i][j] ^= multiply(mbox[i][k] , state[k][j]);
            }
        }
    }
    memcpy(state,result,16);
}

void Aes::rmixColomns() {
    unsigned char result[4][4];
    memset(result,0,16);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
//                result[i][j] ^= (mbox[i][k] * state[k][j])^'\x1b';
                result[i][j] ^= multiply(rmbox[i][k] , state[k][j]);
            }
        }
    }
    memcpy(state,result,16);
}

void Aes::addRoundKey(int i) {
    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 4; n++) {
            state[m][n] = state[m][n]^roundkey[i][n][m];
        }
    }
}

void Aes::readKey(char *ch) {
  memcpy(roundkey[0],ch,16);
}

void Aes::makeRoundKey() {
    for(int i = 1; i < 11; i ++) {
        generateKey(i);
    }
}

void Aes::generateKey(int i) {
    unsigned char left[4];
    memcpy(left, roundkey[i-1][0],4);
    unsigned char right[4];
    memcpy(right, roundkey[i-1][3],4);
    T(right);
    roundkey[i][0][0] = left[0]^right[0]^RC[i-1];
    roundkey[i][0][1] = left[1]^right[1]^'\x00';
    roundkey[i][0][2] = left[2]^right[2]^'\x00';
    roundkey[i][0][3] = left[3]^right[3]^'\x00';

    for(int r = 1; r < 4; r++) {
        for (int m = 0; m < 4; m++) {
            roundkey[i][r][m] = roundkey[i][r - 1][m]^roundkey[i-1][r][m];
        }
    }
}

void Aes::T(unsigned char * t) {

    unsigned char temp = t[0];
    t[0] = t[1];
    t[1] = t[2];
    t[2] = t[3];
    t[3] = temp;

    for (int i = 0; i < 4; i++) {
        t[i] = (unsigned char)sbox[t[i]];
    }
}


char* Aes::encrypt() {
    addRoundKey(0);
    dump();
    for(int i = 1; i < 10; i++) {
        subBytes();
        shiftRows();
        mixColomns();
        addRoundKey(i);
        dump();
    }
    subBytes();
    shiftRows();
    addRoundKey(10);
    dump();
}

char * Aes::decrypt() {
    addRoundKey(10);
    rshiftRows();
    rsubBytes();
    for (int i = 9; i > 0; i--) {
        addRoundKey(i);
        rmixColomns();
        rshiftRows();
        rsubBytes();
    }
    addRoundKey(0);
}


void Aes::aes_encrypt(char* text,char* key) {
    initState(text);
    readKey(key);
    makeRoundKey();
    encrypt();
}

void Aes::aes_decrypt(char *text, char *key) {
    initState(text);
    readKey(key);
    makeRoundKey();
    decrypt();
}

void Aes::print() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%02x",state[j][i]);
        }
    }
    printf("\n");
}


void Aes::test() {
    unsigned char m = 0;
//    m = '\x02' * '\xd4' + '\x03' * '\xbf' + '\x01' * '\x5d' + '\x01' * '\x30';
    m = ('\x02' * '\xd4') % '\x1b';
    printf("\n%x", m);
    m = ('\x04' * '\xd4') % '\x1b';
    printf("\n%x", m);
}

char Aes::get(int x, int y) {
    return state[x][y];
}

void Aes::dump() {
    printf("\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%02x ", (int) state[i][j]);
        }
        printf("\n");
    }
}

void Aes::dumpkey(int i) {
    printf("\n");
    for(int m = 0; m < 4; m++) {
        for(int n = 0; n < 4; n++) {
            printf("%02x ", roundkey[i][m][n]);
        }
        printf("\n");
    }
}

#endif //ECRYPT_AES_H
