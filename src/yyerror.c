// Known Errors
// yyerror should be giving me "expecting bool chat int" etc for first error sommetimes, but doesnt
// yyerror returns "expecting ')'" sometimes instead of "expecting '}'"
// relops arent working

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
int isBasic(int tokenClass);
int isBasicString(int tokenClass);

void yyerror(const char *msg) {
    printf("%s\n", msg);
    char * expecting = NULL;
    if(strstr(msg, "syntax error, unexpected '('")) {
        expecting = getExpecting(msg);
        if(expecting) {
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
        expecting = getExpecting(msg);
        if(expecting) {
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
    } else if(strstr(msg, "syntax error, unexpected ']'")) {
        expecting = getExpecting(msg);
        if(expecting) {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ']', expecting %s.\n",
                line,
                expecting
            );
        } else {
            errs++;
            printf(
                "ERROR(%d): Syntax error, unexpected ']'.\n",
                line
            );
        }
    } else if(strstr(msg, "syntax error, unexpected '}'")) {
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
    } else if(lastToken->tokenClass == CHARCONST) {
        expecting = getExpecting(msg);
        if(expecting) {
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
        result = strstr(expecting, "NUMCONST");
        if(result != NULL) {
            expecting = "numeric constant";
            return expecting;
        }
        result = strstr(expecting, "CHARCONST");
        if(result != NULL) {
            expecting = "unfinished constant";
            return expecting;
        }
        result = strstr(expecting, "STRINGCONST");
        if(result != NULL) {
            expecting = "unfinished constant";
            return expecting;
        }
        result = strstr(expecting, "BOOLCONST");
        if(result != NULL) {
            expecting = "unfinished constant";
            return expecting;
        }
        result = strstr(expecting, "ytint");
        if(result != NULL) {
            expecting = "\"int\"";
            return expecting;
        }
        result = strstr(expecting, "ytbool");
        if(result != NULL) {
            expecting = "\"bool\"";
            return expecting;
        }
        result = strstr(expecting, "ytchar");
        if(result != NULL) {
            expecting = "\"char\"";
            return expecting;
        }
        result = strstr(expecting, "ytequals");
        if(result != NULL) {
            expecting = "\'=\'";
            return expecting;
        }
        result = strstr(expecting, "ytdo");
        if(result != NULL) {
            expecting = "\"do\"";
            return expecting;
        }
        result = strstr(expecting, "ytor");
        if(result != NULL) {
            expecting = "\"or\"";
            return expecting;
        }
        result = strstr(expecting, "ytcompound");
        if(result != NULL) {
            expecting = "\')\'";
            return expecting;
        }
    }
    return expecting;
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
        tokenClass == ytcompound
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
        tokenClass == ytreturn ||
        tokenClass == ytarr
    ) {
        return 1;
    } else {
        return 0;
    }
}