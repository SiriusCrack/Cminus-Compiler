#include "yyerror.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Token * lastToken;
extern int errs;
extern int warns;
extern int line;

char * getExpecting(const char *msg);
int isBasic(yytoken_kind_t tokenClass);
int isBasicString(yytoken_kind_t tokenClass);

void yyerror(const char *msg) {
    // printf("%s\n", msg);
    char * expecting = NULL;
    if(strstr(msg, "syntax error, unexpected '}'")) {
        expecting = getExpecting(msg);
        if(expecting) {
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
        expecting = getExpecting(msg);
        if(expecting) {
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
        expecting = getExpecting(msg);
        if(expecting) {
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
        expecting = getExpecting(msg);
        if(expecting) {
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
        expecting = getExpecting(msg);
        if(expecting) {
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
        expecting = getExpecting(msg);
        if(expecting) {
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
        expecting = getExpecting(msg);
        if(expecting) {
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
        expecting = getExpecting(msg);
        if(expecting) {
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
    } else if(isBasic(lastToken->tokenClass)) {
        expecting = getExpecting(msg);
        if(expecting) {
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
        expecting = getExpecting(msg);
        if(expecting) {
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

char * getExpecting(const char *msg) {
    char * expecting = strstr(msg, ", expecting ");
    if(expecting != NULL) {
        char * result = NULL;
        result = strstr(expecting, "\"");
        if(result != NULL) {
            expecting = result;
            return expecting;
        }
        result = strstr(expecting, "\'");
        if(result != NULL) {
            expecting = result;
            return expecting;
        }
        result = strstr(expecting, "ID");
        if(result != NULL) {
            expecting = "identifier";
            return expecting;
        }
    }
    return expecting;
}

int isBasic(yytoken_kind_t tokenClass) {
    if(
        tokenClass == ytequals ||
        tokenClass == ytadd ||
        tokenClass == ytcompound
    ) {
        return 1;
    } else {
        return 0;
    }
}

int isBasicString(yytoken_kind_t tokenClass) {
    if(
        tokenClass == ytelse ||
        tokenClass == ytif ||
        tokenClass == ytwhile ||
        tokenClass == ytint ||
        tokenClass == ytinc
    ) {
        return 1;
    } else {
        return 0;
    }
}