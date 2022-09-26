%{

#include "scanType.h"
#include "ASTNode.h"
#include "NodeVector.h"
#include <stdio.h>
#include <string.h>

extern FILE *yyin;
extern int yydebug;
int printTreeFlag;

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

%type <nodePtr> varDeclId varDeclInit parmId mutable assignop constant returnStmt funDecl exp simpleExp andExp unaryRelExp relExp sumExp mulExp unaryExp factor expStmt compoundStmt scopedVarDecl localDecls varDecl matched stmt parms parmList parmTypeList decl relop call args sumop mulop matchedSelectStmt immutable unmatchedSelectStmt matchedIterStmt unmatchedIterStmt iterRange
%type <nodeVectorPtr> varDeclList stmtList parmIdList argList
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
        if($1 != NULL) {
            $$ = $1;
        }
    }|
    funDecl {
        if($1 != NULL) {
            $$ = $1;
        }
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
        if($1 != NULL) {
            $$ = $1;
        }
    }|
    unmatched {
    };
    
matched:
    expStmt {
        if($1 != NULL) {
            $$ = $1;
        }
    }|
    compoundStmt {
        if($1 != NULL) {
            $$ = $1;
        }
    }|
    matchedSelectStmt {
        if($1 != NULL) {
            $$ = $1;
        }
    }|
    matchedIterStmt {
    }|
    returnStmt {
        if($1 != NULL) {
            $$ = $1;
        }
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
        if($1 != NULL) {
            $$ = $1;
        }
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
        Token emptyToken;
        emptyToken.tokenClass = 100;
        emptyToken.lineNum = 0;
        emptyToken.value.str = strdup("empty");
        $$ = NewNode(emptyToken);
        $$->nodeType = ntEmpty;
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
        $$ = NewNode($1);
        $$->nodeType = ntIf;
        if ($2 != NULL) {
            $$ = AddChild($$, $2);
        }
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    };
unmatchedSelectStmt:
    ytif simpleExp ytthen stmt {
        $$ = NULL;
    }|
    ytif simpleExp ytthen matched ytelse unmatched {
        $$ = NULL;
    };
matchedIterStmt:
    ytwhile simpleExp ytdo matched {
        $$ = NULL;
    }|
    ytfor ID ytequals iterRange ytdo matched {
    };
unmatchedIterStmt:
    ytwhile simpleExp ytdo unmatched {
        $$ = NULL;
    }|
    ytfor ID ytequals iterRange ytdo unmatched {
    };
iterRange:
    simpleExp ytto simpleExp {
        $$ = NULL;
    }|
    simpleExp ytto simpleExp ytby simpleExp {
        $$ = NULL;
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
        $$ = NULL;
    }|
    andExp {
        if($1 != NULL) {
            $$ = $1;
        }
    };
andExp:
    andExp ytand unaryRelExp {
        $$ = NULL;
    }|
    unaryRelExp {
        if($1 != NULL) {
            $$ = $1;
        }
    };
unaryRelExp:
    ytnot unaryRelExp {
        $$ = NULL;
    }|
    relExp {
        if($1 != NULL) {
            $$ = $1;
        }
    };
relExp:
    sumExp relop sumExp {
        $2 = AddChild($2, $1);
        $2 = AddChild($2, $3);
        $$ = $2;
    }|
    sumExp {
        if($1 != NULL) {
            $$ = $1;
        }
    };
relop:
    ytlesser {
        $$ = NULL;
    }|
    yteqlesser {
        $$ = NULL;
    }|
    ytgreater {
        $$ = NULL;
    }|
    yteqgreater {
        $$ = NULL;
    }|
    yteq {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    }|
    ytnoteq {
        $$ = NULL;
    };
sumExp:
    sumExp sumop mulExp {
        $2 = AddChild($2, $1);
        $2 = AddChild($2, $3);
        $$ = $2;
    }|
    mulExp {
        if($1 != NULL) {
            $$ = $1;
        }
    };
sumop:
    ytadd {
        $$ = NULL;
    }|
    ytsub {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    };
mulExp:
    mulExp mulop unaryExp {
        $2 = AddChild($2, $1);
        $2 = AddChild($2, $3);
        $$ = $2;
    }|
    unaryExp {
        if($1 != NULL) {
            $$ = $1;
        }
    };
mulop:
    ytmul {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    }|
    ytdiv {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    }|
    ytmod {
        $$ = NULL;
    };
unaryExp:
    unaryop unaryExp {
        $$ = NULL;
    }|
    factor {
        if($1 != NULL) {
            $$ = $1;
        }
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
        if($1 != NULL) {
            $$ = $1;
        }
    }|
    immutable {
        if($1 != NULL) {
            $$ = $1;
        }
    };
mutable:
    ID {
        $$ = NewNode($1);
        $$->nodeType = ntID;
    }|
    ID '[' exp ']' {
        $$ = NULL;
    };
immutable:
    '(' exp ')' {
        $$ = NULL;
    }|
    call {
        if($1 != NULL) {
            $$ = $1;
        }
    }|
    constant {
        if($1 != NULL) {
            $$ = $1;
        }
    };
call:
    ID '(' args ')' {
        $$ = NewNode($1);
        $$->nodeType = ntCall;
        $$ = AddChild($$, $3);
    };
args:
    argList {
        $$ = UnpackVector($1, "arg");
        workingNodeVector = NewNodeVector();
    }|
    %empty {
        Token emptyToken;
        emptyToken.tokenClass = 100;
        emptyToken.lineNum = 0;
        emptyToken.value.str = strdup("empty");
        $$ = NewNode(emptyToken);
        $$->nodeType = ntEmpty;
    };
argList:
    argList ',' exp {
        AddToVector(workingNodeVector, $3);
        $$ = workingNodeVector;
    }|
    exp {
        AddToVector(workingNodeVector, $1);
        $$ = workingNodeVector;
    };
constant:
    NUMCONST {
        $$ = NewNode($1);
        $$->nodeType = ntConst;
    }|
    CHARCONST {
        printf("constant CHARCONST\n");
    }|
    STRINGCONST {
        printf("constant STRINGCONST\n");
    }|
    BOOLCONST {
        printf("constant BOOLCONST\n");
    };
%%
int main (int argc, char *argv[]) {
    printTreeFlag = 0;
    if(argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if(fp) {
            yyin = fp;
        }
    } else if(argc == 3) {
        if(argv[1][1] == 'p') {
            printTreeFlag = 1;
        }
        if(argv[1][1] == 'd') {
            yydebug = 1;
        }
        FILE *fp = fopen(argv[2], "r");
        if(fp) {
            yyin = fp;
        }
    } else if(argc == 4) {
        if(argv[1][1] == 'p') {
            printTreeFlag = 1;
        }
        if(argv[1][1] == 'd') {
            yydebug = 1;
        }
        if(argv[2][1] == 'p') {
            printTreeFlag = 1;
        }
        if(argv[2][1] == 'd') {
            yydebug = 1;
        }
        FILE *fp = fopen(argv[3], "r");
        if(fp) {
            yyin = fp;
        }
    }
    workingNodeVector = NewNodeVector();
    yyparse();
    //printf("nice\n\n");
    PrintTree(AST, 0, printTreeFlag);
    return 0;
}

int yyerror (char *s) {
    printf("%s\n", s);
    return 0;
}