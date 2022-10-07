#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include "ASTNode.h"

#define MAX_CHILDREN 10

typedef struct SymbolTableEntry SymbolTableEntry;
struct SymbolTableEntry {
    // Connections
    SymbolTableEntry * next; // pointer to the next entry in this vector

    // Data
    char * nodeName; // node literal for this declaration
    Node * node; // pointer to the declaration node on the tree
};

typedef struct ScopeTable ScopeTable;
struct ScopeTable {
    // Connections
    ScopeTable * child[MAX_CHILDREN]; // pointers to nested scopes

    // Info
    char * scopeName; // name of this scope
    SymbolTableEntry * symbolTable; //pointer to the vector of symbols in this scope
    int debugFlag;
};

ScopeTable * NewScope (Node * node);
SymbolTableEntry * NewEntry (Node * node);

#endif