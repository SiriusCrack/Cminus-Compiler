%{
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>

extern int yylex();
extern int line;
extern char *inputLiteral;

int yyerror(char *s) {
    printf("%s\n", s);
    return 0;
}

%}

%union {
    int intValue;
    char charValue;
    char *stringValue;
}

%token ttStatic
%token ttBool ttInt ttChar
%token ttIf ttThen ttElse ttWhile ttDo ttFor ttTo ttBy
%token ttReturn ttBreak
%token ttIncrement ttDecrement
%token ttAddAssign ttSubtractAssign ttMultiplyAssign ttDivideAssign
%token ttOr ttAnd ttNot
%token ttEqual ttNotEqual
%token ttGreaterEqual ttLesserEqual
%token ttVariable
%token <intValue> ttBoolValue ttIntValue
%token <charValue> ttCharValue
%token <stringValue> ttStringValue

%%
input:
    input ';' {
        printf("Line %d Token: ;\n", line);
    }|
    input ',' {
        printf("Line %d Token: ,\n", line);
    }|
    input ':' {
        printf("Line %d Token: :\n", line);
    }|
    input '{' {
        printf("Line %d Token: {\n", line);
    }|
    input '}' {
        printf("Line %d Token: }\n", line);
    }|
    input '[' {
        printf("Line %d Token: [\n", line);
    }|
    input ']' {
        printf("Line %d Token: ]\n", line);
    }|
    input '(' {
        printf("Line %d Token: (\n", line);
    }|
    input ')' {
        printf("Line %d Token: )\n", line);
    }|
    input ttStatic {
        printf("Line %d Token: STATIC\n", line);
    }|
    input ttBool {
        printf("Line %d Token: BOOL\n", line);
    }|
    input ttInt {
        printf("Line %d Token: INT\n", line);
    }|
    input ttChar {
        printf("Line %d Token: CHAR\n", line);
    }|
    input ttIf {
        printf("Line %d Token: IF\n", line);
    }|
    input ttThen {
        printf("Line %d Token: THEN\n", line);
    }|
    input ttElse {
        printf("Line %d Token: ELSE\n", line);
    }|
    input ttWhile {
        printf("Line %d Token: WHILE\n", line);
    }|
    input ttDo {
        printf("Line %d Token: DO\n", line);
    }|
    input ttFor {
        printf("Line %d Token: FOR\n", line);
    }|
    input ttTo {
        printf("Line %d Token: TO\n", line);
    }|
    input ttBy {
        printf("Line %d Token: BY\n", line);
    }|
    input ttReturn {
        printf("Line %d Token: RETURN\n", line);
    }|
    input ttBreak {
        printf("Line %d Token: BREAK\n", line);
    }|
    input ttIncrement {
        printf("Line %d Token: INC\n", line);
    }|
    input ttDecrement {
        printf("Line %d Token: DEC\n", line);
    }|
    input '=' {
        printf("Line %d Token: =\n", line);
    }|
    input ttAddAssign {
        printf("Line %d Token: ADDASS\n", line);
    }|
    input ttSubtractAssign {
        printf("Line %d Token: SUBASS\n", line);
    }|
    input ttMultiplyAssign {
        printf("Line %d Token: MULASS\n", line);
    }|
    input ttDivideAssign {
        printf("Line %d Token: DIVASS\n", line);
    }|
    input ttOr {
        printf("Line %d Token: OR\n", line);
    }|
    input ttAnd {
        printf("Line %d Token: AND\n", line);
    }|
    input ttNot {
        printf("Line %d Token: NOT\n", line);
    }|
    input ttEqual {
        printf("Line %d Token: EQ\n", line);
    }|
    input ttNotEqual {
        printf("Line %d Token: NEQ\n", line);
    }|
    input '>' {
        printf("Line %d Token: >\n", line);
    }|
    input '<' {
        printf("Line %d Token: <\n", line);
    }|
    input ttGreaterEqual {
        printf("Line %d Token: GEQ\n", line);
    }|
    input ttLesserEqual {
        printf("Line %d Token: LEQ\n", line);
    }|
    input '+' {
        printf("Line %d Token: +\n", line);
    }|
    input '-' {
        printf("Line %d Token: -\n", line);
    }|
    input '*' {
        printf("Line %d Token: *\n", line);
    }|
    input '/' {
        printf("Line %d Token: /\n", line);
    }|
    input '%' {
        printf("Line %d Token: %\n", line);
    }|
    input '?' {
        printf("Line %d Token: ?\n", line);
    }|
    input ttVariable {
        printf(
            "Line %d Token: ID Value: %s\n",
            line,
            inputLiteral
        );
    }|
    input ttBoolValue {
        printf(
            "Line %d Token: BOOLCONST Value: %d  Input: %s\n", 
            line,
            $2,
            inputLiteral
        );
    }|
    input ttIntValue {
        printf(
            "Line %d Token: NUMCONST Value: %d  Input: %s\n",
            line,
            $2,
            inputLiteral
        );
    }|
    input ttCharValue {
        printf(
            "Line %d Token: CHARCONST Value: '%c'  Input: %s\n",
            line,
            $2,
            inputLiteral
        );
    }|
    input ttStringValue {
        printf(
            "Line %d Token: STRINGCONST Value: \"%s\"  Len: %d  Input: %s\n",
            line,
            $2,
            strlen($2),
            inputLiteral
        );
    }|
    %empty {
    };

%%