%{

#include "Token.h"
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

%type <nodePtr> varDeclId varDeclInit parmId mutable assignop constant returnStmt funDecl exp simpleExp andExp unaryRelExp relExp sumExp mulExp unaryExp factor expStmt compoundStmt scopedVarDecl localDecls varDecl matched stmt parms parmList parmTypeList decl relop call args sumop mulop matchedSelectStmt immutable unmatchedSelectStmt matchedIterStmt unmatchedIterStmt iterRange argList declList varDeclList stmtList parmIdList breakStmt unmatched
%type <literal> typeSpec

%%
program:
    declList {
        AST = $1;
    };
declList:
    declList decl {
        $$ = $1;
        $$ = AddSibling($1, $2);
    }|
    decl {
        $$ = $1;
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
        if($2 == NULL) {
            printf("null varDecl\n");
        } else {
            $$ = $2;
            Node * cur = $2;
            while(cur != NULL) {
                cur->dataType = $1;
                if(cur->sibling != NULL) {
                    cur = cur->sibling;
                } else {
                    cur = NULL;
                }
            }
        }
    };
scopedVarDecl:
    ytstatic typeSpec varDeclList ';' {
        if($3 == NULL) {
            printf("null varDeclList\n");
        } else {
            $$ = $3;
            Node * cur = $3;
            while(cur != NULL) {
                cur->dataType = $2;
                if(cur->sibling != NULL) {
                    cur = cur->sibling;
                } else {
                    cur = NULL;
                }
            }
        }
    }|
    typeSpec varDeclList ';' {
        if($2 == NULL) {
            printf("null varDeclList\n");
        } else {
            $$ = $2;
            Node * cur = $2;
            while(cur != NULL) {
                cur->dataType = $1;
                if(cur->sibling != NULL) {
                    cur = cur->sibling;
                } else {
                    cur = NULL;
                }
            }
        }
    };
varDeclList:
    varDeclList ',' varDeclInit {
        if($1 != NULL) {
            $$ = AddSibling($1, $3);
        } else {
            $$ = $3;
        }
    }|
    varDeclInit {
        $$ = $1;
    };
varDeclInit:
    varDeclId {
        $$ = $1;
    }|
    varDeclId ':' simpleExp {
        printf("varDeclId ':' simpleExp\n");
    };
varDeclId:
    ID {
        $$ = NewNode($1);
        $$->nodeType = ntVar;
    }|
    ID '[' NUMCONST ']' {
        $$ = NewNode($1);
        $$->nodeType = ntVarArray;
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
        $$ = AddChild($$, $4); //might be empty
        $$ = AddChild($$, $6);
    }|
    ID '(' parms ')' compoundStmt {
        $$ = NewNode($1);
        $$->nodeType = ntFunc;
        $$->dataType = "void";
        $$ = AddChild($$, $3); //might be empty
        $$ = AddChild($$, $5);
    };
parms:
    parmList {
        $$ = $1;
    }|
    %empty {
        $$ = NULL;
    };
parmList:
    parmList ';' parmTypeList {
        $$ = $1;
        if($3 != NULL) {
            $$ = AddSibling($1, $3);
        }
    }|
    parmTypeList {
        $$ = $1;
    };
parmTypeList:
    typeSpec parmIdList {
        if($2 == NULL) {
            printf("null parmIdList\n");
        } else {
            $$ = $2;
            Node * cur = $2;
            while(cur != NULL) {
                cur->dataType = $1;
                if(cur->sibling != NULL) {
                    cur = cur->sibling;
                } else {
                    cur = NULL;
                }
            }
        }
    };
parmIdList:
    parmIdList ',' parmId {
        $$ = $1;
        if($3 != NULL) {
            $$ = AddSibling($1, $3);
        }
    }|
    parmId {
        $$ = $1;
    };
parmId:
    ID {
        $$ = NewNode($1);
        $$->nodeType = ntParm;
    }|
    ID '[' ']' {
        $$ = NewNode($1);
        $$->nodeType = ntParmArray;
    };
stmt:
    matched {
        $$ = $1;
    }|
    unmatched {
        $$ = $1;
    };
    
matched:
    expStmt {
        $$ = $1;
    }|
    compoundStmt {
        $$ = $1;
    }|
    matchedSelectStmt {
        $$ = $1;
    }|
    matchedIterStmt {
        $$ = $1;
    }|
    returnStmt {
        $$ = $1;
    }|
    breakStmt {
        $$ = $1;
    };
unmatched:
    unmatchedSelectStmt {
        $$ = $1;
    }|
    unmatchedIterStmt {
        printf("unmatchedIterStmt\n");
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
        $$ = AddChild($$, $2); //might be empty
        $$ = AddChild($$, $3);
    };
localDecls:
    localDecls scopedVarDecl {
        if($2 == NULL) {
            printf("null scopedVarDecl\n");
        } else if($1 != NULL) {
            $$ = AddSibling($1, $2);
        } else {
            $$ = $2;
        }
    }|
    %empty {
        $$ = NULL;
    };
stmtList:
    stmtList stmt {
        if($1 != NULL) {
            $$ = $1;
            if($2 != NULL) {
                $$ = AddSibling($1, $2);
            }
        } else {
            $$ = $2;
        }
    }|
    %empty {
        $$ = NULL;
    };
matchedSelectStmt:
    ytif simpleExp ytthen matched ytelse matched {
        $$ = NewNode($1);
        $$->nodeType = ntIf;
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    };
unmatchedSelectStmt:
    ytif simpleExp ytthen stmt {
        $$ = NewNode($1);
        $$->nodeType = ntIf;
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
    }|
    ytif simpleExp ytthen matched ytelse unmatched {
        printf("ytif simpleExp ytthen matched ytelse unmatched\n");
    };
matchedIterStmt:
    ytwhile simpleExp ytdo matched {
        $$ = NewNode($1);
        $$->nodeType = ntIter;
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
    }|
    ytfor ID ytequals iterRange ytdo matched {
        $$ = NewNode($1);
        $$->nodeType = ntTo;

        Node * id = NewNode($2);
        id->nodeType = ntVar;
        id->dataType = "int"; //is this fine? assumes always int

        $$ = AddChild($$, id);
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    };
unmatchedIterStmt:
    ytwhile simpleExp ytdo unmatched {
        printf("ytwhile simpleExp ytdo unmatched\n");
    }|
    ytfor ID ytequals iterRange ytdo unmatched {
        printf("ytfor ID ytequals iterRange ytdo unmatched\n");
    };
iterRange:
    simpleExp ytto simpleExp {
        printf("simpleExp ytto simpleExp\n");
    }|
    simpleExp ytto simpleExp ytby simpleExp {
        $$ = NewNode($2);
        $$->nodeType = ntRange;
        $$ = AddChild($$, $1);
        $$ = AddChild($$, $3);
        $$ = AddChild($$, $5);
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
        $$ = NewNode($1);
        $$->nodeType = ntBreak;
    };
exp:
    mutable assignop exp {
        $$ = $2;
        $$ = AddChild($$, $1);
        $$ = AddChild($$, $3);
    }|
    mutable ytinc {
        $$ = NewNode($2);
        $$->nodeType = ntAssign;
        $$ = AddChild($$, $1);
    }|
    mutable ytdec {
        $$ = NewNode($2);
        $$->nodeType = ntAssign;
        $$ = AddChild($$, $1);
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
        printf("ytassadd\n");
    }|
    ytasssub {
        printf("ytasssub\n");
    }|
    ytassmul {
        printf("ytassmul\n");
    }|
    ytassdiv {
        $$ = NewNode($1);
        $$->nodeType = ntAssign;
    };
simpleExp:
    simpleExp ytor andExp {
        printf("simpleExp ytor andExp\n");
    }|
    andExp {
        $$ = $1;
    };
andExp:
    andExp ytand unaryRelExp {
        printf("andExp ytand unaryRelExp\n");
    }|
    unaryRelExp {
        $$ = $1;
    };
unaryRelExp:
    ytnot unaryRelExp {
        printf("ytnot unaryRelExp\n");
    }|
    relExp {
        $$ = $1;
    };
relExp:
    sumExp relop sumExp {
        $2 = AddChild($2, $1);
        $2 = AddChild($2, $3);
        $$ = $2;
    }|
    sumExp {
        $$ = $1;
    };
relop:
    ytlesser {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    }|
    yteqlesser {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    }|
    ytgreater {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    }|
    yteqgreater {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    }|
    yteq {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    }|
    ytnoteq {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    };
sumExp:
    sumExp sumop mulExp {
        $2 = AddChild($2, $1);
        $2 = AddChild($2, $3);
        $$ = $2;
    }|
    mulExp {
        $$ = $1;
    };
sumop:
    ytadd {
        $$ = NewNode($1);
        $$->nodeType = ntOp;
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
        $$ = $1;
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
        $$ = NewNode($1);
        $$->nodeType = ntOp;
    };
unaryExp:
    unaryop unaryExp {
        printf("unaryop unaryExp\n");
    }|
    factor {
        $$ = $1;
    };
unaryop:
    ytsub {
        printf("ytsub\n");
    }|
    ytmul {
        printf("ytmul\n");
    }|
    ytquestion {
        printf("ytquestion\n");
    };
factor:
    mutable {
        $$ = $1;
    }|
    immutable {
        $$ = $1;
    };
mutable:
    ID {
        $$ = NewNode($1);
        $$->nodeType = ntID;
    }|
    ID '[' exp ']' {
        printf("ID exp\n");
    };
immutable:
    '(' exp ')' {
        $$ = $2;
    }|
    call {
        $$ = $1;
    }|
    constant {
        $$ = $1;
    };
call:
    ID '(' args ')' {
        $$ = NewNode($1);
        $$->nodeType = ntCall;
        $$ = AddChild($$, $3);
    };
args:
    argList {
        $$ = $1;
    }|
    %empty {
        $$ = NULL;
    };
argList:
    argList ',' exp {
        $$ = AddSibling($1, $3);
    }|
    exp {
        $$ = $1;
    };
constant:
    NUMCONST {
        $$ = NewNode($1);
        $$->nodeType = ntNumConst;
    }|
    CHARCONST {
        printf("constant CHARCONST\n");
    }|
    STRINGCONST {
        printf("constant STRINGCONST\n");
    }|
    BOOLCONST {
        $$ = NewNode($1);
        $$->nodeType = ntBoolConst;
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