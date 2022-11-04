/*
 *  Probably better if just noone looks in here ever again tbh
 */

#include "yyerror.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Token * lastToken;
extern int errs;
extern int warns;
extern int line;

int expTokens[10];

void getExpecting(char *expString, int expCount);
void initializeExpTokens();
char * ytToString(int yToken);
int findExpTokens(const char *msg);
int isBasic(int tokenClass);
int isBasicString(int tokenClass);

void yyerror(const char *msg) {
    // printf("%s\n", msg);
    initializeExpTokens();
    char expecting[100] = "";
    if(strstr(msg, "syntax error, unexpected '('")) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected '(', expecting %s.\n",
                line,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected '('.\n",
                line
            );
        }
    } else if(strstr(msg, "syntax error, unexpected ':'")) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ':', expecting %s.\n",
                line,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ':'.\n",
                line
            );
        }
    } else if(strstr(msg, "syntax error, unexpected '}'")) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected '}', expecting %s.\n",
                line,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected '}'.\n",
                line
            );
        }
    } else if(strstr(msg, "syntax error, unexpected ','")) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ',', expecting %s.\n",
                line,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ','.\n",
                line
            );
        }
    } else if(strstr(msg, "syntax error, unexpected ')'")) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ')', expecting %s.\n",
                line,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ')'.\n",
                line
            );
        }
    } else if(strstr(msg, "syntax error, unexpected ';'")) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ';', expecting %s.\n",
                line,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ';'.\n",
                line
            );
        }
    } else if(lastToken->tokenClass == ID) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected identifier \"%s\", expecting %s.\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected identifier \"%s\".\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        }
    } else if(lastToken->tokenClass == NUMCONST) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected numeric constant \"%s\", expecting %s.\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected numeric constant \"%s\".\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        }
    } else if(lastToken->tokenClass == BOOLCONST) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected Boolean constant \"%s\", expecting %s.\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected Boolean constant \"%s\".\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        }
    } else if(lastToken->tokenClass == STRINGCONST) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected string constant \"%s\", expecting %s.\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected string constant \"%s\".\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        }
    } else if(lastToken->tokenClass == CHARCONST) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected character constant %s, expecting %s.\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected character constant %s.\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        }
    } else if(isBasic(lastToken->tokenClass)) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected '%s', expecting %s.\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected '%s'.\n",
                lastToken->lineNum,
                lastToken->literal
            );
        }
    } else if(isBasicString(lastToken->tokenClass)) {
        int expCount = findExpTokens(msg);
        if(expCount > 0) {
            getExpecting(expecting, expCount);
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected \"%s\", expecting %s.\n",
                lastToken->lineNum,
                lastToken->literal,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected \"%s\".\n",
                lastToken->lineNum,
                lastToken->literal
            );
        }
    } else {
        printf("%s %d\n", msg, lastToken->tokenClass);
    }
}

void initializeExpTokens() {
    for(int i = 0; i < 10; i++) {
        expTokens[i] = 0;
    }
}

