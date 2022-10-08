#include "SemanticAnalysis.h"
#include <stdio.h>

extern Node * AST;
extern ScopeTable * SymbolTable;

void WriteScopes (Node * tree, ScopeTable * table) {
    if(tree->nodeType == ntFunc) {
        ScopeTable * newScope = NewScope(tree);
        AddChildScope(table, newScope);
        table = newScope;
    }
    int i;
    for(i = 0; i < AST_MAX_CHILDREN; i++) {
        if(tree->child[i] != NULL) {
            WriteScopes(tree->child[i], table);
        }
    }
}