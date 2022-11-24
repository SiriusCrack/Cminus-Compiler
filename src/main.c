#include "parser.tab.h"
#include <stdio.h>

extern FILE *yyin;

void parseArguments (int argc, char *argv[]);

int main(int argc, char *argv[]) {
    if(argc > 1) parseArguments(argc, argv);
    yyparse();
    return 0;
}

void parseArguments(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    if(fp) {
        yyin = fp;
    } else {
        printf("unable to open file \"%s\"", argv[argc-1]);
    }
}