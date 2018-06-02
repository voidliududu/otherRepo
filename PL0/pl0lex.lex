%{
#include<stdio.h>
%}
digit  [0-9]
constant (digit)+
%%
constant    {printf("constant"); return 1;}
%%