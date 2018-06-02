//
// Created by liududu on 18-4-4.
//

#include <cstdio>
#include <cmath>

typedef struct point{
    double x;
    double y;
} Point;

#define INF 1e20
Point p[10000];
void quickSort(Point p[],int m,int n);
double close_pair(int l,int r);
int main(void) {
    int n;
    FILE* f = fopen("test.txt","r");
    FILE* out = fopen("out.txt","w");
    while(true)
    {
        if(feof(f))
            return 0;
        fscanf(f,"%d",&n);
        if(n==0)
            break;
        for(int i = 0; i < n; i++)
            fscanf(f,"%lf %lf",&p[i].x,&p[i].y);
        quickSort(p,0,n-1);
        fprintf(out,"%.2lf\n",close_pair(0,n-1));
    }
    return 0;
}

int partion(Point p[], int m, int n) {
    Point temp = p[m];
    int i = m,j = n;
    while(i < j) {
        Point t;
        while (i < j && p[j].x >= temp.x) j--;
        p[i] = p[j];
        while (i < j && p[i].x < temp.x) i++;
        p[j] = p[i];
    }
    p[i] = temp;
    return i;
}

void quickSort(Point p[],int m,int n) {
    if(m >= n)
        return;
    int k= 0;
    k = partion(p,m,n);
    quickSort(p,m,k-1);
    quickSort(p,k+1,n);

}

double get_distance(Point a, Point b)
{
    return sqrt((a.x - b.x)*(a.x - b.x)+(a.y - b.y)*(a.y - b.y));
}


double close_pair(int l,int r)
{
    if (l == r)
        return INF;
    if (l + 1 == r)
        return get_distance(p[l],p[r]);
    int m = (l + r) / 2;
    double dl, dr, d;
    dl = close_pair(l,m);
    dr = close_pair(m+1,r);
    d = dl<dr?dl:dr;
    Point temp[r-l];
    int j = -1;
    for(int i = l; i <=r; i++) {
        if(fabs(p[m].x - p[i].x) < d) {
            temp[++j] = p[i];
        }
    }
    quickSort(temp,0,j);
    for(int i = 0; i < j-1; i++){
        if(get_distance(temp[i],temp[i+1]) <d) {
            d = get_distance(temp[i],temp[i+1]);
        }
    }
    return d;
}



