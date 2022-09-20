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
%token <tokenPtr> 
ID
NUMCONST
CHARCONST
STRINGCONST
BOOLCONST
ytlesser
ytgreater
ytequals
ytadd
ytsub
ytmul
ytdiv
ytquestion
ytmod
ytand
ytor
yteq
ytnoteq
yteqlesser
yteqgreater
ytassadd
ytasssub
ytassmul
ytassdiv
ytinc
ytdec
ytnot
ytint
ytif
ytfor
ytto
ytby
ytdo
ytthen
ytbreak
ytelse
ytwhile
ytreturn
ytbool
ytchar
ytstatic

%%
program         : declList
                ;
declList        : declList decl
                | decl
                ;
decl            : varDecl
                | funDecl
                ;
varDecl         : typeSpec varDeclList ';'
                ;
scopedVarDecl   : ytstatic typeSpec varDeclList ';'
                | typeSpec varDeclList ';'
                ;
varDeclList     : varDeclList ',' varDeclInit
                | varDeclInit
                ;
varDeclInit     : varDeclId
                | varDeclId ':' simpleExp
                ;
varDeclId       : ID
                | ID '[' NUMCONST ']'
                ;
typeSpec        : ytbool
                | ytchar
                | ytint
                ;
funDecl         : typeSpec ID '(' parms ')' compoundStmt
                | ID '(' parms ')' compoundStmt
                ;
parms           : parmList
                | %empty
                ;
parmList        : parmList ';' parmTypeList
                | parmTypeList
                ;
parmTypeList    : typeSpec parmIdList
                ;
parmIdList      : parmIdList ',' parmId
                | parmId
                ;
parmId          : ID
                | ID '[' ']'
                ;
stmt            : expStmt
                | compoundStmt
                | selectStmt
                | iterStmt
                | returnStmt
                | breakStmt
                ;
expStmt         : exp ';'
                | ';'
                ;
compoundStmt    : '{' localDecls stmtList '}'
                ;
localDecls      : localDecls scopedVarDecl
                | %empty
                ;
stmtList        : stmtList stmt
                | %empty
                ;
selectStmt      : ytif simpleExp ytthen stmt
                | ytif simpleExp ytthen stmt ytelse stmt
                ;
iterStmt        : ytwhile simpleExp ytdo stmt
                | ytfor ID ytequals iterRange ytdo stmt
                ;
iterRange       : simpleExp ytto simpleExp
                | simpleExp ytto simpleExp ytby simpleExp
                ;
returnStmt      : ytreturn ';'
                | ytreturn exp ';'
                ;
breakStmt       : ytbreak ';'
                ;
exp             : mutable assignop exp 
                | mutable ytinc
                | mutable ytdec
                | simpleExp
                ;
assignop        : ytequals
                | ytassadd
                | ytasssub
                | ytassmul
                | ytassdiv
                ;
simpleExp       : simpleExp ytor andExp
                | andExp
                ;
andExp          : andExp ytand unaryRelExp
                | unaryRelExp
                ;
unaryRelExp     : ytnot unaryRelExp
                | relExp 
                ;
relExp          : sumExp relop sumExp
                | sumExp
                ;
relop           : ytlesser
                | yteqlesser
                | ytgreater
                | yteqgreater
                | yteq
                | ytnoteq
                ;
sumExp          : sumExp sumop mulExp
                | mulExp
                ;
sumop           : ytadd
                | ytsub
                ;
mulExp          : mulExp mulop unaryExp
                | unaryExp
                ;
mulop           : ytmul
                | ytdiv
                | ytmod
                ;
unaryExp        : unaryop unaryExp
                | factor
                ;
unaryop         : ytsub
                | ytmul
                | ytquestion
                ;
factor          : mutable
                | immutable
                ;
mutable         : ID
                | ID '[' exp ']'
                ;
immutable       : '(' exp ')'
                | call
                | constant
                ;
call            : ID '(' args ')'
                ;
args            : argList
                | %empty
                ;
argList         : argList ',' exp
                | exp
                ;
constant        : NUMCONST
                | CHARCONST
                | STRINGCONST
                | BOOLCONST
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
    printf("nice\n");
    return 0;
}

yyerror (char *s) {
    printf("%s\n", line, s);
    return 0;
}