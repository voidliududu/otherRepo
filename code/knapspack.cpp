//
// Created by liududu on 18-4-29.
//

#include <cstdlib>
#include <ctime>

#define max(a,b) ((a) > (b)? (a) : (b))

int odd[100][2];
int totalValue[100];
int get[100];
int Knapspack;

int matrix[100][100];

int K(int m, int n) {
    for(int i = 0; i < m; i++) {
        matrix[i][0] = 0;
    }
    for (int j = 0; j < n; j++) {
        matrix[0][j] = 0;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j < odd[i][2]) {
                matrix[i][j] = matrix[i-1][j];
            } else {
                matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - odd[i][1]] + odd[i][2]);
            }
        }
    }
}

void kanpspack_generator(int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {

    }
}


int main() {

}