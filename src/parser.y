%{
#include "scanType.h"
#include <stdio.h>
#include <string.h>
extern FILE *yyin;
extern int line;
%}

%union {
    struct NumConst numConst;
    struct ID id;
    struct CharConst charConst;
    struct StringConst stringConst;
    struct Operand operand;
    struct BoolConst boolConst;
}
%token <numConst> NUMCONST
%token <id> ID
%token <charConst> CHARCONST
%token <stringConst> STRINGCONST
%token <boolConst> BOOLCONST
%token <operand> OPERAND

%%
input:
    %empty {
    }|
    '\n' {
    }|
    input NUMCONST  {
        printf("Line %d Token: NUMCONST Value: %d  Input: %s\n", line, $2.value, $2.tokenStr);
        free($2.tokenStr);
    }|
    input ID  {
        printf("Line %d Token: ID Value: %s\n", line, $2.value);
        free($2.tokenStr);
    }|
    input CHARCONST  {
        printf("Line %d Token: CHARCONST Value: '%c'  Input: %s\n", line, $2.value, $2.tokenStr);
        free($2.tokenStr);
    }|
    input STRINGCONST  {
        printf("Line %d Token: STRINGCONST Value: %s  Len: %d  Input: %s\n", line, $2.value, strlen($2.value)-2, $2.tokenStr);
        free($2.tokenStr);
    }|
    input BOOLCONST  {
        printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n", line, $2.value, $2.tokenStr);
        free($2.tokenStr);
    }|
    input OPERAND  {
        printf("Line %d Token: %s\n", line, $2.value);
        free($2.tokenStr);
    };
%%
int main (int argc, char *argv[]) {
    if(argc > 1) {
        FILE *fp = fopen(argv[1], "r");
        if(fp) {
            yyin = fp;
        }
    }
    yyparse();
    return 0;
}

int yyerror (char *s) {
    printf("%s\n", line, s);
    return 0;
}