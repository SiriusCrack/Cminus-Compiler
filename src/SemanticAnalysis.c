#include "SemanticAnalysis.h"
#include <stdio.h>

extern Node * AST;
extern ScopeTable * SymbolTable;

DataType OpHandler (Node * tree, ScopeTable * table);
DataType UnaryHandler (Node * tree, ScopeTable * table);
DataType ArrHandler (Node * tree, ScopeTable * table);
DataType ConstHandler (Node * tree, ScopeTable * table);
int IsScope (Node * node);
int IsUnary (Node * node);

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
    if(tree->nodeType == ntOp || tree->nodeType == ntArrAd) {
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
    DataType dataTypeChildren[2] = {unknown, unknown};
    int i;
    for(i = 0; i < 2; i++) {
        if(tree->child[i]->nodeType == ntOp || tree->child[i]->nodeType == ntArrAd) {
            dataTypeChildren[i] = OpHandler(tree->child[i], table);
        } else if(IsUnary(tree->child[i])) {
            return UnaryHandler(tree->child[i], table);
        } else if(tree->child[i]->nodeType == ntID) {
            SymbolTableEntry *newEntry = NewEntry(tree->child[i]);
            AddEntryToScope(newEntry, table);
            dataTypeChildren[i] = newEntry->following->node->dataType;
        } else {
            dataTypeChildren[i] = ConstHandler(tree->child[i], table);
        }
    }
    if(dataTypeChildren[0] == dataTypeChildren[1]) {
        printf("good beans\n");
        return dataTypeChildren[0];
    } else {
        printf("%d %s doesnt match %d %s\n", dataTypeChildren[0], tree->child[0]->literal, dataTypeChildren[1], tree->child[1]->literal);
        return dataTypeChildren[0];
    }
}

DataType UnaryHandler (Node * tree, ScopeTable * table) {
    if(tree->child[0]->nodeType == ntOp || tree->child[0]->nodeType == ntArrAd) {
        return OpHandler(tree->child[0], table);
    } else if(IsUnary(tree->child[0])) { // is this possible??
        return UnaryHandler(tree->child[0], table);
    } else if(tree->child[0]->nodeType == ntID) {
        SymbolTableEntry *newEntry = NewEntry(tree->child[0]);
        AddEntryToScope(newEntry, table);
        return newEntry->following->node->dataType;
    } else {
        return ConstHandler(tree->child[0], table);
    }
}

DataType ArrHandler (Node * tree, ScopeTable * table) {

}

DataType ConstHandler (Node * tree, ScopeTable * table) {
    switch (tree->nodeType) {
        case ntNumConst:
            return intData;
            break;
        case ntCharConst:
            return charData;
            break;
        case ntStringConst:
            printf("what do I do with this??\n");
            break;
        case ntBoolConst:
            return boolData;
            break;
        default:
            printf("%s\n", tree->literal);
            break;
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

int IsUnary (Node * node) {
    if(
        node->nodeType == ntSignOp ||
        node->nodeType == ntSizeofOp ||
        node->nodeType == ntQuestOp
    ) {
        return 1;
    } else {
        return 0;
    }
}