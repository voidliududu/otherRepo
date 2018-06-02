
//以下是PL0.cpp源程序
#include<stdio.h>
#include"PL0.h"
#include"string.h"

//这个宏定义的意思表示是运行时的数据栈大小，这个会在interpret函数中出现，可以先不用管它
#define stacksize 500


/*********************************************************************************
    **  在看源程序之前，请始终记住                              **
    **  sym表示的是当前字符串的类型，                           **
    **  num表示的数字，                                          **
    **  id中存放的是字符串，                                     **
    **  记住这点在看源程序的时候非常重要。                      **
    **  另外，还要记住的是nxtlev数组中存放的是后继符号集        **
**********************************************************************************/
int main()
{
    bool nxtlev[symnum];//这个数组表示的是当前语句的后继符号集合，一共有32个
    printf("Input pl/0 file?");//输入文件的路径
    scanf("%s",fname);
    fin=fopen(fname,"r");//以只读打开文件，fin文件指针
    if(fin)
    {
        printf("List object code? (Y/N)");
        scanf("%s",fname);
        listswitch=(fname[0]=='y'||fname[0]=='Y');//listswitch用于列举代码
        printf("List symbol table? (Y/N)");
        scanf("s%",fname);
        tableswitch=(fname[0]=='y'||fname[0]=='Y');//tableswitch表示是否输出table表
        //该表类似于22页的表

        fa1=fopen("fa1.tmp","w");//以只读格式打开文件，对于本程序其实是新建一个文件
        //fa1文件中存储的是源程序，运行一次，看看这个文件就明白啦
        fprintf(fa1,"Input pl/0 file?");//将"Input pl/0 file?"输入文件中
        fprintf(fa1,"%s\n",fname);//同上
        init();//初始化
        err=0;
        cc=cx=ll=0;
        ch=' ';
        if(-1!=getsym())
        {
            //如果程序开始是对的，则往下执行
            //fa存放的是模拟程序的代码
            //fas存放的是table表中的数据
            //运行一次代码看一下文件即明白
            fa=fopen("fa.tmp","w");//以只读形式打开
            fas=fopen("fas.tmp","w");//同上
            //函数原型：int addset(bool*sr,bool*s1,bool*s2,int n);
            //bool nxtlev[32];
            /*
                declbegsys[constsym]=true;
                declbegsys[varsym]=true;
                declbegsys[procsym]=true;

                statbegsys[beginsym]=true;
                statbegsys[callsym]=true;
                statbegsys[ifsym]=true;
                statbegsys[whilesym]=true;
                执行该函数的结果为对应的下标在nxtlev中上述值均为true；
            */
            //在分程序开始的时候，其后继符号可以是
            //const,var,procedure,begin,call,if,while
            //所以在nxtlev中将上述这些置为true
            //当然在整个程序可以只有一个'.'，即程序是空的也可以，所以会有nxtlev[period]=true;
            addset(nxtlev,declbegsys,statbegsys,symnum);//symnum=32；
            nxtlev[period]=true;
            //block是编译程序的主程序，是分程序的分析处理过程，其里面调用了大部分程序
            //耐心看
            //请记住在block程序开始的时候，只读取了源程序的一个语句单位
            if(-1==block(0,0,nxtlev))
            {
                //当程序出错的时候，则关闭以下文件，并退出程序
                fclose(fa);
                fclose(fa1);
                fclose(fas);
                fclose(fin);
                printf("\n");
                return 0;
            }
            fclose(fa);
            fclose(fa1);
            fclose(fas);
            //如果在源程序的结尾没有'.'，则报错
            if(sym!=period)
            {
                error(9);
            }
            //err=0表示源程序没有错误
            if(err==0)
            {
                //在源程序没有错误的前提下，打开fa2文件，依次执行里面的语句，输出源程序结果
                fa2=fopen("fa2.tmp","w");

                //模拟计算机执行源程序
                interpret();

                fclose(fa2);
            }
            else
            {
                //如果远程有错的话，会这样
                printf("Errors in pl/0 program");
            }
        }
        fclose(fin);
    }
    else
    {
        printf("Can't open file! \n");
    }
    printf("\n");
    return 0;
}
void init()
{
    int i;

    for (i=0;i<=255;i++)
    {
        ssym[i]=nul;//nul为0，将ssym初始化为0
    }
    //ssym大小为256，可以表示所有的ASCLL码
    ssym['+']=plus;
    ssym['-']=minus;
    ssym['*']=times;
    ssym['/']=slash;
    ssym['(']=lparen;
    ssym[')']=rparen;
    ssym['=']=eql;
    ssym[',']=comma;
    ssym['.']=period;
    ssym['#']=neq;
    ssym[';']=semicolon;

    //将保留字输入word数组中，为了使用二分查找，这个设置顺序是按照字母序
    strcpy(&(word[0][0]),"begin");
    strcpy(&(word[1][0]),"call");
    strcpy(&(word[2][0]),"const");
    strcpy(&(word[3][0]),"do");
    strcpy(&(word[4][0]),"end");
    strcpy(&(word[5][0]),"if");
    strcpy(&(word[6][0]),"odd");
    strcpy(&(word[7][0]),"procedure");
    strcpy(&(word[8][0]),"read");
    strcpy(&(word[9][0]),"then");
    strcpy(&(word[10][0]),"var");
    strcpy(&(word[11][0]),"while");
    strcpy(&(word[12][0]),"write");

    //wsym内放有保留字所对应的枚举变量的值
    wsym[0]=beginsym;
    wsym[1]=callsym;
    wsym[2]=constsym;
    wsym[3]=dosym;
    wsym[4]=endsym;
    wsym[5]=ifsym;
    wsym[6]=oddsym;
    wsym[7]=procsym;
    wsym[8]=readsym;
    wsym[9]=thensym;
    wsym[10]=varsym;
    wsym[11]=whilesym;
    wsym[12]=writesym;

    //mnemonic中存放的是模拟程序的命令符
    //大小是8个，因为只有8中命令符
    strcpy(&(mnemonic[lit][0]),"lit");
    strcpy(&(mnemonic[opr][0]),"opr");
    strcpy(&(mnemonic[lod][0]),"lod");
    strcpy(&(mnemonic[sto][0]),"sto");
    strcpy(&(mnemonic[cal][0]),"cal");
    strcpy(&(mnemonic[inte][0]),"int");
    strcpy(&(mnemonic[jmp][0]),"jmp");
    strcpy(&(mnemonic[jpc][0]),"jpc");

    //初始化这些数组，全部为false
    for(i=0;i<symnum;i++)
    {
        declbegsys[i]=false;
        statbegsys[i]=false;
        facbegsys[i]=false;
    }

    //下面的这三块内容的功能在后续的介绍中会有，
    //分别是声明开始符号集，语句开始符号集，因子开始符号集
    declbegsys[constsym]=true;
    declbegsys[varsym]=true;
    declbegsys[procsym]=true;

    statbegsys[beginsym]=true;
    statbegsys[callsym]=true;
    statbegsys[ifsym]=true;
    statbegsys[whilesym]=true;

    facbegsys[ident]=true;
    facbegsys[number]=true;
    facbegsys[lparen]=true;
}

