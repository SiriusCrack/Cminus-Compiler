#include "SemanticAnalysis.h"
#include <stdio.h>

extern Node * AST;
extern ScopeTable * SymbolTable;

DataType OpHandler (Node * tree, ScopeTable * table);
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
    if(tree->nodeType == ntOp) {
        OpHandler(tree, newScope);
    } else {
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
    }
    if(tree->sibling != NULL) {
        WriteRefs(tree->sibling, table);
    }
}

DataType OpHandler (Node * tree, ScopeTable * table) {
    DataType dataTypeChildren[2] = { 0, 0 };
    int i;
    for(i = 0; i < 2; i++) {
        if(tree->child[i]->nodeType == ntOp) {
            dataTypeChildren[i] = OpHandler(tree->child[i], table);
        } else if(tree->child[i]->nodeType == ntID) {
            SymbolTableEntry *newEntry = NewEntry(tree->child[i]);
            AddEntryToScope(newEntry, table);
            dataTypeChildren[i] = newEntry->following->node->dataType;
        } else {
            switch (tree->child[i]->nodeType) {
                case ntNumConst:
                    dataTypeChildren[i] = intData;
                    break;
                case ntCharConst:
                    dataTypeChildren[i] = charData;
                    break;
                case ntStringConst:
                    printf("what do I do with this??\n");
                    break;
                case ntBoolConst:
                    dataTypeChildren[i] = boolData;
                    break;
                default:
                    printf("AAAUUAAUUAAUUGGHHH\n");
                    break;
            }
        }
    }
    if(dataTypeChildren[0] == dataTypeChildren[1]) {
        printf("good beans\n");
        return dataTypeChildren[0];
    } else {
        printf("%d %s doesnt match %d %s\n", dataTypeChildren[0], tree->child[0]->literal, dataTypeChildren[1], tree->child[1]->literal);
        return unknown;
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