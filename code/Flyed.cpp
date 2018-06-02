//
// Created by liududu on 18-5-30.
//

#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdio>

#define MaxVetex  100
#define Inf 1e8

int graph[MaxVetex][MaxVetex];

int result[MaxVetex][MaxVetex];


void graph_generator(int m) {
    srand(time(NULL));
    for (int i = 0; i < m; i ++) {
        for(int j = 0; j < m; j++) {
            graph[i][j] = rand() % 10 + 1;
        }
    }

    for (int i = 0; i < m; i++) {
        graph[i][i] = Inf;
    }
}

void print_graph(int m) {
    printf("原始图\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d ",graph[i][j] >= Inf ? -1: graph[i][j]);
        }
        printf("\n");
    }
    printf("计算结果\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d ",result[i][j]);
        }
        printf("\n");
    }
}

void floyed(int n) {
    int dist = Inf;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
//            printf("%d ",result[i][j]);
            result[i][j] = graph[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int p = 0; p < n; p++) {
            for (int q = 0; q < n; q++) {
                dist =  result[p][i] + result[i][q];
                result[p][q] = result[p][q] > dist ? dist: result[p][q];
            }
        }
    }
}



int main() {
    graph_generator(3);
    floyed(3);
    print_graph(3);
    return 0;
}
