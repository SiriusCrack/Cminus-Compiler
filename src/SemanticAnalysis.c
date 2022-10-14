#include "SemanticAnalysis.h"
#include <stdio.h>
#include <string.h>

extern Node * AST;
extern ScopeTable * SymbolTable;
extern int warns;
extern int errs;

DataType CmpHandler (Node * tree, ScopeTable * table);
DataType UnaryCmpHandler (Node * tree, ScopeTable * table);
DataType RelOpHandler (Node * tree, ScopeTable * table);
DataType OpHandler (Node * tree, ScopeTable * table);
DataType UnaryHandler (Node * tree, ScopeTable * table);
DataType ConstHandler (Node * tree, ScopeTable * table);
char * DataTypeToString (DataType dataType);
int IsScope (Node * node);
int IsUnary (Node * node);

void WriteScopes (Node * node, ScopeTable * table) {
    // Action
    ScopeTable * newScope = table;
    if(IsScope(node)) { // add scope table
        newScope = NewScope(node);
        AddChildScope(table, newScope);
    } else if(node->isDecl) { // add declaration to this scope table
        SymbolTableEntry * newEntry = NewEntry(node);
        AddEntryToScope(newEntry, newScope);
    }
    // Traversal
    int i;
    for(i = 0; i < AST_MAX_CHILDREN; i++) {
        if(node->child[i] != NULL) {
            WriteScopes(node->child[i], newScope);
        }
    }
    if(node->sibling != NULL) {
        WriteScopes(node->sibling, table);
    }
}

