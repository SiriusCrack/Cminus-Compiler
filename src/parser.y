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
%token <token> ytcompound

%type <nodePtr> varDeclId varDeclInit parmId mutable assignop constant returnStmt funDecl exp simpleExp andExp unaryRelExp relExp sumExp mulExp unaryExp factor expStmt compoundStmt scopedVarDecl localDecls varDecl matched stmt parms parmList parmTypeList decl
%type <nodeVectorPtr> varDeclList stmtList parmIdList
%type <literal> typeSpec

%%
program:
    declList {
    };
declList:
    declList decl {
        AST = AddSibling(AST, $2);
    }|
    decl {
        AST = AddSibling(AST, $1);
    };
decl:
    varDecl {
        $$ = $1;
    }|
    funDecl {
        $$ = $1;
    };
varDecl:
    typeSpec varDeclList ';' {
        $$ = UnpackVector($2, $1);
        workingNodeVector = NewNodeVector();
    };
scopedVarDecl:
    ytstatic typeSpec varDeclList ';' {
        UnpackVector($3, $2);
        workingNodeVector = NewNodeVector();
    }|
    typeSpec varDeclList ';' {
        $$ = UnpackVector($2, $1);
        workingNodeVector = NewNodeVector();
    };
varDeclList:
    varDeclList ',' varDeclInit {
        AddToVector(workingNodeVector, $3);
        $$ = workingNodeVector;
    }|
    varDeclInit {
        AddToVector(workingNodeVector, $1);
        $$ = workingNodeVector;
    };
varDeclInit:
    varDeclId {
        $$ = $1;
        $1->nodeType = ntVar;
    }|
    varDeclId ':' simpleExp {
    };
varDeclId:
    ID {
        $$ = NewNode($1);
        $$->nodeType = ntVar;
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
        $$ = NewNode($2);
        $$->nodeType = ntFunc;
        $$->dataType = $1;
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    }|
    ID '(' parms ')' compoundStmt {
        $$ = NewNode($1);
        $$->nodeType = ntFunc;
        $$->dataType = "void";
        $$ = AddChild($$, $3);
        $$ = AddChild($$, $5);
    };
parms:
    parmList {
        $$ = $1;
    }|
    %empty {
        Token emptyToken;
        emptyToken.tokenClass = 100;
        emptyToken.lineNum = 0;
        emptyToken.value.str = strdup("empty");
        emptyToken.literal = strdup("empty");
        $$ = NewNode(emptyToken);
        $$->nodeType = ntEmpty;
    };
parmList:
    parmList ';' parmTypeList {
    }|
    parmTypeList {
        $$ = $1; //placeholder, might want to make a vector
    };
parmTypeList:
    typeSpec parmIdList {
        $$ = UnpackVector($2, $1);
        workingNodeVector = NewNodeVector();
    };
parmIdList:
    parmIdList ',' parmId {
        AddToVector(workingNodeVector, $3);
        $$ = workingNodeVector;
    }|
    parmId {
        AddToVector(workingNodeVector, $1);
        $$ = workingNodeVector;
    };
parmId:
    ID {
        $$ = NewNode($1);
        $$->nodeType = ntParm;
    }|
    ID '[' ']' {
        printf("parm %s\n", $1);
    };
stmt:
    matched {
        $$ = $1;
    }|
    unmatched {
    };
    
matched:
    expStmt {
        $$ = $1;
    }|
    compoundStmt {
        $$ = $1;
    }|
    matchedSelectStmt {
    }|
    matchedIterStmt {
    }|
    returnStmt {
        $$ = $1;
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
        $$ = $1;
    }|
    ';' {
    };
compoundStmt:
    ytcompound localDecls stmtList '}' {
        $$ = NewNode($1);
        $$->nodeType = ntCompound;
        $$ = AddChild($$, $2);
        Node * stmtListRoot = UnpackVector($3, "stmt");
        workingNodeVector = NewNodeVector();
        $$ = AddChild($$, stmtListRoot);
    };
localDecls:
    localDecls scopedVarDecl {
        $$ = AddSibling($$, $2);
    }|
    %empty {
    };
stmtList:
    stmtList stmt {
        AddToVector(workingNodeVector, $2);
        $$ = workingNodeVector;
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
        $$ = NewNode($1);
        $$->nodeType = ntReturn;
        $$ = AddChild($$, $2);
    };
breakStmt:
    ytbreak ';' {
    };
exp:
    mutable assignop exp {
        $$ = $2;
        $$ = AddChild($$, $1);
        $$ = AddChild($$, $3);

    }|
    mutable ytinc {
    }|
    mutable ytdec {
    }|
    simpleExp {
        $$ = $1;
    };
assignop:
    ytequals {
        $$ = NewNode($1);
        $$->nodeType = ntAssign;
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
        $$ = $1;
    };
andExp:
    andExp ytand unaryRelExp {
    }|
    unaryRelExp {
        $$ = $1;
    };
unaryRelExp:
    ytnot unaryRelExp {
    }|
    relExp  {
        $$ = $1;
    };
relExp:
    sumExp relop sumExp {
    }|
    sumExp {
        $$ = $1;
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
        $$ = $1;
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
        $$ = $1;
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
        $$ = $1;
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
        $$ = $1;
    }|
    immutable {
    };
mutable:
    ID {
        $$ = NewNode($1);
        $$->nodeType = ntID;
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
        $$ = NewNode($1);
        $$->nodeType = ntConst;
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
    PrintAST(AST, 0);
    return 0;
}

int yyerror (char *s) {
    printf("%s\n", s);
    return 0;
}