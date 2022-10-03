%{

#include "Token.h"
#include "ASTNode.h"
#include <stdio.h>
#include <string.h>

extern FILE *yyin;
extern int yydebug;
int printDebugFlag;
int printTreeFlag;

Node * AST;

%}

%union {
    Token token;
    Node * nodePtr;
    char * literal;
}

%token <token> ytint ytbool ytchar ytstatic
%token <token> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%token <token> ytequals ytadd ytsub ytmul ytdiv ytmod ytassadd ytasssub ytassmul ytassdiv ytinc ytdec ytquestion
%token <token> ytlesser ytgreater yteq ytnoteq yteqlesser yteqgreater
%token <token> ytif ytelse ytwhile ytdo ytthen ytnot ytand ytor ytfor ytto ytby ytbreak ytreturn
%token <token> ytcompound ytarr

%type <nodePtr> varDeclId varDeclInit parmId mutable assignop constant returnStmt funDecl exp simpleExp andExp unaryRelExp relExp sumExp mulExp unaryExp factor expStmt compoundStmt scopedVarDecl localDecls varDecl matched stmt parms parmList parmTypeList decl relop call args sumop mulop matchedSelectStmt immutable unmatchedSelectStmt matchedIterStmt unmatchedIterStmt iterRange argList declList varDeclList stmtList parmIdList breakStmt unmatched unaryop
%type <literal> typeSpec

%%
program:
    declList {
        AST = $1;
    };
declList:
    declList decl {
        if($1 != NULL) {
            $$ = AddSibling($1, $2, printDebugFlag);
        } else {
            $$ = $2;
        }
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
        Node * cur = $2;
        while(cur != NULL) {
            cur->dataType = $1;
            if(cur->sibling != NULL) {
                cur = cur->sibling;
            } else {
                cur = NULL;
            }
        }
        $$ = $2;
    };
scopedVarDecl:
    ytstatic typeSpec varDeclList ';' {
        $3->nodeType = ntStaticVar;
        Node * cur = $3;
        while(cur != NULL) {
            cur->dataType = $2;
            if(cur->sibling != NULL) {
                cur = cur->sibling;
            } else {
                cur = NULL;
            }
        }
        $$ = $3;
    }|
    typeSpec varDeclList ';' {
        Node * cur = $2;
        while(cur != NULL) {
            cur->dataType = $1;
            if(cur->sibling != NULL) {
                cur = cur->sibling;
            } else {
                cur = NULL;
            }
        }
        $$ = $2;
    };
varDeclList:
    varDeclList ',' varDeclInit {
        if($1 != NULL) {
            $$ = AddSibling($1, $3, printDebugFlag);
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
        if($1 != NULL) {
            if($3 != NULL) {
                $$ = AddChild($1, $3, printDebugFlag);
            }
        } else {
            $$ = $1;
        }
    };
varDeclId:
    ID {
        $$ = NewNode($1, ntVar, printDebugFlag);
    }|
    ID ytarr NUMCONST ']' {
        $$ = NewNode($1, ntVarArray, printDebugFlag); // doesn't clean ytarr
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
        $$ = NewNode($2, ntFunc, printDebugFlag);
        $$->dataType = $1;
        $$ = AddChild($$, $4, printDebugFlag); //might be empty
        $$ = AddChild($$, $6, printDebugFlag);
    }|
    ID '(' parms ')' compoundStmt {
        $$ = NewNode($1, ntFunc, printDebugFlag);
        $$->dataType = strdup("void");
        $$ = AddChild($$, $3, printDebugFlag); //might be empty
        $$ = AddChild($$, $5, printDebugFlag);
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
            $$ = AddSibling($1, $3, printDebugFlag);
        }
    }|
    parmTypeList {
        $$ = $1;
    };
parmTypeList:
    typeSpec parmIdList {
        Node * cur = $2;
        while(cur != NULL) {
            cur->dataType = $1;
            if(cur->sibling != NULL) {
                cur = cur->sibling;
            } else {
                cur = NULL;
            }
        }
        $$ = $2;
    };
parmIdList:
    parmIdList ',' parmId {
        if($1 != NULL) {
            $$ = AddSibling($1, $3, printDebugFlag);
        } else {
            $$ = $1;
        }
    }|
    parmId {
        $$ = $1;
    };
parmId:
    ID {
        $$ = NewNode($1, ntParm, printDebugFlag);
    }|
    ID ytarr ']' {
        $$ = NewNode($1, ntParmArray, printDebugFlag); // doesn't clean ytarr
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
        $$ = $1;
    };
expStmt:
    exp ';' {
        $$ = $1;
    }|
    ';' {
        $$ = NULL;
    };
compoundStmt:
    ytcompound localDecls stmtList '}' {
        $$ = NewNode($1, ntCompound, printDebugFlag);
        $$ = AddChild($$, $2, printDebugFlag); //might be empty
        $$ = AddChild($$, $3, printDebugFlag);
    };
