//循环赛日程安排问题
//输入2^k,输出日程表
#include <stdio.h>
#include <malloc.h>
FILE* in = fopen("main_in.txt","r");
FILE* out = fopen("main_out.txt","w");
//void generateTable(int table[64][64], int m, int n);
void print(int table[128][128], int n);
void getTable(int table[128][128],int m, int n, int r);
int main(int argc, char const *argv[])
{
	int n = 0;
	fscanf(in,"%d",&n);
	int table[128][128];
	n = 1<<n;
	if (n > 128) {
		fprintf(out,"out of bound\n");
	}else{
		for (int i = 1; i <= n; i ++){
			table[i-1][0] = i;
		}
		getTable(table,0,0,n);
		print(table,n);
	}
	return 0;
}

//void generateTable(int table[64][64], int m, int n)
//{
//	int s = n - m + 1;
//	if (s == 2) {
//		table[m + 1][1] = table[m][0];
//		table[m][1] = table[n][0];
//		return;
//	}
//	if (s <= 1)
//		return;
//	generateTable(table, m, m + s / 2 - 1);
//	generateTable(table, m + s / 2, n);
//	for (int i = 0; i < s / 2; i ++) {
//		for (int j = 0; j < s / 2; j ++) {
//			table[m + i + s / 2][m + j + s / 2] = table[m + i][m + j];
//			table[m + i][m + j + s / 2] = table[m + s / 2 + i][m + j];
//		}
//	}
//}

void print(int table[128][128], int n)
{

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            fprintf(in,"%d ",table[i][j]);
        }
        fprintf(out,"\n");
    }
}
void cp(int table[128][128], int m, int n, int r, int x, int y) {
    for(int i = 0; i < r; i ++) {
        for (int j = 0; j < r; j++) {
            table[m+x+i][n+y+j] = table[m+i][n+j];
        }
    }
}
void getTable(int table[128][128],int m, int n, int r) {
    if (r <= 1) {
        return;
    }
    getTable(table, m, n,r / 2);
    getTable(table,m+r/2,n,r / 2);
    cp(table,m,n,r/2,r/2,r/2);
    cp(table,m+r/2,n,r/2,-r/2,r/2);
}


