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
%token <tokenPtr> ID NUMCONST CHARCONST STRINGCONST OPERAND BOOLCONST

%%
program         : declList
                ;
declList        : declList decl
                | decl
                ;
decl            : varDecl
                | funDecl
                ;
varDecl         : typeSpec varDeclList ';'
                ;
scopedVarDecl   : "static" typeSpec varDeclList ';'
                | typeSpec varDeclList ';'
                ;
varDeclList     : varDeclList ',' varDeclInit
                | varDeclInit
                ;
varDeclInit     : varDeclId
                | varDeclId ':' simpleExp
                ;
varDeclId       : ID
                | ID '[' NUMCONST ']'
                ;
typeSpec        : "bool"
                | "char"
                | "int"
                ;
funDecl         : typeSpec ID '(' parms ')' compoundStmt
                | ID '(' parms ')' compoundStmt
                ;
parms           : parmList
                |
                ;
parmList        : parmList ';' parmTypeList
                | parmTypeList
                ;
parmTypeList    : typeSpec parmIdList
                ;
parmIdList      : parmIdList ',' parmId
                | parmId
                ;
parmId          : ID
                | ID '[' ']'
                ;
stmt            : expStmt
                | compoundStmt
                | selectStmt
                | iterStmt
                | returnStmt
                | breakStmt
                ;
expStmt         : exp ';'
                | ';'
compoundStmt    : '{' localDecls stmtList '}'
                ;
localDecls      : localDecls scopedVarDecl
                | 
                ;
stmtList        : stmtList stmt
                | 
                ;
selectStmt      : "if" simpleExp "then" stmt
                | "if" simpleExp "then" "else" stmt
                ;
iterStmt        : "while" simpleExp "then" stmt
                | "for" ID '=' iterRange "do" stmt
                ;
iterRange       : simpleExp "to" simpleExp
                | simpleExp "to" simpleExp "by" simpleExp
                ;
returnStmt      : "return" ';'
                | "return" exp ';'
                ;
breakStmt       : "break" ';'
                ;
exp             : mutable assignop exp 
                | mutable "++"
                | mutable "--"
                | simpleExp
                ;
assignop        : '='
                | "+="
                | "-="
                | "*="
                | "/="
                ;
simpleExp       : simpleExp "or" andExp
                | andExp
                ;
andExp          : andExp "and" unaryRelExp
                | unaryRelExp
                ;
unaryRelExp     : "not" unaryRelExp
                | relExp 
                ;
relExp          : sumExp relop sumExp
                | sumExp
                ;
relop           : '<'
                | "<="
                | '>'
                | ">="
                | "=="
                | "!="
                ;
sumExp          : sumExp sumop mulExp
                | mulExp
                ;
sumop           : '+'
                | '-'
                ;
mulExp          : mulExp mulop unaryExp 
                | unaryExp 
                ;
mulop           : '*'
                | '/'
                | '%'
                ;
unaryExp        : unaryop unaryExp
                | factor
                ;
unaryop         : '-'
                | '*'
                | '?'
                ;
factor          : mutable
                | immutable
                ;
mutable         : ID
                | ID '[' exp ']'
                ;
immutable       : '(' exp ')'
                | call
                | constant
                ;
call            : ID '(' args ')'
                ;
args            : argList
                |
                ;
argList         : argList ',' exp
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
    return 0;
}

yyerror (char *s) {
    printf("%s\n", line, s);
    return 0;
}