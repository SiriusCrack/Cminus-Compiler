%{
#include "scanType.h"
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>

int line = 1;

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
    struct TokenData * tokenPtr;
    tokenPtr = malloc(sizeof(struct TokenData));
    yylval.tokenPtr = tokenPtr;
    yylval.tokenPtr->linenum = linenum;
    yylval.tokenPtr->tokenstr = strdup(svalue);
    if (tokenclass == ID) {
        yylval.tokenPtr->svalue = svalue;
    } else if (tokenclass == BOOLCONST) {
        if(svalue[0] == 't') {
            yylval.tokenPtr->nvalue = 1;
        } else if (svalue[0] == 'f') {
            yylval.tokenPtr->nvalue = 0;
        }
    } else if (tokenclass == NUMCONST) {
        yylval.tokenPtr->nvalue = atoi(svalue);
    } else if (tokenclass == STRINGCONST) {
        removeEscape(svalue);
        yylval.tokenPtr->svalue = svalue;
    } else if (tokenclass == CHARCONST) {
        if (svalue[1] == '\\') {
            if(svalue[2] == 'n') {
                yylval.tokenPtr->cvalue = '\n';
            } else if(svalue[2] == '0') {
                yylval.tokenPtr->cvalue = '\0';
            } else {
                yylval.tokenPtr->cvalue = svalue[2];
            }
        } else {
            yylval.tokenPtr->cvalue = svalue[1];
        }
    } else if (tokenclass == OPERAND) {
        yylval.tokenPtr->svalue = svalue;
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
\"(\\.|[^\n"\\])*\"       { return setValue(line, STRINGCONST, yytext); }
'[^']'|'\\?.'           { return setValue(line, CHARCONST, yytext); }
'[^\n^']+'|'\\?.[^\n^']+' { printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n", line, strlen(yytext)-2, yytext); return setValue(line, CHARCONST, yytext); }
[a-zA-Z][0-9a-zA-Z]*    { return setValue(line, ID, yytext); }
[0-9]+                  { return setValue(line, NUMCONST, yytext); }
.                       { printf("ERROR(%d): Invalid or misplaced input character: '%s'. Character Ignored.\n", line, yytext); }
%%