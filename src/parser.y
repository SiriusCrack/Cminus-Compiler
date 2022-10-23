%{
#include "Token.h"
#include "ASTNode.h"
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>

extern int yylex();

extern Node * AST;

int yyerror (char *s) { //does nothing?
    printf("%s\n", s);
    return 0;
}

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
            $$ = AddSibling($1, $2);
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
            SetDataType($1, cur);
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
            SetDataType($2, cur);
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
            SetDataType($1, cur);
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
        if($1 != NULL) {
            if($3 != NULL) {
                $$ = AddChild($1, $3);
                $1->isInitialized = 1;
            }
        } else {
            $$ = $1;
        }
    };
varDeclId:
    ID {
        $$ = NewNode($1, ntVar);
        $$->isDecl = 1;
    }|
    ID ytarr NUMCONST ']' {
        $$ = NewNode($1, ntVarArray); // doesn't clean ytarr
        $$->isDecl = 1;
        $$->isArray = 1;
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
        $$ = NewNode($2, ntFunc);
        $$->isDecl = 1;
        $$->isInitialized = 1;
        SetDataType($1, $$);
        $$ = AddChild($$, $4); //might be empty
        $$ = AddChild($$, $6);
        $6->nodeType = ntCompoundwFunc;
    }|
    ID '(' parms ')' compoundStmt {
        $$ = NewNode($1, ntFunc);
        $$->isDecl = 1;
        $$->isInitialized = 1;
        SetDataType(strdup("void"), $$);
        $$ = AddChild($$, $3); //might be empty
        $$ = AddChild($$, $5);
        $5->nodeType = ntCompoundwFunc;
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
        Node * cur = $2;
        while(cur != NULL) {
            SetDataType($1, cur);
            cur->isInitialized = 1;
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
            $$ = AddSibling($1, $3);
        } else {
            $$ = $1;
        }
    }|
    parmId {
        $$ = $1;
    };
parmId:
    ID {
        $$ = NewNode($1, ntParm);
        $$->isDecl = 1;
    }|
    ID ytarr ']' {
        $$ = NewNode($1, ntParmArray); // doesn't clean ytarr
        $$->isDecl = 1;
        $$->isArray = 1;
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
        $$ = NewNode($1, ntCompound);
        $$ = AddChild($$, $2); //might be empty
        $$ = AddChild($$, $3);
    };
localDecls:
    localDecls scopedVarDecl {
        if($1 != NULL) {
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
            $$ = AddSibling($1, $2);
        } else {
            $$ = $2;
        }
    }|
    %empty {
        $$ = NULL;
    };
matchedSelectStmt:
    ytif simpleExp ytthen matched ytelse matched {
        $$ = NewNode($1, ntIf);
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    };
unmatchedSelectStmt:
    ytif simpleExp ytthen stmt {
        $$ = NewNode($1, ntIf);
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
    }|
    ytif simpleExp ytthen matched ytelse unmatched {
        $$ = NewNode($1, ntIf);
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    };
matchedIterStmt:
    ytwhile simpleExp ytdo matched {
        $$ = NewNode($1, ntIter);
        $$->isLoop = 1;
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
    }|
    ytfor ID ytequals iterRange ytdo matched {
        $$ = NewNode($1, ntTo);
        $$->isLoop = 1;
        Node * id;
        id = NewNode($2, ntVar);
        id->isDecl = 1;
        id->isInitialized = 1;
        SetDataType(strdup("int"), id); //is this fine? assumes always int
        $$ = AddChild($$, id);
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    };
unmatchedIterStmt:
    ytwhile simpleExp ytdo unmatched {
        $$ = NewNode($1, ntIter);
        $$->isLoop = 1;
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
    }|
    ytfor ID ytequals iterRange ytdo unmatched {
        $$ = NewNode($1, ntTo);
        $$->isLoop = 1;
        Node * id;
        id = NewNode($2, ntVar);
        id->isDecl = 1;
        id->isInitialized = 1;
        SetDataType(strdup("int"), id); //is this fine? assumes always int
        $$ = AddChild($$, id);
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    };
iterRange:
    simpleExp ytto simpleExp {
        $$ = NewNode($2, ntRange);
        $$ = AddChild($$, $1);
        $$ = AddChild($$, $3);
    }|
    simpleExp ytto simpleExp ytby simpleExp {
        $$ = NewNode($2, ntRange);
        $$ = AddChild($$, $1);
        $$ = AddChild($$, $3);
        $$ = AddChild($$, $5);
    };
