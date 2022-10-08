#include "SemanticAnalysis.h"
#include <stdio.h>

extern Node * AST;
extern ScopeTable * SymbolTable;

void WriteScopes (Node * tree, ScopeTable * table) {
    ScopeTable * newScope = table;
    if(tree->nodeType == ntFunc || tree->nodeType == ntCompound) {
        newScope = NewScope(tree);
        AddChildScope(table, newScope);
    }
    int i;
    for(i = 0; i < AST_MAX_CHILDREN; i++) {
        if(tree->child[i] != NULL) {
            WriteScopes(tree->child[i], newScope);
        }
    }
    if(tree->sibling != NULL) {
        WriteScopes(tree->sibling, table);
    }
}