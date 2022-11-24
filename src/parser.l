%{
#include "parser.tab.h"
#include <string.h>
#include "ScanUtils.h"

int line = 1;
char *inputLiteral;

%}
%option noyywrap

%%
\n {
    line++;
}
[ \t] {
}
"//".*\n {
    line++;
}
";" {
    return yytext[0];
}
"," {
    return yytext[0];
}
":" {
    return yytext[0];
}
"{" {
    return yytext[0];
}
"}" {
    return yytext[0];
}
"[" {
    return yytext[0];
}
"]" {
    return yytext[0];
}
"(" {
    return yytext[0];
}
")" {
    return yytext[0];
}
"static" {
    return ttStatic;
}
"bool" {
    return ttBool;
}
"int" {
    return ttInt;
}
"char" {
    return ttChar;
}
"if" {
    return ttIf;
}
"then" {
    return ttThen;
}
"else" {
    return ttElse;
}
"while" {
    return ttWhile;
}
"do" {
    return ttDo;
}
"for" {
    return ttFor;
}
"to" {
    return ttTo;
}
"by" {
    return ttBy;
}
"return" {
    return ttReturn;
}
"break" {
    return ttBreak;
}
"++" {
    return ttIncrement;
}
"--" {
    return ttDecrement;
}
"=" {
    return yytext[0];
}
"+=" {
    return ttAddAssign;
}
"-=" {
    return ttSubtractAssign;
}
"*=" {
    return ttMultiplyAssign;
}
"/=" {
    return ttDivideAssign;
}
"or" {
    return ttOr;
}
"and" {
    return ttAnd;
}
"not" {
    return ttNot;
}
"==" {
    return ttEqual;
}
"!=" {
    return ttNotEqual;
}
">" {
    return yytext[0];
}
"<" {
    return yytext[0];
}
">=" {
    return ttGreaterEqual;
}
"<=" {
    return ttLesserEqual;
}
"+" {
    return yytext[0];
}
"-" {
    return yytext[0];
}
"*" {
    return yytext[0];
}
"/" {
    return yytext[0];
}
"%" {
    return yytext[0];
}
"?" {
    return yytext[0];
}
"''" {
    printf("ERROR(%d): Empty character ''.  Characters ignored.\n", line);
}
"true" {
    inputLiteral = yytext;
    yylval.intValue = 1;
    return ttBoolValue;
}
"false" {
    inputLiteral = yytext;
    yylval.intValue = 0;
    return ttBoolValue;
}
\"(\\.|[^\n"\\])*\" {
    inputLiteral = yytext;
    yylval.stringValue = CleanString(yytext);
    return ttStringValue;
}
'[^']'|'\\?.' {
    inputLiteral = yytext;
    yylval.charValue = CleanChar(yytext);
    return ttCharValue;
}
'[^\n^']+'|'\\?.[^\n^']+' {
    inputLiteral = yytext;
    printf(
        "WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n",
        line,
        strlen(yytext) - 2,
        yytext
    );
    yylval.charValue = CleanChar(yytext);
    return ttCharValue;
}
[a-zA-Z][0-9a-zA-Z]* {
    inputLiteral = yytext;
    yylval.stringValue = strdup(yytext);
    return ttVariable;
}
[0-9]+ {
    inputLiteral = yytext;
    yylval.intValue = atoi(yytext);
    return ttIntValue;
}
. {
    printf(
        "ERROR(%d): Invalid or misplaced input character: '%s'. Character Ignored.\n",
        line,
        yytext
    );
}

%%