returnStmt:
    ytreturn ';' {
        $$ = NewNode($1, ntReturn);
    }|
    ytreturn exp ';' {
        $$ = NewNode($1, ntReturn);
        $$ = AddChild($$, $2);
    };
breakStmt:
    ytbreak ';' {
        $$ = NewNode($1, ntBreak);
    };
exp:
    mutable assignop exp {
        $2 = AddChild($2, $1);
        $2 = AddChild($2, $3);
        $$ = $2;
    }|
    mutable ytinc {
        $$ = NewNode($2, ntAssign);
        $$ = AddChild($$, $1);
    }|
    mutable ytdec {
        $$ = NewNode($2, ntAssign);
        $$ = AddChild($$, $1);
    }|
    simpleExp {
        $$ = $1;
    };
assignop:
    ytequals {
        $$ = NewNode($1, ntTrueAssign);
    }|
    ytassadd {
        $$ = NewNode($1, ntTrueAssign);
    }|
    ytasssub {
        $$ = NewNode($1, ntTrueAssign);
    }|
    ytassmul {
        $$ = NewNode($1, ntTrueAssign);
    }|
    ytassdiv {
        $$ = NewNode($1, ntTrueAssign);
    };
simpleExp:
    simpleExp ytor andExp {
        $$ = NewNode($2, ntOrOp);
        $$ = AddChild($$, $1);
        $$ = AddChild($$, $3);
    }|
    andExp {
        $$ = $1;
    };
andExp:
    andExp ytand unaryRelExp {
        $$ = NewNode($2, ntAndOp);
        $$ = AddChild($$, $1);
        $$ = AddChild($$, $3);
    }|
    unaryRelExp {
        $$ = $1;
    };
unaryRelExp:
    ytnot unaryRelExp {
        $$ = NewNode($1, ntNotOp);
        $$ = AddChild($$, $2);
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
        $$ = NewNode($1, ntRelOp);
    }|
    yteqlesser {
        $$ = NewNode($1, ntRelOp);
    }|
    ytgreater {
        $$ = NewNode($1, ntRelOp);
    }|
    yteqgreater {
        $$ = NewNode($1, ntRelOp);
    }|
    yteq {
        $$ = NewNode($1, ntRelOp);
    }|
    ytnoteq {
        $$ = NewNode($1, ntRelOp);
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
        $$ = NewNode($1, ntOp);
    }|
    ytsub {
        $$ = NewNode($1, ntOp);
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
        $$ = NewNode($1, ntOp);
    }|
    ytdiv {
        $$ = NewNode($1, ntOp);
    }|
    ytmod {
        $$ = NewNode($1, ntOp);
    };
unaryExp:
    unaryop unaryExp {
        $$ = AddChild($1, $2);
    }|
    factor {
        $$ = $1;
    };
unaryop:
    ytsub {
        $$ = NewNode($1, ntSignOp);
    }|
    ytmul {
        $$ = NewNode($1, ntSizeofOp);
    }|
    ytquestion {
        $$ = NewNode($1, ntQuestOp);
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
        $$ = NewNode($1, ntID);
    }|
    ID ytarr exp ']' {
        $$ = NewNode($2, ntArrAd);
        Node * firstChild;
        firstChild = NewNode($1, ntID);
        $$ = AddChild($$, firstChild);
        $$ = AddChild($$, $3);
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
        $$ = NewNode($1, ntCall);
        if($3 != NULL) {
            $$ = AddChild($$, $3);
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
            $$ = AddSibling($1, $3);
        } else {
            $$ = $3;
        }
    }|
    exp {
        $$ = $1;
    };
constant:
    NUMCONST {
        $$ = NewNode($1, ntNumConst);
        $$->isInitialized = 1;
        $$->isConst = 1;
    }|
    CHARCONST {
        $$ = NewNode($1, ntCharConst);
        $$->isInitialized = 1;
        $$->isConst = 1;
    }|
    STRINGCONST {
        $$ = NewNode($1, ntStringConst);
        $$->isInitialized = 1;
        $$->isConst = 1;
    }|
    BOOLCONST {
        $$ = NewNode($1, ntBoolConst);
        $$->isInitialized = 1;
        $$->isConst = 1;
    };

%%