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
        yylval.tokenPtr->value.svalue = svalue;
    } else if (tokenclass == BOOLCONST) {
        if(svalue[0] == 't') {
            yylval.tokenPtr->value.nvalue = 1;
        } else if (svalue[0] == 'f') {
            yylval.tokenPtr->value.nvalue = 0;
        }
    } else if (tokenclass == NUMCONST) {
        yylval.tokenPtr->value.nvalue = atoi(svalue);
    } else if (tokenclass == STRINGCONST) {
        removeEscape(svalue);
        yylval.tokenPtr->value.svalue = svalue;
    } else if (tokenclass == CHARCONST) {
        if (svalue[1] == '\\') {
            if(svalue[2] == 'n') {
                yylval.tokenPtr->value.cvalue = '\n';
            } else if(svalue[2] == '0') {
                yylval.tokenPtr->value.cvalue = '\0';
            } else {
                yylval.tokenPtr->value.cvalue = svalue[2];
            }
        } else {
            yylval.tokenPtr->value.cvalue = svalue[1];
        }
    } else {
        yylval.tokenPtr->value.svalue = svalue;
    }
    return tokenclass;
}
%}

%option noyywrap
%%
\n { 
    line++; }
[ \t] { 
    ; }
"//".*\n { 
    line++; }
"<" { 
    return setValue(line, ytlesser, yytext); }
">" { 
    return setValue(line, ytgreater, yytext); }
"=" { 
    return setValue(line, ytequals, yytext); }
"+" { 
    return setValue(line, ytadd, yytext); }
"-" { 
    return setValue(line, ytsub, yytext); }
"*" { 
    return setValue(line, ytmul, yytext); }
"/" { 
    return setValue(line, ytdiv, yytext); }
"?" { 
    return setValue(line, ytquestion, yytext); }
"%" { 
    return setValue(line, ytmod, yytext); }
"and" { 
    return setValue(line, ytand, yytext); }
"or" { 
    return setValue(line, ytor, yytext); }
"==" { 
    return setValue(line, yteq, yytext); }
"!=" { 
    return setValue(line, ytnoteq, yytext); }
"<=" { 
    return setValue(line, yteqlesser, yytext); }
">=" { 
    return setValue(line, yteqgreater, yytext); }
"+=" { 
    return setValue(line, ytassadd, yytext); }
"-=" { 
    return setValue(line, ytasssub, yytext); }
"*=" { 
    return setValue(line, ytassmul, yytext); }
"/=" { 
    return setValue(line, ytassdiv, yytext); }
"--" { 
    return setValue(line, ytinc, yytext); }
"++" { 
    return setValue(line, ytdec, yytext); }
"not" { 
    return setValue(line, ytnot, yytext); }
"int" { 
    return setValue(line, ytint, yytext); }
"if" { 
    return setValue(line, ytif, yytext); }
"for" { 
    return setValue(line, ytfor, yytext); }
"to" { 
    return setValue(line, ytto, yytext); }
"by" { 
    return setValue(line, ytby, yytext); }
"do" { 
    return setValue(line, ytdo, yytext); }
"then" { 
    return setValue(line, ytthen, yytext); }
"break" { 
    return setValue(line, ytbreak, yytext); }
"else" { 
    return setValue(line, ytelse, yytext); }
"while" { 
    return setValue(line, ytwhile, yytext); }
"return" { 
    return setValue(line, ytreturn, yytext); }
"bool" { 
    return setValue(line, ytbool, yytext); }
"char" { 
    return setValue(line, ytchar, yytext); }
"static" { 
    return setValue(line, ytstatic, yytext); }
[\[\],;:{}\(\)] { 
    return yytext[0]; }
"true"|"false" { 
    return setValue(line, BOOLCONST, yytext); }
\"(\\.|[^\n"\\])*\" { 
    return setValue(line, STRINGCONST, yytext); }
'[^']'|'\\?.' { 
    return setValue(line, CHARCONST, yytext); }
'[^\n^']+'|'\\?.[^\n^']+' { 
    printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n", line, strlen(yytext)-2, yytext); 
    return setValue(line, CHARCONST, yytext); }
[a-zA-Z][0-9a-zA-Z]* { 
    return setValue(line, ID, yytext); }
[0-9]+ { 
    return setValue(line, NUMCONST, yytext); }
. { 
    printf("ERROR(%d): Invalid or misplaced input character: '%s'. Character Ignored.\n", line, yytext); }
%%