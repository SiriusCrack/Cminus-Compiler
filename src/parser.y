%{
#include "scanType.h"
#include "ASTNode.h"
#include <stdio.h>
#include <string.h>

extern FILE *yyin;

Node * AST;

%}
%union {
    Token token;
    Node * nodePtr;
}
%token <token> ytint ytbool ytchar ytstatic
%token <token> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%token <token> ytequals ytadd ytsub ytmul ytdiv ytmod ytassadd ytasssub ytassmul ytassdiv ytinc ytdec ytquestion
%token <token> ytlesser ytgreater yteq ytnoteq yteqlesser yteqgreater
%token <token> ytif ytelse ytwhile ytdo ytthen ytnot ytand ytor ytfor ytto ytby ytbreak ytreturn

%type <nodePtr> varDeclId
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
        printf("adding sibling\n");
        $1->nodeType = "Var";
        AST = AddSibling(AST, $1);
        printf("added sibling\n");
    }|
    varDeclId ':' simpleExp {
    };
varDeclId:
    ID {
        printf("parsed: %s\n", $1.value.str);
        $$ = NewNode($1);
        printf("made node\n");
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
    printf("nice\n\n");
    PrintAST(AST);
    return 0;
}

yyerror (char *s) {
    printf("%s\n", s);
    return 0;
}