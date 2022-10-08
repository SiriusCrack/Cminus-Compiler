#include "ASTNode.h"
#include "SymbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int PrintSymTblFlag;

ScopeTable * NewGlobalScope () {
    ScopeTable * newScope = (ScopeTable *) malloc(sizeof(ScopeTable));
    if(newScope == NULL) {
        printf("New scope out of memory\n");
        return NULL;
    } else {
        newScope->parent = NULL;
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
        newScope->parent = NULL;
        int i;
        for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
            newScope->child[i] = NULL;
        }
        newScope->scopeName = node->literal;
        newScope->lineNum = node->lineNum;
        newScope->symbolTable = NULL;
        return newScope;
    }
}

ScopeTable * GetMatchingChildScope (ScopeTable * scopeTable, int lineNum) {
    int i;
    for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
        if(scopeTable->child[i]->lineNum == lineNum) {
            printf("enter child with ln%d\n", lineNum);
            return scopeTable->child[i];
        }
    }
    printf("child with ln%d not found\n", lineNum);
    return NULL;
}

void AddChildScope (ScopeTable * parentScopeTable, ScopeTable * newScopeTable) {
    newScopeTable->parent = parentScopeTable;
    int i;
    for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
        if(parentScopeTable->child[i] == NULL) {
            parentScopeTable->child[i] = newScopeTable;
            newScopeTable->depth = parentScopeTable->depth+1;
            return;
        }
    }
}

void PrintSymbolTable (ScopeTable * symbolTable) {
    if(PrintSymTblFlag == 0) return;
    int i;
    for(i = 0; i < symbolTable->depth; i++) {
        printf(".\t");
    }
    printf("%d: %s\n", symbolTable->depth, symbolTable->scopeName);
    SymbolTableEntry * cur = symbolTable->symbolTable;
    while(cur != NULL) {
        for(i = 0; i < symbolTable->depth; i++) {
            printf(".\t");
        }
        printf(" ");
        printf("entry %d: %s\n", cur->node->isDecl, cur->node->literal);
        cur = cur->next;
    }
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
        newEntry->isDecl = node->isDecl;
        return newEntry;
    }
}

void AddEntryToScope (SymbolTableEntry * entry, ScopeTable * scope) {
    if(scope->symbolTable == NULL) {
        scope->symbolTable = entry;
    } else {
        SymbolTableEntry * cur = scope->symbolTable;
        while(1) { // removed duplicate check. should probably rework
            if(cur->next != NULL) {
                cur = cur->next;
            } else {
                cur->next = entry;
                break;
            }
        }
    }
}