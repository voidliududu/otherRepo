//
// Created by liududu on 17-11-27.
//

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H


#include <cstring>
#include <cstdio>

class Graph {
    char* buffer;
    int sizeX;
    int sizeY;
    char* color;
public:
    Graph(int height, int width){
        sizeX = width;
        sizeY = height;
        buffer = new char[height*(width + 1)+1];
        memset(buffer,int(' '),(size_t)height*(width + 1));
        for(int i = 0; i < height; i++)
            *(buffer + (width+1)*i + width) = '\n';
        *(buffer+(width+1)*(height)) = '\0';
    }

    void flush(){
        printf("%s",buffer);
    }

    void setChar(int x, int y ,char* ch){
        char* temp = buffer + (sizeX+1)*y + x;
        while(*ch != '\0'){
            *temp = *ch;
            temp ++;
            ch ++;
        }
    }
    void drawData(int data[],int n){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < data[i]; j++)
            setChar(3*j,i,"█");
        }
    }

    char* printRect(int x){
        fflush(stdout);
        char * str = new char[x*2 + 1];
        memset(str,'█',(size_t)x*2);
        str[x*2] = '\0';
        return str;
    }

};


#endif //DATASTRUCTURE_GRAPH_H
