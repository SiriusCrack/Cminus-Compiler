%{

#include "scanType.h"
#include "ASTNode.h"
#include "NodeVector.h"
#include <stdio.h>
#include <string.h>

extern FILE *yyin;

Node * AST;
NodeVector * workingNodeVector;

%}

%union {
    Token token;
    Node * nodePtr;
    NodeVector * nodeVectorPtr;
    char * literal;
}

%token <token> ytint ytbool ytchar ytstatic
%token <token> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%token <token> ytequals ytadd ytsub ytmul ytdiv ytmod ytassadd ytasssub ytassmul ytassdiv ytinc ytdec ytquestion
%token <token> ytlesser ytgreater yteq ytnoteq yteqlesser yteqgreater
%token <token> ytif ytelse ytwhile ytdo ytthen ytnot ytand ytor ytfor ytto ytby ytbreak ytreturn

%type <nodePtr> varDeclId varDeclInit parmId
%type <nodeVectorPtr> varDeclList
%type <literal> typeSpec

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
        UnpackVector($2, $1);
        workingNodeVector = NewNodeVector();
    };
scopedVarDecl:
    ytstatic typeSpec varDeclList ';' {
        UnpackVector($3, $2);
        workingNodeVector = NewNodeVector();
    }|
    typeSpec varDeclList ';' {
        UnpackVector($2, $1);
        workingNodeVector = NewNodeVector();
    };
varDeclList:
    varDeclList ',' varDeclInit {
        AddToVector(workingNodeVector, $3);
        $$ = workingNodeVector;
        printf("added to 1vector: %s\n", $3->value.str);
    }|
    varDeclInit {
        AddToVector(workingNodeVector, $1);
        $$ = workingNodeVector;
        printf("added to 2vector: %s\n", $1->value.str);
    };
varDeclInit:
    varDeclId {
        $$ = $1;
        $1->nodeType = "Var";
        AST = AddSibling(AST, $1);
        printf("added sibling: %s\n", $1->value.str);
    }|
    varDeclId ':' simpleExp {
    };
varDeclId:
    ID {
        $$ = NewNode($1);
        printf("made node: %s\n", $$->value.str);
    }|
    ID '[' NUMCONST ']' {
        printf("vardecl %s %s\n", $1, $3);
    };
typeSpec:
    ytbool {
        $$ = "bool";
    }|
    ytchar {
        $$ = "char";
    }|
    ytint {
        $$ = "int";
    };
funDecl:
    typeSpec ID '(' parms ')' compoundStmt {
        printf("func %s\n", $2);
    }|
    ID '(' parms ')' compoundStmt {
        printf("func %s\n", $1);
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
        $$ = NewNode($1);
        printf("made node: %s\n", $$->value.str); //start passing up. guessing the tree gets built in funDecl?
        // AST = AddSibling(AST, $$);
        // printf("added sibling: %s\n", $$->value.str);
    }|
    ID '[' ']' {
        printf("parm %s\n", $1);
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
        printf("%s\n", $2);
    };
unmatchedIterStmt:
    ytwhile simpleExp ytdo unmatched {
    }|
    ytfor ID ytequals iterRange ytdo unmatched {
        printf("%s\n", $2);
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
        printf("mut %s\n", $1);
    }|
    ID '[' exp ']' {
        printf("mut %s\n", $1);
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
        printf("call %s\n", $1);
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
        printf("const %s\n", $1);
    }|
    CHARCONST {
        printf("const %s\n", $1);
    }|
    STRINGCONST {
        printf("const %s\n", $1);
    }|
    BOOLCONST {
        printf("const %s\n", $1);
    };
%%
int main (int argc, char *argv[]) {
    if(argc > 1) {
        FILE *fp = fopen(argv[1], "r");
        if(fp) {
            yyin = fp;
        }
    }
    workingNodeVector = NewNodeVector();
    yyparse();
    printf("nice\n\n");
    PrintAST(AST);
    return 0;
}

int yyerror (char *s) {
    printf("%s\n", s);
    return 0;
}