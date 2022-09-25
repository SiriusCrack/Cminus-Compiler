%{
#include "scanType.h"
#include "ASTNode.h"
#include "NodeVector.h"
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>

int line = 1;

char checkSpecialChars (char * str) {
    if (str[1] == '\\') {
        if(str[2] == 'n') {
            return '\n';
        } else if(str[2] == '0') {
            return '\0';
        } else {
            return str[2];
        }
    } else {
        return str[1];
    }
}

char * removeEscapedChars (char * str) {
    char * newStr = strdup(str);
    int i, j;
    int length = strlen(newStr);
    for(i = 0; i < length; i++) {
        if(newStr[i] == '\\') {
            if (newStr[i+1] == 'n') {
                newStr[i+1] = '\n';
            }
            if (newStr[i+1] == '0') {
                newStr[i+1] = '\0';
            }
            if (newStr[i+1] == '\\') {
                i++;
            }
            for(j = i; j < length; j++) {
                newStr[j] = newStr[j+1];
            }
            length--;
            i--;
        }
    }
    return newStr;
}

int checkBool (char * str) {
    if(str[0] == 't') {
        return 1;
    } else if (str[0] == 'f') {
        return 0;
    }
}

static int setToken (int lineNum, int tokenClass, char * literal) {
    yylval.token.tokenClass = tokenClass;
    yylval.token.lineNum = lineNum;
    yylval.token.literal = literal;
    switch (tokenClass) {
        case NUMCONST:
            yylval.token.value.integer = atoi(literal);
            break;
        case ID:
            yylval.token.value.str = removeEscapedChars(literal);
            break;
        case CHARCONST:
            yylval.token.value.character = checkSpecialChars(literal);
            break;
        case STRINGCONST:
            yylval.token.value.str = removeEscapedChars(literal);
            break;
        case BOOLCONST:
            yylval.token.value.integer = checkBool(literal);
            break;
        default:
            yylval.token.value.str = literal;
    }
    return tokenClass;
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
    return setToken (line, ytlesser, yytext); }
">" { 
    return setToken (line, ytgreater, yytext); }
"=" {
    return setToken (line, ytequals, yytext); }
"+" { 
    return setToken (line, ytadd, yytext); }
"-" { 
    return setToken (line, ytsub, yytext); }
"*" { 
    return setToken (line, ytmul, yytext); }
"/" { 
    return setToken (line, ytdiv, yytext); }
"?" { 
    return setToken (line, ytquestion, yytext); }
"%" { 
    return setToken (line, ytmod, yytext); }
"and" { 
    return setToken (line, ytand, yytext); }
"or" { 
    return setToken (line, ytor, yytext); }
"==" { 
    return setToken (line, yteq, yytext); }
"!=" { 
    return setToken (line, ytnoteq, yytext); }
"<=" { 
    return setToken (line, yteqlesser, yytext); }
">=" { 
    return setToken (line, yteqgreater, yytext); }
"+=" { 
    return setToken (line, ytassadd, yytext); }
"-=" { 
    return setToken (line, ytasssub, yytext); }
"*=" { 
    return setToken (line, ytassmul, yytext); }
"/=" { 
    return setToken (line, ytassdiv, yytext); }
"--" { 
    return setToken (line, ytinc, yytext); }
"++" { 
    return setToken (line, ytdec, yytext); }
"not" { 
    return setToken (line, ytnot, yytext); }
"int" { 
    return setToken (line, ytint, yytext); }
"if" { 
    return setToken (line, ytif, yytext); }
"for" { 
    return setToken (line, ytfor, yytext); }
"to" { 
    return setToken (line, ytto, yytext); }
"by" { 
    return setToken (line, ytby, yytext); }
"do" { 
    return setToken (line, ytdo, yytext); }
"then" { 
    return setToken (line, ytthen, yytext); }
"break" { 
    return setToken (line, ytbreak, yytext); }
"else" { 
    return setToken (line, ytelse, yytext); }
"while" { 
    return setToken (line, ytwhile, yytext); }
"return" { 
    return setToken (line, ytreturn, yytext); }
"bool" { 
    return setToken (line, ytbool, yytext); }
"char" { 
    return setToken (line, ytchar, yytext); }
"static" { 
    return setToken (line, ytstatic, yytext); }
[\[\],;:{}\(\)] { 
    return yytext[0]; }
"true"|"false" { 
    return setToken (line, BOOLCONST, yytext); }
\"(\\.|[^\n"\\])*\" { 
    return setToken (line, STRINGCONST, yytext); }
'[^']'|'\\?.' { 
    return setToken (line, CHARCONST, yytext); }
'[^\n^']+'|'\\?.[^\n^']+' { 
    printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n", line, strlen(yytext)-2, yytext); 
    return setToken (line, CHARCONST, yytext); }
[a-zA-Z][0-9a-zA-Z]* { 
    return setToken (line, ID, yytext); }
[0-9]+ { 
    return setToken (line, NUMCONST, yytext); }
. { 
    printf("ERROR(%d): Invalid or misplaced input character: '%s'. Character Ignored.\n", line, yytext); }
%%