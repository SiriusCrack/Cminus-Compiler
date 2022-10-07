#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include "ASTNode.h"

#define SCOPE_MAX_CHILDREN 10

typedef struct SymbolTableEntry SymbolTableEntry;
struct SymbolTableEntry {
    // Connections
    SymbolTableEntry * next; // pointer to the next entry in this vector

    // Data
    char * nodeName; // node literal for this declaration
    Node * node; // pointer to the declaration node on the tree
};

SymbolTableEntry * NewEntry (Node * node);

typedef struct ScopeTable ScopeTable;
struct ScopeTable {
    // Connections
    ScopeTable * child[SCOPE_MAX_CHILDREN]; // pointers to nested scopes

    // Info
    char * scopeName; // name of this scope
    int depth;
    SymbolTableEntry * symbolTable; //pointer to the vector of symbols in this scope
    int debugFlag;
};

ScopeTable * NewGlobalScope ();
ScopeTable * NewScope (Node * node);
void AddChildScope (ScopeTable * parentScopeTable, ScopeTable * newScopeTable);
void PrintSymbolTable (ScopeTable * symbolTable);

#endif