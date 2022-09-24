%{
#include "scanType.h"
#include <stdio.h>
#include <string.h>
extern FILE *yyin;
extern int line;
%}

%union {
    struct TokenData *tokenPtr;
}
%token <tokenPtr> ID NUMCONST CHARCONST STRINGCONST OPERAND BOOLCONST

%%
input:
    %empty {
    }|
    '\n' {
    }|
    input NUMCONST  {
        printf("Line %d Token: NUMCONST Value: %d  Input: %s\n", line, $2->nvalue, $2->tokenstr);
    }|
    input ID  { 
        printf("Line %d Token: ID Value: %s\n", line, $2->svalue); 
    }|
    input CHARCONST  { 
        printf("Line %d Token: CHARCONST Value: '%c'  Input: %s\n", line, $2->cvalue, $2->tokenstr); 
    }|
    input STRINGCONST  { 
        printf("Line %d Token: STRINGCONST Value: %s  Len: %d  Input: %s\n", line, $2->svalue, strlen($2->svalue)-2, $2->tokenstr); 
    }|
    input OPERAND  { 
        printf("Line %d Token: %s\n", line, $2->svalue); 
    }|
    input BOOLCONST  { 
        printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n", line, $2->nvalue, $2->tokenstr); 
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