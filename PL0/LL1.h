//
// Created by liududu on 18-5-8.
//

#include "stdio.h"
#include "stdlib.h"

#define MaxRuleNum 8
#define MaxVnNum 5
#define MaxVtNum 5
#define MaxStackDepth 20
#define MaxPLength 20
#define MaxStLength 50


typedef enum {
    false,
    true
} bool;

/*-----------------main struct define-----------------*/
/*
声明：非终结符序号 = 100 + Vn的下标
  终结符序号 = Vn的下标
*/
/*++++++++++文法结构++++++++++*/
typedef struct pRNode /*产生式右部结构*/
{
    int rCursor; /*右部序号*/
    struct pRNode *next;
} pRNode;

typedef struct pNode /*产生式结点结构*/
{
    int lCursor; /*左部符号序号*/
    int rLength; /*右部长度*/
    /*注当rLength = 1 时，rCursor = -1为空产生式*/
    struct pRNode *rHead; /*右部结点头指针*/
}  pNode;
char Vn[MaxVnNum + 1]; /*非终结符集*/
int vnNum;
char Vt[MaxVtNum + 1]; /*终结符集*/
int vtNum;
struct pNode P[MaxRuleNum]; /*产生式*/
int PNum; /*产生式实际个数*/
char buffer[MaxPLength + 1];
char ch; /*符号或string ch;*/
char st[MaxStLength]; /*要分析的符号串*/
/*++first and follow collect struct++*/
struct collectNode /*集合元素结点结构*/
{
    int nVt; /*在终结符集中的下标*/
    struct collectNode *next;
};
struct collectNode *first[MaxVnNum + 1]; /*first集*/
struct collectNode *follow[MaxVnNum + 1]; /*follow集*/
/*+++++++++++++analysis table struct++++++++++++++++*/
int analyseTable[MaxVnNum + 1][MaxVtNum + 1 + 1];
/*预测分析表存放为产生式的编号，+1用于存放结束符，多+1用于存放#(-1)*/
/*+++++++++++++++analysis stack struct++++++++++++++*/
int analyseStack[MaxStackDepth + 1]; /*分析栈*/
int topAnalyse; /*分析栈顶*/
/*int reverseStack[MaxStackDepth + 1]; /*颠倒顺序栈*/
/*int topReverse; /*倒叙栈顶*/
/*------------------function declare---------------*/
void Init();/*初始化*/
int IndexCh(char ch);

/*返回Vn在Vn表中的位置+100、Vt在Vt表中的位置，-1表示未找到*/
void InputVt(); /*输入终结符*/
void InputVn();/*输入非终结符*/
//void ShowChArray(char *collect, int num);/*输出Vn或Vt的内容*/
void ShowChArray(char *collect);/*输出Vn或Vt的内容*/
void InputP();/*产生式输入*/
bool CheckP(char *st);/*判断产生式正确性*/
void First(int U);/*计算first集,U->xx...*/
void AddFirst(int U, int nCh); /*加入first集*/
bool HaveEmpty(int nVn); /*判断first集中是否有空(-1)*/
void Follow(int V);/*计算follow集*/
void AddFollow(int V, int nCh, int kind);/*加入follow集，
 kind = 0表加入follow集，kind = 1加入first集*/
void ShowCollect(struct collectNode **collect);/*输出first或follow集*/
void FirstFollow();/*计算first和follow*/
void CreateAT();/*构造预测分析表*/
void ShowAT();/*输出分析表*/
void Identify(char *st);/*主控程序,为操作方便*/
/*分析过程显示操作为本行变换所用，与教程的显示方式不同*/
void InitStack();/*初始化栈及符号串*/
void ShowStack();/*显示符号栈中内容*/
void Pop();/*栈顶出栈*/
void Push(int r);/*使用产生式入栈操作*/


