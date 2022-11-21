#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include "ASTNode.h"

#define SCOPE_MAX_CHILDREN 24
#define ENTRY_MAX_FOLLOWERS 24

typedef struct Node Node;

typedef struct SymbolTableEntry SymbolTableEntry;
typedef struct ScopeTable ScopeTable;

struct SymbolTableEntry {
    // Connections
    ScopeTable * scope; // pointer to this entry's scope
    SymbolTableEntry * next; // pointer to the next entry in this vector

    // Data
    Node * node; // pointer to the entry's node on the tree
    SymbolTableEntry * following;
    SymbolTableEntry * followers[ENTRY_MAX_FOLLOWERS];
    int isDecl;
};

struct ScopeTable {
    // Connections
    ScopeTable * parent;
    ScopeTable * child[SCOPE_MAX_CHILDREN]; // pointers to nested scopes

    // Info
    char * scopeName; // name of this scope
    int depth;
    int isGlobal;
    int isIO;
    SymbolTableEntry * self;
    SymbolTableEntry * symbolTable; //pointer to the vector of symbols in this scope
};

ScopeTable * NewGlobalScope ();
ScopeTable * NewScope (Node * node);
ScopeTable * GetMatchingChildScope (ScopeTable * scopeTable, int nodeUID);
void AddChildScope (ScopeTable * parentScopeTable, ScopeTable * newScopeTable);
void PrintSymbolTable (ScopeTable * symbolTable);

SymbolTableEntry * NewEntry (Node * node);
int AddEntryToScope (SymbolTableEntry * entry, ScopeTable * scope);
SymbolTableEntry * FindDecl (SymbolTableEntry * entry, ScopeTable * scope);
SymbolTableEntry * FindFuncDecl (SymbolTableEntry *entry, ScopeTable *scope);
SymbolTableEntry * FindReDecl(SymbolTableEntry * entry, ScopeTable * scope);
SymbolTableEntry * FindLoop (ScopeTable * scope);
SymbolTableEntry * FindMyFunc (ScopeTable * scope);

#endif