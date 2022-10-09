#include "SemanticAnalysis.h"
#include <stdio.h>

extern Node * AST;
extern ScopeTable * SymbolTable;

int IsScope (Node * node);

void WriteScopes (Node * tree, ScopeTable * table) {
    // Action
    ScopeTable * newScope = table;
    if(IsScope(tree)) {
        newScope = NewScope(tree);
        AddChildScope(table, newScope);
    } else if(tree->isDecl) {
        SymbolTableEntry * newEntry = NewEntry(tree);
        AddEntryToScope(newEntry, newScope);
    }
    // Traversal
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

void WriteRefs (Node * tree, ScopeTable * table) {
    ScopeTable * newScope = table;
    if(IsScope(tree)) {
        newScope = GetMatchingChildScope(newScope, tree->UID);
    }
    // Action
    if(tree->nodeType == ntID) {
        SymbolTableEntry * newEntry = NewEntry(tree);
        AddEntryToScope(newEntry, newScope);
    }
    // Traversal
    int i;
    for(i = 0; i < AST_MAX_CHILDREN; i++) {
        if(tree->child[i] != NULL) {
            WriteRefs(tree->child[i], newScope);
        }
    }
    if(tree->sibling != NULL) {
        WriteRefs(tree->sibling, table);
    }
}

int IsScope (Node * node) {
    if(
        node->nodeType == ntCompound
        || node->nodeType == ntFunc
        || node->nodeType == ntIterwComp
        || node->nodeType == ntTowComp
    ) {
        return 1;
    } else {
        return 0;
    }
}