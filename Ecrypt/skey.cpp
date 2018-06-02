//
// Created by liududu on 18-5-22.
//

#include "md5.h"
#include <iostream>
#include <fstream>

using namespace std;

#define chain_length 100

class Skey{
private:
    string currentHash;
    string beginHash;
public:
    //生成hash链，写入文件
    void generateHashChain(string seed,string path) {
        ofstream file(path);
        string hashchain[chain_length];
        MD5* md5 = NULL;
        md5 = new MD5(seed);
        beginHash = md5->md5();
        hashchain[0] = beginHash;
//        file<<beginHash<<endl;
        string hash = beginHash;
        for (int i = 1; i < chain_length - 1; i++) {
            if (md5 != NULL) {
                delete md5;
            }
            md5 = new MD5(hash);
            hash = md5->md5();
            hashchain[i] = hash;
//            file<<hash<<endl;
        }
        if (md5 != NULL) {
            delete md5;
        }

        for(int i = chain_length - 1; i >=0; i--) {
            file<<hashchain[i]<<endl;
        }
        md5 = new MD5(hash);
        currentHash = md5->md5();
        delete md5;
        file.close();
    }

    //验证口令
    bool verifyToken(string password) {
        if(currentHash == beginHash) {
            return false;
        }
        MD5 md5(password);
        if (md5.md5() == currentHash) {
            currentHash = password;
            return true;
        }else{
            return false;
        }
    }
};


int main() {
   Skey skey;
   string seed;
   string path;
   string password;
   cout<<"input the seed"<<endl;
   cin>>seed;
   cout<<"input the filepath" <<endl;
   cin>>path;
   skey.generateHashChain(seed,path);
   while(1) {
       cout<<"please input the password"<<endl;
       cin>>password;
       if (skey.verifyToken(password)) {
           cout<<"password is true"<<endl;
       }else{
           cout<<"password is false"<<endl;
       }
   }
}