localDecls:
    localDecls scopedVarDecl {
        if($1 != NULL) {
            $$ = AddSibling($1, $2, printDebugFlag);
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
            $$ = AddSibling($1, $2, printDebugFlag);
        } else {
            $$ = $2;
        }
    }|
    %empty {
        $$ = NULL;
    };
matchedSelectStmt:
    ytif simpleExp ytthen matched ytelse matched {
        $$ = NewNode($1, ntIf, printDebugFlag);
        $$ = AddChild($$, $2, printDebugFlag);
        $$ = AddChild($$, $4, printDebugFlag);
        $$ = AddChild($$, $6, printDebugFlag);
    };
unmatchedSelectStmt:
    ytif simpleExp ytthen stmt {
        $$ = NewNode($1, ntIf, printDebugFlag);
        $$ = AddChild($$, $2, printDebugFlag);
        $$ = AddChild($$, $4, printDebugFlag);
    }|
    ytif simpleExp ytthen matched ytelse unmatched {
        $$ = NewNode($1, ntIf, printDebugFlag);
        $$ = AddChild($$, $2, printDebugFlag);
        $$ = AddChild($$, $4, printDebugFlag);
        $$ = AddChild($$, $6, printDebugFlag);
    };
matchedIterStmt:
    ytwhile simpleExp ytdo matched {
        $$ = NewNode($1, ntIter, printDebugFlag);
        $$ = AddChild($$, $2, printDebugFlag);
        $$ = AddChild($$, $4, printDebugFlag);
    }|
    ytfor ID ytequals iterRange ytdo matched {
        $$ = NewNode($1, ntTo, printDebugFlag);
        Node * id;
        id = NewNode($2, ntVar, printDebugFlag);
        id->dataType = strdup("int"); //is this fine? assumes always int
        $$ = AddChild($$, id, printDebugFlag);
        $$ = AddChild($$, $4, printDebugFlag);
        $$ = AddChild($$, $6, printDebugFlag);
    };
unmatchedIterStmt:
    ytwhile simpleExp ytdo unmatched { //untested
        $$ = NewNode($1, ntIter, printDebugFlag);
        $$ = AddChild($$, $2, printDebugFlag);
        $$ = AddChild($$, $4, printDebugFlag);
    }|
    ytfor ID ytequals iterRange ytdo unmatched { //untested
        $$ = NewNode($1, ntTo, printDebugFlag);
        Node * id;
        id = NewNode($2, ntVar, printDebugFlag);
        id->dataType = strdup("int"); //is this fine? assumes always int
        $$ = AddChild($$, id, printDebugFlag);
        $$ = AddChild($$, $4, printDebugFlag);
        $$ = AddChild($$, $6, printDebugFlag);
    };
iterRange:
    simpleExp ytto simpleExp {
        $$ = NewNode($2, ntRange, printDebugFlag);
        $$ = AddChild($$, $1, printDebugFlag);
        $$ = AddChild($$, $3, printDebugFlag);
    }|
    simpleExp ytto simpleExp ytby simpleExp {
        $$ = NewNode($2, ntRange, printDebugFlag);
        $$ = AddChild($$, $1, printDebugFlag);
        $$ = AddChild($$, $3, printDebugFlag);
        $$ = AddChild($$, $5, printDebugFlag);
    };
returnStmt:
    ytreturn ';' {
        $$ = NewNode($1, ntReturn, printDebugFlag);
    }|
    ytreturn exp ';' {
        $$ = NewNode($1, ntReturn, printDebugFlag);
        $$ = AddChild($$, $2, printDebugFlag);
    };
breakStmt:
    ytbreak ';' {
        $$ = NewNode($1, ntBreak, printDebugFlag);
    };
exp:
    mutable assignop exp {
        $2 = AddChild($2, $1, printDebugFlag);
        $2 = AddChild($2, $3, printDebugFlag);
        $$ = $2;
    }|
    mutable ytinc {
        $$ = NewNode($2, ntAssign, printDebugFlag);
        $$ = AddChild($$, $1, printDebugFlag);
    }|
    mutable ytdec {
        $$ = NewNode($2, ntAssign, printDebugFlag);
        $$ = AddChild($$, $1, printDebugFlag);
    }|
    simpleExp {
        $$ = $1;
    };
assignop:
    ytequals {
        $$ = NewNode($1, ntAssign, printDebugFlag);
    }|
    ytassadd {
        $$ = NewNode($1, ntAssign, printDebugFlag);
    }|
    ytasssub {
        $$ = NewNode($1, ntAssign, printDebugFlag);
    }|
    ytassmul {
        $$ = NewNode($1, ntAssign, printDebugFlag);
    }|
    ytassdiv {
        $$ = NewNode($1, ntAssign, printDebugFlag);
    };
simpleExp:
    simpleExp ytor andExp {
        $$ = NewNode($2, ntOrOp, printDebugFlag);
        $$ = AddChild($$, $1, printDebugFlag);
        $$ = AddChild($$, $3, printDebugFlag);
    }|
    andExp {
        $$ = $1;
    };
