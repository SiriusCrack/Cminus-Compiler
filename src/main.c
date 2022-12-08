#include "ASTNode.h"
#include "SymbolTable.h"
#include "SemanticAnalysis.h"
#include "IOLoader.h"
#include "Placement.h"
#include "codegen.h"
#include "parser.tab.h"
#include <stdio.h>

extern FILE * yyin;
extern int yydebug;

Node * AST;
Node * IOTree;
ScopeTable * SymbolTable;
FILE * code;

int NodeUID;
int goffset;
int foffset;

int PrintDebugFlag;
int PrintTreeFlag;
int PrintAnnotatedTreeFlag;
int PrintPlacementTreeFlag;
int PrintSymTblFlag;
int warns;
int errs;

void parseArgs (int, char * []);

int main (int argc, char * argv[]) {
    NodeUID = 0;
    goffset = 0;
    foffset = 0;
    PrintDebugFlag = 0;
    PrintTreeFlag = 0;
    PrintAnnotatedTreeFlag = 0;
    PrintPlacementTreeFlag = 0;
    PrintSymTblFlag = 0;
    warns = 0;
    errs = 0;
    if(argc > 1) {
        parseArgs(argc, argv);
    }
    if(yyin != NULL) {
        SymbolTable = NewGlobalScope();
        AST = LoadIO();
        yyparse();
        PrintTree(AST, 0);
        if(errs < 1) {
            WriteScopes(AST, SymbolTable);
            if(AST != NULL) CheckMain(SymbolTable);
            WriteRefs(AST, SymbolTable);
            CheckUse(SymbolTable);
            Placement();
        }
        PrintSymbolTable(SymbolTable);
        if(errs < 1) PrintAnnotatedTree(AST, 0);
        if(errs < 1) PrintPlacementTree(AST, 0);
        if(errs < 1) if(PrintPlacementTreeFlag) printf("Offset for end of global space: %d\n", goffset);
    }
    // WalkAST(AST);
    printf("Number of warnings: %d\n", warns);
    printf("Number of errors: %d\n", errs);
    return 0;
}

void parseArgs (int argc, char * argv[]) {
    FILE * fp = fopen(argv[argc-1], "r");
    code = fopen("out.tm", "w+");
    if(fp) {
        yyin = fp;
    } else {
        errs = errs + 1;
        printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[argc-1]);
    }
    int i;
    for(i = 1; i < argc-1; i++) {
        switch (argv[i][1]) {
            case 'h':
                printf("usage: c- [options] [sourcefile]\n");
                printf("options:\n");
                printf("-d \t- turn on parser debugging\n");
                printf("-D \t- turn on symbol table debugging\n");
                printf("-h \t- print this usage message\n");
                printf("-p \t- print the abstract syntax tree\n");
                printf("-P \t- print the abstract syntax tree plus type information\n");
                printf("-M \t- print scope/size/location information\n");
                break;
            case 'd':
                yydebug = 1;
                break;
            case 'D':
                break;
            case 'p':
                PrintTreeFlag = 1;
                break;
            case 'P':
                PrintAnnotatedTreeFlag = 1;
                break;
            case 'M':
                PrintPlacementTreeFlag = 1;
                break;
            case 'T':
                PrintSymTblFlag = 1;
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