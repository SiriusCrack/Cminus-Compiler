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
        if(($1 && $2) != NULL) {
            $$ = AddSibling($1, $2);`
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
    }|
    error {
        $$ = NULL;
    };
varDecl:
    typeSpec varDeclList ';' {
        Node * cur = $2;
        while(cur != NULL) {
            SetDataType($1, cur);
            cur = cur->sibling;
        }
        $$ = $2;
        yyerrok;
    }|
    error varDeclList ';' {
        $$ = NULL;
        yyerrok;
    }|
    typeSpec error ';' {
        $$ = NULL;
        yyerrok;
    };
scopedVarDecl:
    ytstatic typeSpec varDeclList ';' { // static token memleak
        Node * cur = $3;
        while(cur != NULL) {
            SetDataType($2, cur);
            cur->nodeType = ntStaticVar;
            cur->isInitialized = 1;
            cur = cur->sibling;
        }
        $$ = $3;
        yyerrok;
    }|
    typeSpec varDeclList ';' {
        Node * cur = $2;
        while(cur != NULL) {
            SetDataType($1, cur);
            cur = cur->sibling;
        }
        $$ = $2;
        yyerrok;
    };
varDeclList:
    varDeclList ',' varDeclInit {
        if(($1 && $3) != NULL) {
            $$ = AddSibling($1, $3);
        } else {
            $$ = $3;
        }
        yyerrok;
    }|
    varDeclList ',' error {
        $$ = NULL;
    }|
    varDeclInit {
        $$ = $1;
    }|
    error {
        $$ = NULL;
    };
varDeclInit:
    varDeclId {
        $$ = $1;
    }|
    varDeclId ':' simpleExp {
        if(($1 && $3) != NULL) {
            $$ = AddChild($1, $3);
            $1->isInitialized = 1;
        } else {
            $$ = $1;
        }
    }|
    error ':' simpleExp {
        $$ = NULL;
        yyerrok;
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
    }|
    ID ytarr error { // also memleak
        $$ = NULL;
    }|
    error ']' {
        $$ = NULL;
        yyerrok;
    };
typeSpec: // doesnt clean any tokens
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
    typeSpec error {
        $$ = NULL;
    }|
    typeSpec ID '(' error {
        $$ = NULL;
    }|
    ID '(' parms ')' compoundStmt {
        $$ = NewNode($1, ntFunc);
        $$->isDecl = 1;
        $$->isInitialized = 1;
        SetDataType(strdup("void"), $$);
        $$ = AddChild($$, $3); //might be empty
        $$ = AddChild($$, $5);
        $5->nodeType = ntCompoundwFunc;
    }|
    ID '(' error {
        $$ = NULL;
    }
    ID '(' parms ')' error {
        $$ = NULL;
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
        if(($1 && $3) != NULL) {
            $$ = AddSibling($1, $3);
        } else {
            $$ = $1;
        }
    }|
    parmList ';' error {
        $$ = NULL;
    }|
    parmTypeList {
        $$ = $1;
    }|
    error {
        $$ = NULL;
    };
parmTypeList:
    typeSpec parmIdList {
        Node * cur = $2;
        while(cur != NULL) {
            SetDataType($1, cur);
            cur->isInitialized = 1;
            cur = cur->sibling;
        }
        $$ = $2;
    }|
    typeSpec error {
        $$ = NULL;
    };
parmIdList:
    parmIdList ',' parmId {
        if(($1 && $3) != NULL) {
            $$ = AddSibling($1, $3);
        } else {
            $$ = $1;
        }
        yyerrok;
    }|
    parmIdList ',' error {
        $$ = NULL;
    }|
    parmId {
        $$ = $1;
    }|
    error {
        $$ = NULL;
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
stmt: // so many memleaks
    matched {
        $$ = $1;
    }|
    unmatched {
        $$ = $1;
    };
matched:
    matchedSelectStmt {
        $$ = $1;
    }|
    matchedIterStmt {
        $$ = $1;
    }|
    expStmt {
        $$ = $1;
    }|
    compoundStmt {
        $$ = $1;
    }|
    returnStmt {
        $$ = $1;
    }|
    breakStmt {
        $$ = $1;
    };
matchedSelectStmt: 
    ytif simpleExp ytthen matched ytelse matched {
        $$ = NewNode($1, ntIf);
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    }|
    ytif error {
        $$ = NULL;
    }|
    ytif error ytelse matched {
        $$ = NULL;
        yyerrok;
    }|
    ytif error ytthen matched ytelse matched {
        $$ = NULL;
        yyerrok;
    };
matchedIterStmt:
    ytwhile simpleExp ytdo matched {
        $$ = NewNode($1, ntIter);
        $$->isLoop = 1;
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
    }|
    ytwhile error ytdo matched {
        $$ = NULL;
        yyerrok;
    }|
    ytwhile error {
        $$ = NULL;
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
    }|
    ytfor ID ytequals error ytdo matched {
        $$ = NULL;
        yyerrok;
    }|
    ytfor error {
        $$ = NULL;
    };
unmatched:
    unmatchedSelectStmt {
        $$ = $1;
    }|
    unmatchedIterStmt {
        $$ = $1;
    };
unmatchedSelectStmt:
    ytif simpleExp ytthen stmt {
        $$ = NewNode($1, ntIf);
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
    }|
    ytif error ytthen stmt {
        $$ = NULL;
        yyerrok;
    }|
    ytif simpleExp ytthen matched ytelse unmatched {
        $$ = NewNode($1, ntIf);
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
        $$ = AddChild($$, $6);
    }|
    ytif error ytthen matched ytelse unmatched {
        $$ = NULL;
        yyerrok;
    };
unmatchedIterStmt:
    ytwhile simpleExp ytdo unmatched {
        $$ = NewNode($1, ntIter);
        $$->isLoop = 1;
        $$ = AddChild($$, $2);
        $$ = AddChild($$, $4);
    }|
    ytwhile error ytdo unmatched {
        $$ = NULL;
        yyerrok;
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
    }|
    ytfor ID ytequals error ytdo unmatched {
        $$ = NULL;
        yyerrok;
    };
iterRange:
    simpleExp ytto simpleExp {
        $$ = NewNode($2, ntRange);
        $$ = AddChild($$, $1);
        $$ = AddChild($$, $3);
    }|
    simpleExp ytto error {
        $$ = NULL;
    }|
    simpleExp ytto simpleExp ytby simpleExp {
        $$ = NewNode($2, ntRange);
        $$ = AddChild($$, $1);
        $$ = AddChild($$, $3);
        $$ = AddChild($$, $5);
    }|
    error ytby error {
        $$ = NULL;
        yyerrok;
    }|
    simpleExp ytto simpleExp ytby error {
        $$ = NULL;
    };
expStmt:
    exp ';' {
        $$ = $1;
    }|
    error ';' {
        $$ = NULL;
        yyerrok;
    };
    ';' {
        $$ = NULL;
    }|
compoundStmt:
    ytcompound localDecls stmtList '}' {
        $$ = NewNode($1, ntCompound);
        $$ = AddChild($$, $2); //might be empty
        $$ = AddChild($$, $3);
        yyerrok;
    };
localDecls:
    localDecls scopedVarDecl {
        if(($1 && $2) != NULL) {
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
        if(($1 && $2) != NULL) {
            $$ = AddSibling($1, $2);
        } else {
            $$ = $2;
        }
    }|
    %empty {
        $$ = NULL;
    };
returnStmt:
    ytreturn ';' {
        $$ = NewNode($1, ntReturn);
    }|
    ytreturn exp ';' {
        $$ = NewNode($1, ntReturn);
        $$ = AddChild($$, $2);
        yyerrok;
    }|
    ytreturn error ';' {
        $$ = NULL;
        yyerrok;
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
    error assignop exp {
        $$ = NULL;
        yyerrok;
    }|
    mutable assignop error {
        $$ = NULL;
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
    }|
    error ytinc {
        $$ = NULL;
        yyerrok;
    }|
    error ytdec {
        $$ = NULL;
        yyerrok;
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
    simpleExp ytor error {
        $$ = NULL;
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
    }|
    andExp ytand error {
        $$ = NULL;
    };
unaryRelExp:
    ytnot unaryRelExp {
        $$ = NewNode($1, ntNotOp);
        $$ = AddChild($$, $2);
    }|
    ytnot error {
        $$ = NULL;
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
    sumExp sumop error {
        $$ = NULL;
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
    mulExp mulop error {
        $$ = NULL;
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
    unaryop error {
        $$ = NULL;
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
        Node * id;
        id = NewNode($1, ntID);
        $$ = AddChild($$, id);
        if($3 != NULL) {
            $$ = AddChild($$, $3);
        }
    };
immutable:
    '(' exp ')' {
        $$ = $2;
        yyerrok;
    }|
    '(' error {
        $$ = NULL;
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
    }|
    error '(' {
        $$ = NULL;
        yyerrok;
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
        if(($1 && $3) != NULL) {
            $$ = AddSibling($1, $3);
        } else {
            $$ = $3;
        }
        yyerrok;
    }|
    argList ',' error {
        $$ = NULL;
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