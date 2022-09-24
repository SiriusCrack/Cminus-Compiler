%{
#include "scanType.h"
#include <stdio.h>
#include <string.h>
extern FILE *yyin;
extern int line;
%}

%union {
    struct Token token;
}
%token <token> NUMCONST ID CHARCONST STRINGCONST BOOLCONST OPERAND

%%
input:
    %empty {
    }|
    '\n' {
    }|
    input NUMCONST  {
        printf("Line %d Token: NUMCONST Value: %d  Input: %s\n", $2.lineNum, $2.value.integer, $2.literal);
    }|
    input ID  {
        printf("Line %d Token: ID Value: %s\n", $2.lineNum, $2.value.str);
    }|
    input CHARCONST  {
        printf("Line %d Token: CHARCONST Value: '%c'  Input: %s\n", $2.lineNum, $2.value.character, $2.literal);
    }|
    input STRINGCONST  {
        printf("Line %d Token: STRINGCONST Value: %s  Len: %d  Input: %s\n", $2.lineNum, $2.value.str, strlen($2.value.str)-2, $2.literal);
    }|
    input BOOLCONST  {
        printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n", $2.lineNum, $2.value.integer, $2.literal);
    }|
    input OPERAND  {
        printf("Line %d Token: %s\n", $2.lineNum, $2.value.str);
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