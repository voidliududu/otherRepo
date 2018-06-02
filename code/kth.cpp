//
// Created by liududu on 18-4-4.
//


//问题 找不到返回什么

#include <cstdio>
#include <cstdlib>
#include <ctime>

void print_arr(int arr[], int m, int n) {
    for(int i = m; i < n; i++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void quickSort(int array[], int m, int n) {
    if(m >= n)
        return;
    int temp = array[m];
    int i = m , j = n;
    while(i<j) {
        while(temp<=array[j] && i < j) j--;
        array[i] = array[j];
        while(temp>array[i] && i <j) i++;
        array[j] = array[i];
    }
    array[i] = temp;
    quickSort(array, m,i-1);
    quickSort(array,i+1,n);
}

//从n个数中找到第k大的数
int find(int array[], int n, int k) {
    printf("n=%d\n",n);
    printf("k=%d\n",k);
    if(n <= 75){
        quickSort(array,0,n-1);
        return array[k-1];
    }
    int length = n / 5;
    int* middle_set = (int *)malloc(sizeof(int)*length);
    for (int i = 0; i < length; i ++) {
//       for(int j = 0; j < 4; j++) {
//           if (array[i*5 + j] > array[i*5 + j + 1])
//               middle_set[i] = array[i*5 + j];
//       }
        quickSort(array,5*i,5*i+4);
        middle_set[i] = array[5*i+2];
    }
    int middle = (length) / 2 + (length ) % 2;
    int m = find(middle_set,length,middle);
    printf("m=%d\n",m);
    if (middle + 1 == k)
        return m;
    int* s1 = (int *)malloc(sizeof(int)*n);
    int* s2 = (int *)malloc(sizeof(int)*n);
    int p = 0, q = 0;
    for(int i = 0; i < n; i++) {
        if(array[i] < m) {
            s1[p++] = array[i];
            continue;
        }
        if (array[i] > m) {
            s2[q++] = array[i];
        }
    }
    printf("p=%d\n",p);
    printf("q=%d\n",q);

    printf("s1=");
    print_arr(s1,0,p);
    printf("s2=");
    print_arr(s2,0,q);
    if (p > k)
        m =find(s1,p,k);
    else
        m = find(s2,q,k-p-1);
    free(middle_set);
    free(s1);
    free(s2);
    return m;
}




int main(void) {
    int array[10000];
    for (int i = 0; i < 10000; i++) {
        array[i] = i;
    }
    srand(time(NULL));
    int m,n,t;
    for(int i = 0; i < 5000; i++) {
        m = rand() % 10000;
        n = rand() % 10000;
        t = array[m];
        array[m] = array[n];
        array[n] = t;
    }
    printf("%d",find(array,10000,567));
}



















//#include <iostream>
//
//using namespace std;
//
//int KthNumOfList(int List[],int len,int k);
//static int Compare(const void *p1, const void *p2);
//void Mid(int a[], int i, int p[]);
//void Swap(int & a, int & b);
//
//int main()
//{
//    int a[8] = {10,20,30,40,5,6,7,8};
//    int n = KthNumOfList(a, 8, 2);
//    cout << n << "\n";;
//
//    getchar();
//    return 0;
//}
//
//int KthNumOfList(int List[], int len, int k)
//{
//    const int least = 64; //设置一个最小长度least
//    if (len <= least)
//    {
//        qsort(List, len, sizeof(int), Compare); //对数组按递增排序
//        return List[k-1];
//    }
//
//    int *p = new int[3*len/4];
//    int lenp = len/5; //把元素划分为lenp = len/5 组, 每组5个元素,不足5个元素的那组先不予考虑.
//    for (int i=0; i<lenp; i++)
//    {
//        Mid(List, i, p); //取每组的中值元素,构成一个长度为lenp的数组p[].
//    }
//
//    int m = KthNumOfList(p, lenp, lenp/2 + lenp%2);//对数组p[]递归地执行本算法,得到其中值元素m.
//
//    int *q = new int[3*len/4];
//    int *r = new int[3*len/4];
//    int lenq = 0;
//    int lenr = 0;
//    lenp = 0;
//    //把原数组List[]划分成p,q,r三组,使得小于m的元素存放在p[],等于m的元素存放在q[],大于m的元素存放在r[].
//    for (int i=0; i<len; i++)
//    {
//        if (List[i] < m)
//            p[lenp++] = List[i];
//        else if (List[i] == m)
//            q[lenq++] = List[i];
//        else
//            r[lenr++] = List[i];
//    }
//
//    if (lenp > k)
//    {
//        m = KthNumOfList(p, lenp, k);
//    }
//    else if(lenp + lenq < k)
//    {
//        m = KthNumOfList(r, lenr, k-lenp-lenq);
//    }
//    //很明显,此时的m就是所要选择的元素, 销毁p,q,r, 并返回m.
//    delete []p;
//    delete []q;
//    delete []r;
//
//    return m;
//}
//
//static int Compare(const void *p1, const void *p2)
//{
//    return (*(int *)p1) - (*(int *)p2);
//}
///*
//函数介绍：从数组a[]中,每5个元素为一组,取第i组的中值元素作为数组p[]的第i个元素.
//输入： 数组a[].
//      组号 i .
//输出：存放中值元素的数组p[].
//*/
//void Mid(int a[], int i, int p[])
//{
//    int k = 5 * i;
//
//    if (a[k] > a[k+2])
//        Swap(a[k], a[k+2]);
//    if (a[k+1] > a[k+3])
//        Swap(a[k+1], a[k+3]);
//    if (a[k] > a[k+1])
//        Swap(a[k], a[k+1]);
//    if (a[k+2] > a[k+3])
//        Swap(a[k+2], a[k+3]);
//    if (a[k+1] > a[k+2])
//        Swap(a[k+1], a[k+2]);
//
//    if (a[k+4] > a[k+2])
//        p[i] = a[k+2];
//    else if (a[k+4] > a[k+1])
//        p[i] = a[k+4];
//    else
//        p[i] = a[k+1];
//}
//
//void Swap(int & a, int & b)
//{
//    int temp = a;
//    a = b;
//    b = temp;
//}

