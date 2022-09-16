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
input   : 
        | '\n'
        | NUMCONST { printf("Line %d Token: NUMCONST Value: %d  Input: %s\n", line, $1->nvalue, $1->tokenstr); } input
        | ID { printf("Line %d Token: ID Value: %s\n", line, $1->svalue); } input
        | CHARCONST { printf("Line %d Token: CHARCONST Value: '%c'  Input: %s\n", line, $1->cvalue, $1->tokenstr); } input
        | STRINGCONST { printf("Line %d Token: STRINGCONST Value: %s  Len: %d  Input: %s\n", line, $1->svalue, strlen($1->svalue)-2, $1->tokenstr); } input
        | OPERAND { printf("Line %d Token: %s\n", line, $1->svalue); } input
        | BOOLCONST { printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n", line, $1->nvalue, $1->tokenstr); } input
        ;
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

yyerror (char *s) {
    printf("%s\n", line, s);
    return 0;
}