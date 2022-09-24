%{
#include "scanType.h"
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>

int line = 1;
char * tokenString;

void removeEscape (char *str) {
    int i, j;
    int length = strlen(str);
    for(i = 0; i < length; i++) {
        if(str[i] == '\\') {
            if (str[i+1] == 'n') {
                str[i+1] = '\n';
            }
            if (str[i+1] == '0') {
                str[i+1] = '\0';
            }
            if (str[i+1] == '\\') {
                i++;
            }
            for(j = i; j < length; j++) {
                str[j] = str[j+1];
            }
            length--;
            i--;
        }
    } 
}

static int setValue(int linenum, int tokenclass, char *svalue) {
    if (tokenclass == NUMCONST) {
        yylval.numConst.lineNum = linenum;
        yylval.numConst.tokenStr = strdup(svalue);
        yylval.numConst.value = atoi(svalue);
    } else if (tokenclass == ID) {
        yylval.id.lineNum = linenum;
        yylval.id.tokenStr = strdup(svalue);
        yylval.id.value = svalue;
    } else if (tokenclass == CHARCONST) {
        yylval.charConst.lineNum = linenum;
        yylval.charConst.tokenStr = strdup(svalue);
        if (svalue[1] == '\\') {
            if(svalue[2] == 'n') {
                yylval.charConst.value = '\n';
            } else if(svalue[2] == '0') {
                yylval.charConst.value = '\0';
            } else {
                yylval.charConst.value = svalue[2];
            }
        } else {
            yylval.charConst.value = svalue[1];
        }
    } else if (tokenclass == STRINGCONST) {
        yylval.stringConst.lineNum = linenum;
        yylval.stringConst.tokenStr = strdup(svalue);
        removeEscape(svalue);
        yylval.stringConst.value = svalue;
    } else if (tokenclass == BOOLCONST) {
        yylval.boolConst.lineNum = linenum;
        yylval.boolConst.tokenStr = strdup(svalue);
        if(svalue[0] == 't') {
            yylval.boolConst.value = 1;
        } else if (svalue[0] == 'f') {
            yylval.boolConst.value = 0;
        }
    } else if (tokenclass == OPERAND) {
        yylval.operand.lineNum = linenum;
        yylval.operand.tokenStr = strdup(svalue);
        yylval.operand.value = svalue;
    }
    return tokenclass;
}
%}

%option noyywrap
%%
\n                      { line++; }
[ \t]                   { }
"//".*\n                { line++; }
"<"                     { return setValue(line, OPERAND, "<"); }
">"                     { return setValue(line, OPERAND, ">"); }
"="                     { return setValue(line, OPERAND, "="); }
"+"                     { return setValue(line, OPERAND, "+"); }
"-"                     { return setValue(line, OPERAND, "-"); }
"*"                     { return setValue(line, OPERAND, "*"); }
"/"                     { return setValue(line, OPERAND, "/"); }
"["                     { return setValue(line, OPERAND, "["); }
"]"                     { return setValue(line, OPERAND, "]"); }
"?"                     { return setValue(line, OPERAND, "?"); }
","                     { return setValue(line, OPERAND, ","); }
";"                     { return setValue(line, OPERAND, ";"); }
":"                     { return setValue(line, OPERAND, ":"); }
"{"                     { return setValue(line, OPERAND, "{"); }
"}"                     { return setValue(line, OPERAND, "}"); }
"("                     { return setValue(line, OPERAND, "("); }
")"                     { return setValue(line, OPERAND, ")"); }
"%"                     { return setValue(line, OPERAND, "%"); }
"and"                   { return setValue(line, OPERAND, "AND"); }
"or"                    { return setValue(line, OPERAND, "OR"); }
"=="                    { return setValue(line, OPERAND, "EQ"); }
"!="                    { return setValue(line, OPERAND, "NEQ"); }
"<="                    { return setValue(line, OPERAND, "LEQ"); }
">="                    { return setValue(line, OPERAND, "GEQ"); }
"+="                    { return setValue(line, OPERAND, "ADDASS"); }
"-="                    { return setValue(line, OPERAND, "SUBASS"); }
"*="                    { return setValue(line, OPERAND, "MULASS"); }
"/="                    { return setValue(line, OPERAND, "DIVASS"); }
"--"                    { return setValue(line, OPERAND, "DEC"); }
"++"                    { return setValue(line, OPERAND, "INC"); }
"not"                   { return setValue(line, OPERAND, "NOT"); }
"int"                   { return setValue(line, OPERAND, "INT"); }
"if"                    { return setValue(line, OPERAND, "IF"); }
"for"                   { return setValue(line, OPERAND, "FOR"); }
"to"                    { return setValue(line, OPERAND, "TO"); }
"by"                    { return setValue(line, OPERAND, "BY"); }
"do"                    { return setValue(line, OPERAND, "DO"); }
"then"                  { return setValue(line, OPERAND, "THEN"); }
"break"                 { return setValue(line, OPERAND, "BREAK"); }
"else"                  { return setValue(line, OPERAND, "ELSE"); }
"while"                 { return setValue(line, OPERAND, "WHILE"); }
"return"                { return setValue(line, OPERAND, "RETURN"); }
"bool"                  { return setValue(line, OPERAND, "BOOL"); }
"char"                  { return setValue(line, OPERAND, "CHAR"); }
"static"                { return setValue(line, OPERAND, "STATIC"); }
"true"|"false"          { return setValue(line, BOOLCONST, yytext); }
\"(\\.|[^\n"\\])*\"     { return setValue(line, STRINGCONST, yytext); }
'[^']'|'\\?.'           { return setValue(line, CHARCONST, yytext); }
'[^\n^']+'|'\\?.[^\n^']+' { printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n", line, strlen(yytext)-2, yytext); return setValue(line, CHARCONST, yytext); }
[a-zA-Z][0-9a-zA-Z]*    { return setValue(line, ID, yytext); }
[0-9]+                  { return setValue(line, NUMCONST, yytext); }
.                       { printf("ERROR(%d): Invalid or misplaced input character: '%s'. Character Ignored.\n", line, yytext); }
%%