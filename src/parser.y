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
ytlbracket
ytrbracket
ytquestion
ytcomma
ytsemicolon
ytcolon
ytlbrace
ytrbrace
ytlparen
ytrparen
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
varDecl         : typeSpec varDeclList ytsemicolon
                ;
scopedVarDecl   : ytstatic typeSpec varDeclList ytsemicolon
                | typeSpec varDeclList ytsemicolon
                ;
varDeclList     : varDeclList ytcomma varDeclInit
                | varDeclInit
                ;
varDeclInit     : varDeclId
                | varDeclId ytcolon simpleExp
                ;
varDeclId       : ID
                | ID ytlbracket NUMCONST ytrbracket
                ;
typeSpec        : ytbool
                | ytchar
                | ytint
                ;
funDecl         : typeSpec ID ytlparen parms ytrparen compoundStmt
                | ID ytlparen parms ytrparen compoundStmt
                ;
parms           : parmList
                |
                ;
parmList        : parmList ytsemicolon parmTypeList
                | parmTypeList
                ;
parmTypeList    : typeSpec parmIdList
                ;
parmIdList      : parmIdList ytcomma parmId
                | parmId
                ;
parmId          : ID
                | ID ytlbracket ytrbracket
                ;
stmt            : expStmt
                | compoundStmt
                | selectStmt
                | iterStmt
                | returnStmt
                | breakStmt
                ;
expStmt         : exp ytsemicolon
                | ytsemicolon
compoundStmt    : ytlbrace localDecls stmtList ytrbrace
                ;
localDecls      : localDecls scopedVarDecl
                | 
                ;
stmtList        : stmtList stmt
                | 
                ;
selectStmt      : ytif simpleExp ytthen stmt
                | ytif simpleExp ytthen ytelse stmt
                ;
iterStmt        : ytwhile simpleExp ytthen stmt
                | ytfor ID ytequals iterRange ytdo stmt
                ;
iterRange       : simpleExp ytto simpleExp
                | simpleExp ytto simpleExp ytby simpleExp
                ;
returnStmt      : ytreturn ytsemicolon
                | ytreturn exp ytsemicolon
                ;
breakStmt       : ytbreak ytsemicolon
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
                | ID ytlbracket exp ytrbracket
                ;
immutable       : ytlparen exp ytrparen
                | call
                | constant
                ;
call            : ID ytlparen args ytrparen
                ;
args            : argList
                |
                ;
argList         : argList ytcomma exp
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