int findExpTokens(const char *msg) {
    int addr = 0;
    char * expecting = NULL;
    expecting = strstr(msg, ", expecting ");
    if(expecting == NULL) {
        return 0;
    }
    if(strstr(expecting, "ID")) {
        expTokens[addr] = ID;
        addr++;
    }
    if(strstr(expecting, "NUMCONST")) {
        expTokens[addr] = NUMCONST;
        addr++;
    }
    if(strstr(expecting, "CHARCONST")) {
        expTokens[addr] = CHARCONST;
        addr++;
    }
    if(strstr(expecting, "BOOLCONST")) {
        expTokens[addr] = BOOLCONST;
        addr++;
    }
    if(strstr(expecting, "ytbool")) {
        expTokens[addr] = ytbool;
        addr++;
    }
    if(strstr(expecting, "ytchar")) {
        expTokens[addr] = ytchar;
        addr++;
    }
    if(strstr(expecting, "ytint")) {
        expTokens[addr] = ytint;
        addr++;
    }
    if(strstr(expecting, "ytequals")) {
        expTokens[addr] = ytequals;
        addr++;
    }
    if(strstr(expecting, "ytdo")) {
        expTokens[addr] = ytdo;
        addr++;
    }
    if(strstr(expecting, "ytor")) {
        expTokens[addr] = ytor;
        addr++;
    }
    if(strstr(expecting, "ytto")) {
        expTokens[addr] = ytto;
        addr++;
    }
    if(strstr(expecting, "ytthen")) {
        expTokens[addr] = ytthen;
        addr++;
    }
    if(strstr(expecting, "ytcompound")) {
        expTokens[addr] = ytcompound;
        addr++;
    }
    if(strstr(expecting, "\'\"\'")) {
        expTokens[addr] = '\"';
        addr++;
    }
    if(strstr(expecting, "\'\'\'")) {
        expTokens[addr] = '\'';
        addr++;
    }
    if(strstr(expecting, "\'(\'")) {
        expTokens[addr] = '(';
        addr++;
    }
    if(strstr(expecting, "\')\'")) {
        expTokens[addr] = ')';
        addr++;
    }
    if(strstr(expecting, "\']\'")) {
        expTokens[addr] = ']';
        addr++;
    }
    if(strstr(expecting, "\',\'")) {
        expTokens[addr] = ',';
        addr++;
    }
    if(strstr(expecting, "\';\'")) {
        expTokens[addr] = ';';
        addr++;
    }
    return addr;
}

void getExpecting(char *expString, int expCount) {
    strcat(expString, ytToString(expTokens[0]));
    for(int i = 1; i < expCount; i++) {
        strcat(expString, " or ");
        strcat(expString, ytToString(expTokens[i]));
    }
}

char * ytToString(int yToken) {
    switch(yToken) {
        case ID:
            return "identifier";
        case NUMCONST:
            return "numeric constant";
        case CHARCONST:
            return "unfinished constant";
        case BOOLCONST:
            return "unfinished constant";
        case ytbool:
            return "\"bool\"";
        case ytchar:
            return "\"char\"";
        case ytint:
            return "\"int\"";
        case ytequals:
            return "\'=\'";
        case ytdo:
            return "\"do\"";
        case ytor:
            return "\"or\"";
        case ytto:
            return "\"to\"";
        case ytthen:
            return "\"then\"";
        case ytcompound:
            return "\')\'";
        case '\"':
            return "\'\"\'";
        case '\'':
            return "\'\'\'";
        case '(':
            return "\'(\'";
        case ')':
            return "\')\'";
        case ']':
            return "\']\'";
        case ',':
            return "\',\'";
        case ';':
            return "\';\'";
    }
}

int isBasic(int tokenClass) {
    if(
        tokenClass == ytequals ||
        tokenClass == ytadd ||
        tokenClass == ytsub ||
        tokenClass == ytmul ||
        tokenClass == ytdiv ||
        tokenClass == ytmod ||
        tokenClass == ytlesser||
        tokenClass == ytgreater ||
        tokenClass == ytcompound ||
        tokenClass == ytarr
    ) {
        return 1;
    } else {
        return 0;
    }
}

int isBasicString(int tokenClass) {
    if(
        tokenClass == ytint ||
        tokenClass == ytbool ||
        tokenClass == ytchar ||
        tokenClass == ytstatic ||
        tokenClass == ytassadd ||
        tokenClass == ytasssub ||
        tokenClass == ytassmul ||
        tokenClass == ytassdiv ||
        tokenClass == ytinc ||
        tokenClass == ytdec ||
        tokenClass == yteq ||
        tokenClass == ytnoteq ||
        tokenClass == yteqlesser ||
        tokenClass == yteqgreater ||
        tokenClass == ytif ||
        tokenClass == ytelse ||
        tokenClass == ytwhile ||
        tokenClass == ytdo ||
        tokenClass == ytthen ||
        tokenClass == ytand ||
        tokenClass == ytor ||
        tokenClass == ytto ||
        tokenClass == ytby ||
        tokenClass == ytbreak ||
        tokenClass == ytreturn
    ) {
        return 1;
    } else {
        return 0;
    }
}