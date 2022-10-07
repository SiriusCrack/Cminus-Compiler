#include "SymbolTable.h"
#include "ASTNode.h"
#include <stdio.h>

ScopeTable * NewScope (Node * node) {
    ScopeTable * newScope = (ScopeTable *) malloc(sizeof(ScopeTable));
    if(newScope == NULL) {
        printf("New scope out of memory\n");
        return NULL;
    } else {
        int i;
        for(i = 0; i < MAX_CHILDREN; i++) {
            newScope->child[i] = NULL;
        }
        newScope->scopeName = node->literal;
        newScope->symbolTable = NULL;
        return newScope;
    }
}

SymbolTableEntry * NewEntry (Node * node) {
    SymbolTableEntry * newEntry = (SymbolTableEntry *) malloc(sizeof(ScopeTable));
    if(newEntry == NULL) {
        printf("New entry out of memory\n");
        return NULL;
    } else {
        newEntry->next = NULL;
        newEntry->nodeName = node->literal;
        newEntry->node = node;
        return newEntry;
    }
}