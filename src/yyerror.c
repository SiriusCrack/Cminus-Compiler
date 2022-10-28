#include "yyerror.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Token * lastToken;
extern int errs;
extern int warns;

char * getExpecting(const char *msg);
int isBasic(yytoken_kind_t tokenClass);

void yyerror(const char *msg) {
    if(lastToken->tokenClass == ID) {
        char * expecting = getExpecting(msg);
        errs++;
        printf(
            "ERROR(%d): Syntax error, unexpected identifier \"%s\", expecting %s.\n",
            lastToken->lineNum,
            lastToken->literal,
            expecting
        );
    } else if(isBasic(lastToken->tokenClass)) {
        errs++;
        printf(
            "ERROR(%d): Syntax error, unexpected '%s'.\n",
            lastToken->lineNum,
            lastToken->literal
        );
    } else {
        printf("%d\n", lastToken->tokenClass);
    }
}

char * getExpecting(const char *msg) {
    char * expecting = strstr(msg, ", expecting ");
    if(expecting != NULL) {
        char * result = strstr(expecting, "\"");
        if(result == NULL) {
            result = strstr(expecting, "\'");
        }
        expecting = result;
    }
    return expecting;
}

int isBasic(yytoken_kind_t tokenClass) {
    if(
        tokenClass == ytequals
    ) {
        return 1;
    } else {
        return 0;
    }
}