//该函数的功能是返回符号e是否在符号集s中
//是则返回true，否则返回false
int inset(int e,bool* s)
{
    return s[e];
}

//对于下标i，如果s1或s2是true，则sr也是true
//这个函数其实是初始化后继符号集，即nxtlev数组
int addset(bool* sr,bool* s1,bool* s2,int n)
{
    int i;
    for (i=0;i<n;i++)
    {
        sr[i]=s1[i]||s2[i];
    }
    return 0;
}

//下面的函数不知干什么用，我没找到这两个函数的使用地方，不知道是不是作者弄错啦
int subset(bool* sr,bool* s1,bool* s2,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        sr[i]=s1[i]&&(! s2[i]);
    }
    return 0;
}
int mulset(bool * sr,bool* s1,bool* s2,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        sr[i]=s1[i]&&s2[i];
    }
    return 0;
}

//当出问题的时候，仅仅输出错误，并不退出程序
//对于出错码，可以参考课本27页
void error (int n)
{
    char space[81];
    memset(space,32,81);//将space全部置为空格
    space[cc-1]=0;//出错时当前符号已经读完，所以是CC-1
    printf("****%s!%d\n",space,n);
    fprintf(fa1,"****%s!%d\n",space,n);
    err++;
}

int getch()
{
    if(cc==ll)
    {
        if (feof(fin))
        {
            printf("program incomplete");
            return -1;//返回-1表示文件不正常结束
        }
        ll=0;
        cc=0;
        printf("%d",cx);
        fprintf(fa1,"%d",cx);
        ch=' ';
        //下面的循环的功能是将源文件中一行代码输出并且输入fa1文件中
        while(ch!=10)//10为换行符
        {
            //fscanf(fin,"%c",&ch)
            if (EOF==fscanf(fin,"%c",&ch))//fscanf(fin,"%c",&ch)将fin指向的内容放入ch中
            {
                line[ll]=0;
                break;
            }
            printf("%c",ch);//输出代码
            fprintf(fa1,"%c",ch);//将代码输入fa1文件中
            line[ll]=ch;//将代码放入line数组中，ll表示代码长度
            ll++;
        }
        printf("\n");
        fprintf(fa1,"\n");
    }
    ch=line[cc];
    cc++;
    return 0;
}
//该函数的功能就是取一个数据单位，通过条用该函数可以一次取出一个
//数字或字符串或运算符，这个函数和getch函数我觉得应该是调用最经常地函数啦，
//每调用一次该函数，该函数就会去调用getch函数
//sym记录的是语句单位的类型，num中存放的是数字的大小
int getsym()
{
    int i,j,k;
    //忽略空格，换行符，制表符
    while (ch==' '||ch==10||ch==9)
    {
        //相当于执行if(-1==getch())
        //          return -1
        //即取一个符号单位
        getchdo;
    }
    //功能是取一个单词符号
    if(ch>='a'&&ch<='z')
    {
        k=0;
        do
        {
            if (k<al)//al=10
            {
                a[k]=ch;//将一个单词符号放入a[]数组中，从al可以看出，pl0语言要求的最大单词
                //符号不能超过10个
                k++;
            }
            getchdo;
        }while (ch>='a'&&ch<='z'||ch>='0'&&ch<='9');
        a[k]=0;//单词符号以0结尾
        strcpy(id,a);//将该单词符号复制到id[]数组中
        i=0;
        j=norw-1;//norw=13
        //执行二分查找，搜索该单词符号是否是保留字
        do{
            k=(i+j)/2;
            if (strcmp(id,word[k])<=0)
            {
                j=k-1;
            }
            if (strcmp(id,word[k])>=0)
            {
                i=k+1;
            }
        }while(i<=j);
        if(i-1>j)
        {
            sym=wsym[k];//如果是保留字则置为保留字的数字
        }
        else
        {
            sym=ident;//如果不是保留字，则置sym为1
        }
    }
        //取一个数字单位
    else
    {
        if (ch>='0'&&ch<='9')
        {
            k=0;
            num=0;
            sym=number;//以sym表示这是一个数字
            do{
                num=10*num+ch-'0';
                k++;
                getchdo;
            }while(ch>='0'&&ch<='9');
            k--;
            if(k>nmax)//要求数字位数不能超过15位，nmax=14，不过我觉得这有错误
            {
                error(30);//输出错误码
            }
        }
            //如果是赋值运算符的话，执行这个
        else
        {
            if(ch==':')
            {
                getchdo;
                if(ch=='=')
                {
                    sym=becomes;//如果是赋值的话，则置sym=19
                    getchdo;
                }
                else
                {
                    sym=nul;//个人认为这地有错，我觉得应该是错误退出才对
                }
            }
            else
            {
                if(ch=='<')
                {
                    getchdo;
                    if(ch=='=')
                    {
                        sym=leq;
                        getchdo;
                    }
                    else
                    {
                        sym=lss;
                    }
                }
                else
                {
                    if(ch=='>')
                    {
                        getchdo;
                        if(ch=='=')
                        {
                            sym=geq;
                            getchdo;
                        }
                        else
                        {
                            sym=gtr;
                        }
                    }
                    else
                    {
                        sym=ssym[ch];
                        if(sym!=period)
                        {
                            getchdo;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int gen(enum fct  x,int y,int z)
{
    if(cx>=cxmax)//cxmax=200
    {
        printf("Program too long");
        return -1;
    }
    code[cx].f=x;
    code[cx].l=y;
    code[cx].a=z;
    cx++ ;
    return 0;
}
int test(bool* s1,bool * s2,int n)
{
    if(!inset(sym,s1))
    {
        error(n);
        //当检测不通过时，不停获取符号，只到它属于需要的集合或补救集合
        while((!inset(sym,s1))&&(!inset(sym,s2)))
        {
            getsymdo;
        }
    }
    return 0;
}
//cc=cx=ll=0;cx表示源程序中代码的第几行
//block(0,0,nxtlev)这是主程序
//nxtlev中已有部分值为1，大小为32
int block(int lev,int tx,bool* fsys)//lev表示分程序所在层，tx表示当前尾指针，fsys表示当前模块后跟符号集
{
    int i;
    int dx;
    int tx0;
    int cx0;
    //新建一个
    bool nxtlev[symnum];

    dx=3;//默认为3，原因在书上
    tx0=tx;//记录本层名字的初始位置
    table[tx].adr=cx;//cx=0，即table表的第一元素的地址为0
    gendo(jmp,0,0);
    if(lev>levmax)//levmax=3，所以该编译器允许的嵌套为3层
    {
        error(32);
    }
    do{
        //如果当前字符是constant，则将字符放入table中
        if(sym==constsym)
        {
            //读取const后的常量符号
            getsymdo;
            do{
                //#define constdeclarationdo(a,b,c)
                //if(-1==constdeclaration(a,b,c))
                //  return -1
                constdeclarationdo(&tx,lev,&dx);//tx=0,lev=0,dx=3;
                while(sym==comma)//如果是逗号，则表示下一个单词串为常量，将所有的
                {                //在同一行的常量符号输入table表中
                    getsymdo;
                    constdeclarationdo(&tx,lev,&dx);
                }
                if(sym==semicolon)//为分号的时候，表示常量的读取结束，读取下一个符号串
                {
                    getsymdo;
                }
                else
                {
                    error(5);//每行必须以分号结束，如果不是，则报错
                }
            }while(sym==ident);
        }

        //如果当前字符是变量，则将字符放入table中，形式同上述代码，如对下面不动的请参照上面的代码
        if(sym==varsym)
        {
            getsymdo;
            do{
                vardeclarationdo(&tx,lev,&dx);
                while(sym==comma)
                {
                    getsymdo;
                    vardeclarationdo(&tx,lev,&dx);
                }
                if(sym==semicolon)
                {
                    getsymdo;
                }
                else
                {
                    error(5);
                }
            }while(sym==ident);
        }

        //如果当前字符是子过程，则将字符放入table中
        while(sym==procsym)
        {
            getsymdo;
            if(sym==ident)
            {
                enter(procedur,&tx,lev,&dx);
                getsymdo;
            }
            else
            {
                error(4);
            }

            //子过程的语句后面必须跟一个分号，否则错误
            if(sym==semicolon)
            {
                getsymdo;
            }
            else
            {
                error(5);
            }
            memcpy(nxtlev,fsys,sizeof(bool) *symnum);//将fsys所指的内存首地址，大小为32的内容放入nxtlev中
            //其实就是把初始化好的nexlev的内容复制到新申请的内存中去
            nxtlev[semicolon]=true;//分程序的程序体可以为空
            if(-1==block(lev+1,tx,nxtlev))//递归调用，进入子过程，此时lev+1，
            {
                return -1;
            }
            if (sym==semicolon)
            {
                getsymdo;
                memcpy(nxtlev,statbegsys,sizeof(bool)*symnum);
                nxtlev[ident]=true;
                nxtlev[procsym]=true;
                //#define testdo(a,b,c)
                //if(-1==test(a,b,c))
                //return -1
                testdo(nxtlev,fsys,6);//测试后更符号类型类型是否合法
            }
            else
            {
                error(5);
            }
        }

        //nxtlev表示语句开始的符号集
        memcpy(nxtlev,statbegsys,sizeof(bool)*symnum);
        nxtlev[ident]=true;
        nxtlev[period]=true;
        testdo(nxtlev,declbegsys,7);//测试当前符号是否是后继符号集中的元素
        //如果不是则找第一个是的位置
        //对于一个分程序的开始无非是语句开始符号集和声明开始符号集
    }while(inset(sym,declbegsys));//如果没有了声明符号的字符，则退出循环
    //jmp 0 CX表示跳转到CX      号位置执行代码，这条语句是模拟程序的第一条指令
    code[table[tx0].adr].a=cx;

    table[tx0].adr=cx;
    table[tx0].size=dx;
    cx0=cx;
    //模拟程序的第二条语句表示申请多大的存储空间，用于存储变量
    gendo(inte,0,dx);
    if(tableswitch)//是否列出table表中的内容
    {
        printf("TABLE:\n");
        if(tx0+1>tx)//当table表为空时，只输出NULL
        {
            printf("NULL\n");
        }
        for(i=tx0+1;i<=tx;i++)
        {
            switch(table[i].kind)
            {
                case constant:
                    printf("%d const %s",i,table[i].name);
                    printf("val=%d\n",table[i].val);
                    fprintf(fas,"%d const %s",i,table[i].name);
                    fprintf(fas,"val=%d\n",table[i].val);
                    break;
                case variable:
                    printf("%d var%s",i,table[i].name);
                    printf("lev=%d addr=%d\n",table[i].level,table[i].adr);
                    fprintf(fas,"%d var%s",i,table[i].name);
                    fprintf(fas,"lev=%d addr=%d\n",table[i].level,table[i].adr);
                    break;
                case procedur:
                    printf("%d proc%s",i,table[i].name);
                    printf("lev=%d addr=%d size=%d\n",table[i].level,table[i].adr,table[i].size);
                    fprintf(fas,"%d proc%s",i,table[i].name);
                    fprintf(fas,"lev=%d addr=%d size=%d\n",table[i].level,table[i].adr,table[i].size);
                    break;
            }
        }
        printf("\n");
    }
    memcpy(nxtlev,fsys,sizeof(bool) *symnum);
    nxtlev[semicolon]=true;
    nxtlev[endsym]=true;
    statementdo(nxtlev,&tx,lev);//进入语句处理程序，lev表示层，nxtlev表示后继符号集
    gendo(opr,0,0);
    memset(nxtlev,0,sizeof (bool) *symnum);//语句结束，无补救集合
    testdo(fsys,nxtlev,8);//检测语句结束的正确性，这事课本上的回答，但是我觉得有问题，我无法解决
    listcode(cx0);//列举目标代码
    return 0;
}

//该函数的功能是将源程序中的常量，变量，分程序符号串输入到table表中
//该table表是从下标1开始的，0号空间另做其它用途
void enter(enum object k,int* ptx ,int lev ,int * pdx)
{
    (*ptx)++;
    strcpy(table[(*ptx)].name,id);
    table[(*ptx)].kind=k;
    switch (k)
    {
        case constant:
            if(num>amax)//amax=2047,即const数最大为2047
            {
                error(31);
                num=0;
            }
            table[(*ptx)].val=num;
            break;
        case variable:
            table[(*ptx)].level=lev;
            table[(*ptx)].adr=(*pdx);
            (*pdx)++;
            break;
        case  procedur:
            table[(*ptx)].level=lev;
            break;
    }
}
//在table表中查找idt的位置，并返回其所在位置
int position(char * idt,int tx)
{
    int i;
    strcpy(table[0].name,idt);
    i=tx;
    while(strcmp(table[i].name,idt)!=0)
    {
        i--;
    }
    return i;
}


int constdeclaration(int * ptx,int lev,int * pdx)
{
    //如果当前的符号是一个变量，则继续执行
    if(sym==ident)
    {
        getsymdo;
        if(sym==eql||sym==becomes)
        {
            if(sym==becomes)
                error(1);
            getsymdo;
            if(sym==number)
            {
                enter(constant,ptx,lev,pdx);
                getsymdo;
            }
            else
                error(2);
        }
        else
            error(3);
    }
    else
        error(4);
    return 0;
}

int vardeclaration(int * ptx,int lev ,int * pdx)
{
    if(sym==ident)
    {
        enter(variable,ptx,lev,pdx);
        getsymdo;
    }
    else
    {
        error(4);
    }
    return 0;
}

//列举模拟程序，即目标程序
void listcode(int cx0)
{
    int i;
    if(listswitch)
    {
        for(i=cx0;i<cx;i++)
        {
            printf("%d %s %d %d\n",i,mnemonic[code[i].f],code[i].l,code[i].a);
            fprintf(fa,"%d %s %d %d\n",i,mnemonic[code[i].f],code[i].l,code[i].a);
        }
    }
}
//递归读取分析每一个语句，该函数会将整个程序的大部分子程序联系起来
//该程序中大部分是递归调用，虽说代码很多，但基本都是一个格式，所以读起来并不复杂
//相对来说还比较简单
//对于代码实现上差不多的部分，我没有做过多的注释
int statement(bool* fsys,int * ptx,int lev)
{
    int i,cx1,cx2;
    bool nxtlev[symnum];
    //如果当前字符串是一个变量，则其后跟的是一个表达式
    if(sym==ident)
    {
        //确定该变量在table表中的位置
        i=position(id,*ptx);
        if(i==0)
        {
            error(11);
        }
        else
        {
            //如果该字符串不是变量，则出错
            if(table[i].kind!=variable)
            {
                error(12);
                i=0;
            }
            else
            {
                getsymdo;
                if(sym==becomes)
                {
                    //如果是赋值符号的话，则继续读取下一个符号
                    getsymdo;
                }
                else
                {
                    error(13);
                }
                memcpy(nxtlev,fsys,sizeof(bool) *symnum);
                //赋值符号后的肯定是一个表达式，所以后跟expressiondo函数
                expressiondo(nxtlev,ptx,lev);
                if(i!=0)
                {
                    gendo(sto,lev-table[i].level,table[i].adr);
                }
            }
        }
    }
    else
    {
        if(sym==readsym)
        {
            getsymdo;
            //read命令后跟的是左括号，格式是read(X);
            if(sym!=lparen)
            {
                error(34);
            }
            else
            {
                do{
                    getsymdo;
                    //确定要将读入的值赋给哪一个变量
                    if(sym==ident)
                    {
                        i=position(id,*ptx);
                    }
                    else
                    {
                        i=0;
                    }
                    if(i==0)
                    {
                        error(35);
                    }
                    else
                    {
                        gendo(opr,0,16);
                        gendo(sto,lev-table[i].level,table[i].adr);
                    }
                    getsymdo;
                }while(sym==comma);//读到逗号时继续，原因是可能有多个输入变量
            }
            //对于read当不是逗号时，则必须是右括号，表示当前输入的结束
            if(sym!=rparen)
            {
                error(33);
                while(!inset(sym,fsys))
                {
                    getsymdo;
                }
            }
            else
            {
                getsymdo;
            }
        }
        else
        {
            if(sym==writesym)
            {
                getsymdo;
                if(sym==lparen)
                {
                    do
                    {
                        getsymdo;
                        memcpy(nxtlev,fsys,sizeof(bool)*symnum);
                        nxtlev[rparen]=true;
                        nxtlev[comma]=true;
                        //表示输出表达式的值
                        expressiondo(nxtlev,ptx,lev);
                        gendo(opr,0,14);
                    }while(sym==comma);
                    if(sym!=rparen)
                    {
                        error(33);
                    }
                    else
                    {
                        getsymdo;
                    }
                }
                gendo(opr,0,15);
            }
            else
            {
                //对于call，其后跟的是一个变量ident
                if(sym==callsym)
                {
                    getsymdo;
                    if(sym!=ident)
                    {
                        error(14);
                    }
                    else
                    {
                        i=position(id,*ptx);
                        if(i==0)
                        {
                            error(11);
                        }
                        else
                        {
                            if(table[i].kind==procedur)
                            {
                                gendo(cal,lev-table[i].level,table[i].adr);
                            }
                            else
                            {
                                error(15);
                            }
                        }
                        getsymdo;
                    }
                }
                else
                {
                    if(sym==ifsym)
                    {
                        getsymdo;
                        memcpy(nxtlev,fsys,sizeof(bool)*symnum);
                        nxtlev[thensym]=true;
                        nxtlev[dosym]=true;
                        //if子句中含有条件表达式，所以要调用条件子过程
                        conditiondo(nxtlev,ptx,lev);
                        //条件表达式后，必须跟then语句，表示条件满足时，要执行的代码
                        if(sym==thensym)
                        {
                            getsymdo;
                        }
                        else
                        {
                            error(16);
                        }
                        cx1=cx;
                        gendo(jpc,0,0);//跳转转移，栈顶为真时不跳
                        //then后跟的是一个语句
                        statementdo(fsys,ptx,lev);
                        code[cx1].a=cx;//如果条件为假，则跳转到cx的位置
                    }
                    else
                    {
                        if(sym==beginsym)
                        {
                            getsymdo;
                            memcpy(nxtlev,fsys,sizeof(bool)*symnum);
                            nxtlev[semicolon]=true;
                            nxtlev[endsym]=true;

                            statementdo(nxtlev,ptx,lev);
                            //下面的过程表达的意思就是
                            //每一个语句结束后都跟一个分号，
                            //如果后跟的是一个分号，则继续读入另一个语句
                            //如果在一个语句后直接跟了另一个语句则报错，随后处理该语句
                            while(inset(sym,statbegsys)||sym==semicolon)
                            {
                                if(sym==semicolon)
                                {
                                    getsymdo;
                                }
                                else
                                {
                                    error(10);
                                }
                                statementdo(nxtlev,ptx,lev);
                            }
                            if(sym==endsym)
                            {
                                getsymdo;
                            }
                            else
                            {
                                error(17);
                            }
                        }
                        else
                        {
                            if(sym==whilesym)
                            {
                                cx1=cx;
                                getsymdo;
                                memcpy(nxtlev,fsys,sizeof(bool)*symnum);
                                nxtlev[dosym]=true;
                                conditiondo(nxtlev,ptx,lev);
                                cx2=cx;
                                gendo(jpc,0,0);
                                if(sym==dosym)
                                {
                                    //listswitch;
                                    //上面的这一句在原来的程序里是没有注释的，
                                    //我觉得这句话应该去掉，
                                    //一是课本上没有这句话，二是如果加上这句话，我觉得有点多余
                                    getsymdo;
                                }
                                else
                                {
                                    error(18);
                                }
                                statementdo(fsys,ptx,lev);
                                gendo(jmp,0,cx1);
                                code[cx2].a=cx;
                            }
                            else
                            {
                                memset(nxtlev,0,sizeof(bool)*symnum);
                                testdo(fsys,nxtlev,19);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int expression_r(bool * fsys,int * ptx,int lev)
{
    enum symbol addop;//用于记录当前符号是+还是-
    bool nxtlev[symnum];
    //表达式的第一个符号是‘+’或者是‘-’
    if(sym==plus||sym==minus)
    {
        addop=sym;
        getsymdo;
        memcpy(nxtlev,fsys,sizeof(bool)*symnum);
        nxtlev[plus]=true;
        nxtlev[minus]=true;
        termdo(nxtlev,ptx,lev);//进入项处理的过程
        if(addop==minus)
        {
            gendo(opr,0,1);
        }
    }
    else//如果不是以+或-开始的，则指直接进入项的处理过程
    {
        memcpy(nxtlev,fsys,sizeof(bool) * symnum);
        nxtlev[plus]=true;
        nxtlev[minus]=true;
        termdo(nxtlev,ptx,lev);
    }
    //循环进入项的处理过程，知道把所有的项处理完毕，退出循环
    while(sym==plus||sym==minus)
    {
        addop=sym;
        getsymdo;
        memcpy(nxtlev,fsys,sizeof(bool) * symnum);
        nxtlev[plus]=true;
        nxtlev[minus]=true;
        termdo(nxtlev,ptx,lev);
        if(addop==plus)
        {
            gendo(opr,0,2);
        }
        else
        {
            gendo(opr,0,3);
        }
    }
    return 0;
}

//用于每一项的处理
int term(bool* fsys,int* ptx,int lev)
{
    enum symbol mulop;
    bool nxtlev[symnum];
    memcpy(nxtlev,fsys,sizeof(bool)* symnum);
    nxtlev[times]=true;
    nxtlev[slash]=true;
    factordo(nxtlev,ptx,lev);//进入因子的处理过程
    //循环进入因子的处理过程，知道把所有的因子处理完毕，退出循环
    while(sym==times||sym==slash)
    {
        mulop=sym;
        getsymdo;
        factordo(nxtlev,ptx,lev);
        if(mulop==times)//当前如果是乘号，则opr 0 4
        {
            gendo(opr,0,4);
        }
        else            //否则是除号
        {
            gendo(opr,0,5);
        }
    }
    return 0;
}

int factor (bool* fsys,int *ptx,int lev)
{
    int i;
    bool nxtlev[symnum];
    testdo(facbegsys,fsys,24);//判断当前是否是因子的语法开始符号，如果不是，则找到一个合适的
    //开始符号继续执行
    while(inset(sym,facbegsys))//如果当前不是因子的开始符号，则退出该函数
    {
        //如果当前字符是一个变量的话
        if(sym==ident)
        {
            i=position(id,*ptx);
            if(i==0)
            {
                error(11);
            }
            else
            {
                switch(table[i].kind)
                {
                    case  constant:
                        gendo(lit,0,table[i].val);//将当前常量放在栈顶
                        break;
                    case  variable:
                        gendo(lod,lev-table[i].level,table[i].adr);
                        break;
                    case   procedur://因子中不能含有过程的定义
                        error(21);
                        break;
                }
            }
            getsymdo;
        }
        else
        {
            if(sym==number)
            {
                if(num>amax)//如果数字大于最大能表示的数字，则报错。amax=2047
                {
                    error(31);
                    num=0;
                }
                gendo(lit,0,num);
                getsymdo;
            }
            else
            {
                //如果当前是一个左括号，则表示进入一个表达式的处理过程
                if(sym==lparen)
                {
                    getsymdo;
                    memcpy(nxtlev,fsys,sizeof(bool)*symnum);
                    nxtlev[rparen]=true;
                    //在左括号里面是一个表达式
                    expressiondo(nxtlev,ptx,lev);
                    if(sym==rparen)
                    {
                        getsymdo;
                    }
                    else
                    {
                        error(22);
                    }
                }
                testdo(fsys,facbegsys,23);//当前符号要么是因子的开始符号，要么是其他的开始符号
            }
        }
    }
    return 0;
}



//条件语句中不是判断奇偶性，就是判断表达式之间的大小关系
int condition(bool*fsys,int * ptx,int lev)
{
    enum symbol relop;
    bool nxtlev[symnum];
    //如果输入的是‘odd’的话，表示判断是否是奇数
    if(sym==oddsym)
    {
        getsymdo;
        expressiondo(fsys,ptx,lev);
        gendo(opr,0,6);
    }
    else
    {
        memcpy(nxtlev,fsys,sizeof(bool)*symnum);
        nxtlev[eql]=true;
        nxtlev[neq]=true;
        nxtlev[lss]=true;
        nxtlev[leq]=true;
        nxtlev[gtr]=true;
        nxtlev[geq]=true;
        //如果是表达式的话
        expressiondo(nxtlev,ptx,lev);
        //表达式与表达式之间的连接符是=、#、<、<=、>、>=
        //如果不是的话，则出错
        if(sym!=eql&&sym!=neq&&sym!=lss&&sym!=leq&&sym!=gtr&&sym!=geq)
        {
            error(20);
        }
        else
        {
            relop=sym;
            getsymdo;
            //另一个表达式
            expressiondo(fsys,ptx,lev);
            switch(relop)
            {
                case eql:
                    gendo(opr,0,8);
                    break;
                case neq:
                    gendo(opr,0,9);
                    break;
                case lss:
                    gendo(opr,0,10);
                    break;
                case geq:
                    gendo(opr,0,11);
                    break;
                case gtr:
                    gendo(opr,0,12);
                    break;
                case leq:
                    gendo(opr,0,13);
                    break;
            }
        }
    }
    return 0;
}


void interpret()
{
    int p,b,t;
    struct instruction i;//存放当前指令
    //定义运行时数据栈S，与课本29页的图类似，栈大小为500
    int s[stacksize];
    //提示开始执行源程序
    printf("start pl0\n");
    t=0;//栈顶指针
    b=0;//指令基址
    p=0;//表示code中的指针
    //头三个为0，表示的是RA，DL，SL为0
    s[0]=s[1]=s[2]=0;
    do{
        i=code[p];//code中存放的就是源程序的模拟程序，取出每一条指令
        p++;//指针指向下一条指令

        //下面的代码就是模拟计算机运行
        //在看下面的代码之前，请先看23页的指令说明
        switch(i.f)
        {
            case lit:
                s[t]=i.a;
                t++;
                break;
            case opr:
                switch(i.a)
                {
                    case 0:
                        t=b;
                        p=s[t+2];
                        b=s[t+1];
                        break;
                    case 1:
                        s[t-1]-=s[t-1];
                        break;
                    case 2:
                        t--;
                        s[t-1]=s[t-1]+s[t];
                        break;
                    case 3:
                        t--;
                        s[t-1]=s[t-1]-s[t];
                        break;
                    case 4:
                        t--;
                        s[t-1]=s[t-1]*s[t];
                        break;
                    case 5:
                        t--;
                        s[t-1]=s[t-1]/s[t];
                        break;
                    case 6:
                        s[t-1]=s[t-1]%2;
                        break;
                    case 8:
                        t--;
                        s[t-1]=(s[t-1]==s[t]);
                        break;
                    case 9:
                        t--;
                        s[t-1]=(s[t-1]!=s[t]);
                        break;
                    case 10:
                        t--;
                        s[t-1]=(s[t-1]<s[t]);
                        break;
                    case 11:
                        t--;
                        s[t-1]=(s[t-1]>=s[t]);
                        break;
                    case 12:
                        t--;
                        s[t-1]=(s[t-1]>s[t]);
                        break;
                    case 13:
                        t--;
                        s[t-1]=(s[t-1]<=s[t]);
                        break;
                    case 14:
                        printf("%d",s[t-1]);
                        fprintf(fa2,"%d",s[t-1]);
                        t--;
                        break;
                    case 15:
                        printf("\n");
                        fprintf(fa2,"n");
                        break;
                    case 16:
                        printf("?");
                        fprintf(fa2,"?");
                        scanf("%d",&(s[t]));
                        fprintf(fa2,"%d\n",s[t]);
                        t++;
                        break;
                }
                break;
            case lod://取相对当前过程的数据基址为a的内存的值到栈顶
                s[t]=s[base(i.l,s,b)+i.a];
                t++;
                break;
            case sto://栈顶的值存到相对当前过程的数据基地址为a的内存
                t--;
                s[base(i.l,s,b)+i.a]=s[t];
                break;
            case cal://调用子过程
                s[t]=base(i.l,s,b);//将父过程基地址入栈
                s[t+1]=b;//将本过程基地址入栈
                s[t+2]=p;//将当前指令指针入栈
                b=t;//改变基地址指针值为新过程的基地址
                p=i.a;//跳转
                break;
            case inte://分配内存
                t+=i.a;
                break;
            case jmp://直接跳转
                p=i.a;
                break;
            case jpc://条件跳转
                t--;
                if(s[t]==0)
                {
                    p=i.a;
                }
                break;
        }
    }while(p!=0);
}
//该函数的功能是通过基地址求上一过程的基址
int base(int l,int * s,int b)
{
    int b1;
    b1=b;
    while(l>0)
    {
        b1=s[b1];
        l--;
    }
    return b1;
}