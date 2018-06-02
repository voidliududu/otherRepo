//
// Created by liududu on 18-4-18.
//
#include <iostream>
#include <string.h>

using namespace std;

int kmpSearch(string s, string patten) {
    int plen = patten.length();
    int dfa[plen][256];
    memset(dfa,0,sizeof(int)*plen*256);
    int X = 0;
    for(int i = 0; i < plen; i++) {
        for(int c = 0; c < 256; c++) {
            dfa[i][c] = dfa[X][c];
        }
        dfa[i][patten[i]] = i + 1;
        X = dfa[X][patten[i]];
    }
    int i,j, slen = s.length();
    for(i = 0, j = 0; i < slen && j < plen; i++)
        j = dfa[j][s[i]];
    if (j == plen) return i - plen;
    else return slen;

}




int main() {
    string s = "this is a test string and you should test it";
    string patten = "test";
    cout<<kmpSearch(s,patten);
}
