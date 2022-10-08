#include "ASTNode.h"
#include "SymbolTable.h"
#include "SemanticAnalysis.h"
#include "parser.tab.h"
#include <stdio.h>

extern FILE * yyin;
extern int yydebug;
Node * AST;
ScopeTable * SymbolTable;

int PrintDebugFlag;
int PrintTreeFlag;

void parseArgs (int, char * []);

int main (int argc, char * argv[]) {
    PrintDebugFlag = 0;
    PrintTreeFlag = 0;
    if(argc > 1) {
        parseArgs(argc, argv);
    }
    SymbolTable = NewGlobalScope();
    yyparse();
    PrintTree(AST, 0);
    WriteScopes (AST, SymbolTable);
    PrintSymbolTable(SymbolTable);
    return 0;
}

void parseArgs (int argc, char * argv[]) {
    FILE * fp = fopen(argv[argc-1], "r");
    if(fp) {
        yyin = fp;
    } else {
        printf("Need file to parse.\n");
    }
    int i;
    for(i = 1; i < argc-1; i++) {
        switch (argv[i][1]) {
            case 'd':
                yydebug = 1;
                break;
            case 'D':
                break;
            case 'h':
                printf("usage: -c [options] [sourcefile]\n");
                printf("options:\n");
                printf("-d \t- turn on parser debugging\n");
                printf("-D \t- turn on symbol table debugging\n");
                printf("-h \t- print this usage message\n");
                printf("-p \t- print the abstract syntax tree\n");
                printf("-P \t- print the abstract syntax tree plus type information\n");
                break;
            case 'p':
                PrintTreeFlag = 1;
                break;
            case 'P':
                break;
            case 'Z':
                PrintDebugFlag = 1;
                break;
            default:
                printf("\"-%s\" is not a recognized argument.", argv[i]);
                break;
        }
    }
}