%{
#include "scanType.h"
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>

int line = 1;
char * tokenString;

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
            yylval.token.value.str = literal;
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
        case OPERAND:
            yylval.token.value.str = literal;
            break;
    }
    return tokenClass;
}
%}

%option noyywrap
%%
\n { 
    line++; }
[ \t] { 
}
"//".*\n { 
    line++; }
"<" { 
    return setToken (line, OPERAND, "<"); }
">" { 
    return setToken (line, OPERAND, ">"); }
"=" { 
    return setToken (line, OPERAND, "="); }
"+" { 
    return setToken (line, OPERAND, "+"); }
"-" { 
    return setToken (line, OPERAND, "-"); }
"*" { 
    return setToken (line, OPERAND, "*"); }
"/" { 
    return setToken (line, OPERAND, "/"); }
"[" { 
    return setToken (line, OPERAND, "["); }
"]" { 
    return setToken (line, OPERAND, "]"); }
"?" { 
    return setToken (line, OPERAND, "?"); }
"," { 
    return setToken (line, OPERAND, ","); }
";" { 
    return setToken (line, OPERAND, ";"); }
":" { 
    return setToken (line, OPERAND, ":"); }
"{" { 
    return setToken (line, OPERAND, "{"); }
"}" { 
    return setToken (line, OPERAND, "}"); }
"(" { 
    return setToken (line, OPERAND, "("); }
")" { 
    return setToken (line, OPERAND, ")"); }
"%" {
    return setToken (line, OPERAND, "%"); }
"and" {
    return setToken (line, OPERAND, "AND"); }
"or" {
    return setToken (line, OPERAND, "OR"); }
"==" { 
    return setToken (line, OPERAND, "EQ"); }
"!=" { 
    return setToken (line, OPERAND, "NEQ"); }
"<=" { 
    return setToken (line, OPERAND, "LEQ"); }
">=" { 
    return setToken (line, OPERAND, "GEQ"); }
"+=" { 
    return setToken (line, OPERAND, "ADDASS"); }
"-=" { 
    return setToken (line, OPERAND, "SUBASS"); }
"*=" { 
    return setToken (line, OPERAND, "MULASS"); }
"/=" { 
    return setToken (line, OPERAND, "DIVASS"); }
"--" { 
    return setToken (line, OPERAND, "DEC"); }
"++" { 
    return setToken (line, OPERAND, "INC"); }
"not" { 
    return setToken (line, OPERAND, "NOT"); }
"int" { 
    return setToken (line, OPERAND, "INT"); }
"if" { 
    return setToken (line, OPERAND, "IF"); }
"for" { 
    return setToken (line, OPERAND, "FOR"); }
"to" { 
    return setToken (line, OPERAND, "TO"); }
"by" { 
    return setToken (line, OPERAND, "BY"); }
"do" { 
    return setToken (line, OPERAND, "DO"); }
"then" { 
    return setToken (line, OPERAND, "THEN"); }
"break" { 
    return setToken (line, OPERAND, "BREAK"); }
"else" { 
    return setToken (line, OPERAND, "ELSE"); }
"while" { 
    return setToken (line, OPERAND, "WHILE"); }
"return" { 
    return setToken (line, OPERAND, "RETURN"); }
"bool" { 
    return setToken (line, OPERAND, "BOOL"); }
"char" { 
    return setToken (line, OPERAND, "CHAR"); }
"static" { 
    return setToken (line, OPERAND, "STATIC"); }
"true"|"false" { 
    return setToken (line, BOOLCONST, yytext); }
\"(\\.|[^\n"\\])*\" { 
    return setToken (line, STRINGCONST, yytext); }
'[^']'|'\\?.' { 
    return setToken (line, CHARCONST, yytext); }
'[^\n^']+'|'\\?.[^\n^']+' { 
    printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n", line, strlen(yytext)-2, yytext); return setToken (line, CHARCONST, yytext); }
[a-zA-Z][0-9a-zA-Z]* { 
    return setToken (line, ID, yytext); }
[0-9]+ { 
    return setToken (line, NUMCONST, yytext); }
. { 
    printf("ERROR(%d): Invalid or misplaced input character: '%s'. Character Ignored.\n", line, yytext); }
%%