void WriteRefs (Node * tree, ScopeTable * table) {
    ScopeTable * newScope = table;
    if(IsScope(tree)) {
        newScope = GetMatchingChildScope(newScope, tree->UID);
    }
    // Action
    if(tree->nodeType == ntOp || tree->nodeType == ntTrueAssign) {
        OpHandler(tree, newScope);
    } else if(tree->nodeType == ntOrOp || tree->nodeType == ntAndOp) {
        CmpHandler(tree, newScope);
    } else {
        if(tree->nodeType == ntID || tree->nodeType == ntCall) {
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

void CheckMain (ScopeTable *table) {
    int i = 0;
    for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
        if(table->child[i] != NULL) {
            if(strcmp("main", table->child[i]->scopeName) == 0) {
                return;
            }
        } else {
            break;
        }
    }
    printf("ERROR(LINKER): A function named 'main()' must be defined.\n");
}

void CheckUse (ScopeTable *table) {
    int i = 0;
    SymbolTableEntry *cur = table->symbolTable;
    while(cur != NULL) {
        if(cur->isDecl) {
            if(cur->followers[0] == NULL) {
                printf(
                    "WARNING(%d): The variable '%s' seems not to be used.\n",
                    cur->node->lineNum,
                    cur->node->literal
                );
            }
        }
        i = i + 1;
        cur = cur->next;
    }
    for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
        if(table->child[i] != NULL) {
            CheckUse(table->child[i]);
        } else {
            break;
        }
    }
}

DataType CmpHandler (Node * tree, ScopeTable * table) {
    DataType dataTypeChildren[2] = {unknown, unknown};
    int i;
    for(i = 0; i < 2; i++) {
        if(tree->child[i]->nodeType == ntRelOp) {
            dataTypeChildren[i] = RelOpHandler(tree->child[i], table);
        } else if(tree->child[i]->nodeType == ntOrOp || tree->child[i]->nodeType == ntAndOp) {
            dataTypeChildren[i] = CmpHandler(tree->child[i], table);
        } else if(tree->child[i]->nodeType == ntOp || tree->child[i]->nodeType == ntTrueAssign) {
            dataTypeChildren[i] = OpHandler(tree->child[i], table);
        } else if(IsUnary(tree->child[i])) {
            dataTypeChildren[i] = UnaryHandler(tree->child[i], table);
        } else if(tree->child[i]->nodeType == ntNotOp) {
            dataTypeChildren[i] = UnaryCmpHandler(tree->child[i], table);
        } else if (tree->child[i]->nodeType == ntID || tree->child[i]->nodeType == ntCall) {
            SymbolTableEntry *newEntry = NewEntry(tree->child[0]);
            if(AddEntryToScope(newEntry, table)) {
                dataTypeChildren[i] = newEntry->following->node->dataType;
            }
        } else {
            dataTypeChildren[i] = ConstHandler(tree->child[i], table);
        }
    }
    if(dataTypeChildren[0] == dataTypeChildren[1]) {
        return boolData;
    } else {
        printf("%d %s doesnt match %d %s\n", dataTypeChildren[0], tree->child[0]->literal, dataTypeChildren[1], tree->child[1]->literal);
        return dataTypeChildren[0];
    }
}

DataType UnaryCmpHandler (Node * tree, ScopeTable * table) {
    if(tree->child[0]->nodeType == ntOp || tree->child[0]->nodeType == ntTrueAssign) {
        return OpHandler(tree->child[0], table);
    } else if(IsUnary(tree->child[0])) { // is this possible??
        return UnaryHandler(tree->child[0], table);
    } else if(tree->child[0]->nodeType == ntID || tree->child[0]->nodeType == ntCall) {
        SymbolTableEntry *newEntry = NewEntry(tree->child[0]);
        if(AddEntryToScope(newEntry, table)) {
            return newEntry->following->node->dataType;
        }
    } else {
        return boolData;
    }
}

DataType RelOpHandler (Node * tree, ScopeTable * table) {
    DataType dataTypeChildren[2] = {unknown, unknown};
    int i;
    for(i = 0; i < 2; i++) {
        if(tree->child[i]->nodeType == ntOp || tree->child[i]->nodeType == ntTrueAssign) {
            dataTypeChildren[i] = OpHandler(tree->child[i], table);
        } else if(IsUnary(tree->child[i])) {
            dataTypeChildren[i] = UnaryHandler(tree->child[i], table);
        } else if(tree->child[i]->nodeType == ntID || tree->child[i]->nodeType == ntCall) {
            SymbolTableEntry *newEntry = NewEntry(tree->child[i]);
            if(AddEntryToScope(newEntry, table)) {
                dataTypeChildren[i] = newEntry->following->node->dataType;
            }
        } else {
            dataTypeChildren[i] = ConstHandler(tree->child[i], table);
        }
    }
    if(dataTypeChildren[0] == dataTypeChildren[1]) {
        return boolData;
    } else {
        printf("%d %s doesnt match %d %s\n", dataTypeChildren[0], tree->child[0]->literal, dataTypeChildren[1], tree->child[1]->literal);
        return dataTypeChildren[0];
    }
}

DataType OpHandler (Node * tree, ScopeTable * table) {
    DataType dataTypeChildren[2] = {unknown, unknown};
    int i;
    for(i = 0; i < 2; i++) {
        if(tree->child[i]->nodeType == ntRelOp) {
            dataTypeChildren[i] = RelOpHandler(tree->child[i], table);
        } else if(tree->child[i]->nodeType == ntOp || tree->child[i]->nodeType == ntTrueAssign) {
            dataTypeChildren[i] = OpHandler(tree->child[i], table);
        } else if(IsUnary(tree->child[i])) {
            dataTypeChildren[i] = UnaryHandler(tree->child[i], table);
        } else if(tree->child[i]->nodeType == ntID || tree->child[i]->nodeType == ntCall) {
            SymbolTableEntry *newEntry = NewEntry(tree->child[i]);
            if(AddEntryToScope(newEntry, table)) {
                dataTypeChildren[i] = newEntry->following->node->dataType;
            }
        } else {
            dataTypeChildren[i] = ConstHandler(tree->child[i], table);
        }
    }
    if(dataTypeChildren[0] == unknown || dataTypeChildren[1] == unknown) {
        return unknown;
    } else if(dataTypeChildren[0] == dataTypeChildren[1]) {
        return dataTypeChildren[0];
    } else {
        errs = errs + 1;
        printf(
            "ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
            tree->lineNum,
            tree->literal,
            DataTypeToString(dataTypeChildren[0]),
            DataTypeToString(dataTypeChildren[1])
        );
        return dataTypeChildren[0];
    }
}

DataType UnaryHandler (Node * tree, ScopeTable * table) {
    if(tree->child[0]->nodeType == ntOp || tree->child[0]->nodeType == ntTrueAssign) {
        return OpHandler(tree->child[0], table);
    } else if(IsUnary(tree->child[0])) {
        return UnaryHandler(tree->child[0], table);
    } else if(tree->child[0]->nodeType == ntID || tree->child[0]->nodeType == ntCall) {
        SymbolTableEntry *newEntry = NewEntry(tree->child[0]);
        if(AddEntryToScope(newEntry, table)) {
            return newEntry->following->node->dataType;
        }
    } else {
        return ConstHandler(tree->child[0], table);
    }
}

DataType ConstHandler (Node * tree, ScopeTable * table) {
    SymbolTableEntry *newEntry = NULL;
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
        case ntArrAd: // a little haphazard no?
            newEntry = NewEntry(tree->child[0]);
            AddEntryToScope(newEntry, table);
            return newEntry->following->node->dataType;
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