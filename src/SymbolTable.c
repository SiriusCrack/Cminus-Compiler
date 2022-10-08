#include "ASTNode.h"
#include "SymbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ScopeTable * NewGlobalScope () {
    ScopeTable * newScope = (ScopeTable *) malloc(sizeof(ScopeTable));
    if(newScope == NULL) {
        printf("New scope out of memory\n");
        return NULL;
    } else {
        int i;
        for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
            newScope->child[i] = NULL;
        }
        newScope->scopeName = strdup("Global");
        newScope->symbolTable = NULL;
        return newScope;
    }
}

ScopeTable * NewScope (Node * node) {
    ScopeTable * newScope = (ScopeTable *) malloc(sizeof(ScopeTable));
    if(newScope == NULL) {
        printf("New scope out of memory\n");
        return NULL;
    } else {
        int i;
        for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
            newScope->child[i] = NULL;
        }
        newScope->scopeName = node->literal;
        newScope->symbolTable = NULL;
        return newScope;
    }
}

void AddChildScope (ScopeTable * parentScopeTable, ScopeTable * newScopeTable) {
    int i;
    for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
        if(parentScopeTable->child[i] != NULL) {
            continue;
        } else {
            parentScopeTable->child[i] = newScopeTable;
            newScopeTable->depth = parentScopeTable->depth+1;
            break;
        }
    }
}

void PrintSymbolTable (ScopeTable * symbolTable) {
    int i;
    for(i = 0; i < symbolTable->depth; i++) {
        printf(".\t");
    }
    printf("%d: %s\n", symbolTable->depth, symbolTable->scopeName);
    for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
        if(symbolTable->child[i] != NULL) {
            PrintSymbolTable(symbolTable->child[i]);
        }
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