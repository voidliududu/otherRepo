//
// Created by liududu on 18-5-8.
//

//#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int i, j, k, flag, number, status;
/*status which is use to judge the string is keywords or not!*/
char ch;
char words[10] = {" "};
char program[500];

int Scan(char program[]) {
    char *keywords[13] = {"void", "main", "if", "then", "break", "int", "char", "float", "include", "for", "while",
                          "printf", "scanf"};
    number = 0;
    status = 0;
    j = 0;
    ch = program[i++];      /* To handle the lettle space ands tab*/
/*handle letters*/
    if ((ch >= 'a') && (ch <= 'z')) {
        while ((ch >= 'a') && (ch <= 'z')) {
            words[j++] = ch;
            ch = program[i++];
        }
        i--;
        words[j++] = '\0';
        for (k = 0; k < 13; k++)
            if (strcmp(words, keywords[k]) == 0)

                switch (k) {
                    case 0: {
                        flag = 1;
                        status = 1;
                        break;
                    }
                    case 1: {
                        flag = 2;
                        status = 1;
                        break;
                    }
                    case 2: {
                        flag = 3;
                        status = 1;
                        break;
                    }
                    case 3: {
                        flag = 4;
                        status = 1;
                        break;
                    }
                    case 4: {
                        flag = 5;
                        status = 1;
                        break;
                    }
                    case 5: {
                        flag = 6;
                        status = 1;
                        break;
                    }
                    case 6: {
                        flag = 7;
                        status = 1;
                        break;
                    }
                    case 7: {
                        flag = 8;
                        status = 1;
                        break;
                    }
                    case 8: {
                        flag = 9;
                        status = 1;
                        break;
                    }
                    case 9: {
                        flag = 10;
                        status = 1;
                        break;
                    }
                    case 10: {
                        flag = 11;
                        status = 1;
                        break;
                    }
                    case 11: {
                        flag = 12;
                        status = 1;
                        break;
                    }
                    case 12: {
                        flag = 13;
                        status = 1;
                        break;
                    }
                }
        if (status == 0) {
            flag = 100;
        }
    }
/*handle digits*/
    else if ((ch >= '0') && (ch <= '9')) {
        number = 0;
        while ((ch >= '0') && (ch <= '9')) {
            number = number * 10 + (ch - '0');
            ch = program[i++];
        }
        flag = 200;
        i--;
    }
/*opereation and edge handle*/
    else
        switch (ch) {
            case '=': {
                if (ch == '=')
                    words[j++] = ch;
                words[j] = '\0';
                ch = program[i++];
                if (ch == '=') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 401;
                } else {
                    i--;
                    flag = 402;
                }
                break;
            }
            case '>': {
                if (ch == '>')
                    words[j++] = ch;
                words[j] = '\0';
                ch = program[i++];
                if (ch == '=') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 403;
                } else {
                    i--;
                    flag = 404;
                }
                break;
            }
            case '<': {
                if (ch == '<')
                    words[j++] = ch;
                words[j] = '\0';
                ch = program[i++];
                if (ch == '=') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 405;
                } else {
                    i--;
                    flag = 406;
                }
                break;
            }
            case '!': {
                if (ch == '!')
                    words[j++] = ch;
                words[j] = '\0';
                ch = program[i++];
                if (ch == '=') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 407;
                } else {
                    i--;
                    flag = 408;
                }
                break;
            }
            case '+': {
                if (ch == '+')
                    words[j++] = ch;
                words[j] = '\0';
                ch = program[i++];
                if (ch == '=') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 409;
                } else if (ch == '+') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 410;
                } else {
                    i--;
                    flag = 411;
                }
                break;
            }
            case '-': {
                if (ch == '-')
                    words[j++] = ch;
                words[j] = '\0';
                ch = program[i++];
                if (ch == '=') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 412;
                } else if (ch == '-') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 413;
                } else {
                    i--;
                    flag = 414;
                }
                break;
            }
            case '*': {
                if (ch == '*')
                    words[j++] = ch;
                words[j] = '\0';
                ch = program[i++];
                if (ch == '=') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 415;
                } else {
                    i--;
                    flag = 416;
                }
                break;
            }
            case '/': {
                if (ch == '/')
                    words[j++] = ch;
                words[j] = '\0';
                ch = program[i++];
                if (ch == '=') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 417;
                } else {
                    i--;
                    flag = 418;
                }
                break;
            }
            case ';': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 501;
                break;
            }
            case '(': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 502;
                break;
            }
            case ')': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 503;
                break;
            }
            case '[': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 504;
                break;
            }
            case ']': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 505;
                break;
            }
            case '{': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 506;
                break;
            }
            case '}': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 507;
                break;
            }
            case ':': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 508;
                break;
            }
            case '"': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 509;
                break;
            }
            case '%': {
                if (ch == '%')
                    words[j++] = ch;
                words[j] = '\0';
                ch = program[i++];
                if (ch == '=') {
                    words[j++] = ch;
                    words[j] = '\0';
                    flag = 510;
                } else {
                    i--;
                    flag = 511;
                }
                break;
            }
            case ',': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 512;
                break;
            }
            case '#': {
                words[j] = ch;
                words[j + 1] = '\0';
                flag = 513;
                break;
            }
            case '@': {
                words[j] = '#';
                flag = 0;
                break;
            }
            default: {
                flag = -1;
                break;
            }
        }
    return flag;
}

main() {
    i = 0;
    printf("please input a program end with @");
    do {
        ch = getchar();
        program[i++] = ch;
    } while (ch != '@');
    i = 0;
    do {
        flag = Scan(program);
        if (flag == 200) {
            printf("(%2d,%4d)", flag, number);
        } else if (flag == -1) {
            printf("(%d,error)", flag);
        } else {
            printf("(%2d,%4s)", flag, words);
        }
    } while (flag != 0);
}