andExp:
    andExp ytand unaryRelExp {
        $$ = NewNode($2, ntAndOp, printDebugFlag);
        $$ = AddChild($$, $1, printDebugFlag);
        $$ = AddChild($$, $3, printDebugFlag);
    }|
    unaryRelExp {
        $$ = $1;
    };
unaryRelExp:
    ytnot unaryRelExp {
        $$ = NewNode($1, ntNotOp, printDebugFlag);
        $$ = AddChild($$, $2, printDebugFlag);
    }|
    relExp {
        $$ = $1;
    };
relExp:
    sumExp relop sumExp {
        $2 = AddChild($2, $1, printDebugFlag);
        $2 = AddChild($2, $3, printDebugFlag);
        $$ = $2;
    }|
    sumExp {
        $$ = $1;
    };
relop:
    ytlesser {
        $$ = NewNode($1, ntOp, printDebugFlag);
    }|
    yteqlesser {
        $$ = NewNode($1, ntOp, printDebugFlag);
    }|
    ytgreater {
        $$ = NewNode($1, ntOp, printDebugFlag);
    }|
    yteqgreater {
        $$ = NewNode($1, ntOp, printDebugFlag);
    }|
    yteq {
        $$ = NewNode($1, ntOp, printDebugFlag);
    }|
    ytnoteq {
        $$ = NewNode($1, ntOp, printDebugFlag);
    };
sumExp:
    sumExp sumop mulExp {
        $2 = AddChild($2, $1, printDebugFlag);
        $2 = AddChild($2, $3, printDebugFlag);
        $$ = $2;
    }|
    mulExp {
        $$ = $1;
    };
sumop:
    ytadd {
        $$ = NewNode($1, ntOp, printDebugFlag);
    }|
    ytsub {
        $$ = NewNode($1, ntOp, printDebugFlag);
    };
mulExp:
    mulExp mulop unaryExp {
        $2 = AddChild($2, $1, printDebugFlag);
        $2 = AddChild($2, $3, printDebugFlag);
        $$ = $2;
    }|
    unaryExp {
        $$ = $1;
    };
mulop:
    ytmul {
        $$ = NewNode($1, ntOp, printDebugFlag);
    }|
    ytdiv {
        $$ = NewNode($1, ntOp, printDebugFlag);
    }|
    ytmod {
        $$ = NewNode($1, ntOp, printDebugFlag);
    };
unaryExp:
    unaryop unaryExp {
        $$ = AddChild($1, $2, printDebugFlag);
    }|
    factor {
        $$ = $1;
    };
unaryop:
    ytsub {
        $$ = NewNode($1, ntSignOp, printDebugFlag);
    }|
    ytmul {
        $$ = NewNode($1, ntSizeofOp, printDebugFlag);
    }|
    ytquestion {
        $$ = NewNode($1, ntQuestOp, printDebugFlag);
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
        $$ = NewNode($1, ntID, printDebugFlag);
    }|
    ID ytarr exp ']' {
        $$ = NewNode($2, ntArrAd, printDebugFlag);
        Node * firstChild;
        firstChild = NewNode($1, ntID, printDebugFlag);
        $$ = AddChild($$, firstChild, printDebugFlag);
        $$ = AddChild($$, $3, printDebugFlag);
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
        $$ = NewNode($1, ntCall, printDebugFlag);
        if($3 != NULL) {
            $$ = AddChild($$, $3, printDebugFlag);
        }
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
        if($1 != NULL) {
            $$ = AddSibling($1, $3, printDebugFlag);
        } else {
            $$ = $3;
        }
    }|
    exp {
        $$ = $1;
    };
constant:
    NUMCONST {
        $$ = NewNode($1, ntNumConst, printDebugFlag);
    }|
    CHARCONST {
        $$ = NewNode($1, ntCharConst, printDebugFlag);
    }|
    STRINGCONST {
        $$ = NewNode($1, ntStringConst, printDebugFlag);
    }|
    BOOLCONST {
        $$ = NewNode($1, ntBoolConst, printDebugFlag);
    };
%%
int main (int argc, char *argv[]) {
    printTreeFlag = 0;
    printDebugFlag = 0;
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
        if(argv[1][1] == 'D') {
            printDebugFlag = 1;
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
        if(argv[1][1] == 'D') {
            printDebugFlag = 1;
        }
        if(argv[2][1] == 'p') {
            printTreeFlag = 1;
        }
        if(argv[2][1] == 'd') {
            yydebug = 1;
        }
        if(argv[2][1] == 'D') {
            printDebugFlag = 1;
        }
        FILE *fp = fopen(argv[3], "r");
        if(fp) {
            yyin = fp;
        }
    }
    yyparse();
    //printf("nice\n\n");
    PrintTree(AST, 0, printTreeFlag);
    return 0;
}

int yyerror (char *s) {
    printf("%s\n", s);
    return 0;
}