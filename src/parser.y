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
%token <tokenPtr> ytint ytbool ytchar ytstatic
%token <tokenPtr> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%token <tokenPtr> ytequals ytadd ytsub ytmul ytdiv ytmod ytassadd ytasssub ytassmul ytassdiv ytinc ytdec ytquestion
%token <tokenPtr> ytlesser ytgreater yteq ytnoteq yteqlesser yteqgreater
%token <tokenPtr> ytif ytelse ytwhile ytdo ytthen ytnot ytand ytor ytfor ytto ytby ytbreak ytreturn

%%
program:
    declList {
    };
declList:
    declList decl {
    }|
    decl {
    };
decl:
    varDecl {
    }|
    funDecl {
    };
varDecl:
    typeSpec varDeclList ';' {
    };
scopedVarDecl:
    ytstatic typeSpec varDeclList ';' {
    }|
    typeSpec varDeclList ';' {
    };
varDeclList:
    varDeclList ',' varDeclInit {
    }|
    varDeclInit {
    };
varDeclInit:
    varDeclId {
    }|
    varDeclId ':' simpleExp {
    };
varDeclId:
    ID {
    }|
    ID '[' NUMCONST ']' {
    };
typeSpec:
    ytbool {
    }|
    ytchar {
    }|
    ytint {
    };
funDecl:
    typeSpec ID '(' parms ')' compoundStmt {
    }|
    ID '(' parms ')' compoundStmt {
    };
parms:
    parmList {
    }|
    %empty {
    };
parmList:
    parmList ';' parmTypeList {
    }|
    parmTypeList {
    };
parmTypeList:
    typeSpec parmIdList {
    };
parmIdList:
    parmIdList ',' parmId {
    }|
    parmId {
    };
parmId:
    ID {
    }|
    ID '[' ']' {
    };
stmt:
    matched {
    }|
    unmatched {
    };
    
matched:
    expStmt {
    }|
    compoundStmt {
    }|
    matchedSelectStmt {
    }|
    matchedIterStmt {
    }|
    returnStmt {
    }|
    breakStmt {
    };
unmatched:
    unmatchedSelectStmt {
    }|
    unmatchedIterStmt {
    };
expStmt:
    exp ';' {
    }|
    ';' {
    };
compoundStmt:
    '{' localDecls stmtList '}' {
    };
localDecls:
    localDecls scopedVarDecl {
    }|
    %empty {
    };
stmtList:
    stmtList stmt {
    }|
    %empty {
    };
matchedSelectStmt:
    ytif simpleExp ytthen matched ytelse matched {
    };
unmatchedSelectStmt:
    ytif simpleExp ytthen stmt {
    }|
    ytif simpleExp ytthen matched ytelse unmatched {
    };
matchedIterStmt:
    ytwhile simpleExp ytdo matched {
    }|
    ytfor ID ytequals iterRange ytdo matched {
    };
unmatchedIterStmt:
    ytwhile simpleExp ytdo unmatched {
    }|
    ytfor ID ytequals iterRange ytdo unmatched {
    };
iterRange:
    simpleExp ytto simpleExp {
    }|
    simpleExp ytto simpleExp ytby simpleExp {
    };
returnStmt:
    ytreturn ';' {
    }|
    ytreturn exp ';' {
    };
breakStmt:
    ytbreak ';' {
    };
exp:
    mutable assignop exp  {
    }|
    mutable ytinc {
    }|
    mutable ytdec {
    }|
    simpleExp {
    };
assignop:
    ytequals {
    }|
    ytassadd {
    }|
    ytasssub {
    }|
    ytassmul {
    }|
    ytassdiv {
    };
simpleExp:
    simpleExp ytor andExp {
    }|
    andExp {
    };
andExp:
    andExp ytand unaryRelExp {
    }|
    unaryRelExp {
    };
unaryRelExp:
    ytnot unaryRelExp {
    }|
    relExp  {
    };
relExp:
    sumExp relop sumExp {
    }|
    sumExp {
    };
relop:
    ytlesser {
    }|
    yteqlesser {
    }|
    ytgreater {
    }|
    yteqgreater {
    }|
    yteq {
    }|
    ytnoteq {
    };
sumExp:
    sumExp sumop mulExp {
    }|
    mulExp {
    };
sumop:
    ytadd {
    }|
    ytsub {
    };
mulExp:
    mulExp mulop unaryExp {
    }|
    unaryExp {
    };
mulop:
    ytmul {
    }|
    ytdiv {
    }|
    ytmod {
    };
unaryExp:
    unaryop unaryExp {
    }|
    factor {
    };
unaryop:
    ytsub {
    }|
    ytmul {
    }|
    ytquestion {
    };
factor:
    mutable {
    }|
    immutable {
    };
mutable:
    ID {
    }|
    ID '[' exp ']' {
    };
immutable:
    '(' exp ')' {
    }|
    call {
    }|
    constant {
    };
call:
    ID '(' args ')' {
    };
args:
    argList {
    }|
    %empty {
    };
argList:
    argList ',' exp {
    }|
    exp {
    };
constant:
    NUMCONST {
    }|
    CHARCONST {
    }|
    STRINGCONST {
    }|
    BOOLCONST {
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
    printf("nice\n");
    return 0;
}

yyerror (char *s) {
    printf("%s\n", line, s);
    return 0;
}