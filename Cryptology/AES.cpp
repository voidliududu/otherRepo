#include <iostream>
#include "AES.h"
#include <cstdio>

//11223344556677889900AABBCCDDEEFF
//13579BDF02468ACE1234567890ABCDEF
using namespace std;
int main()
{
    unsigned char strtext[16];
    for(int i=0;i<16;i++)
    {
        scanf("%02X",&strtext[i]);
    }
    unsigned char strkey1[16];

    for(int i=0;i<16;i++)
    {
        scanf("%02X",&strkey1[i]);
    }
    int array[4][4];
    int key[4][4];
    inputToArray(strtext,array);
    inputToArray(strkey1,key);
    writeW(key);
    for(int i=0;i<10;i++)
    {
        keyExtend(key);
        writeW(key);
    }
    AESadd(array);
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            printf("%x",array[j][i]);
        }
        cout<<endl;
}