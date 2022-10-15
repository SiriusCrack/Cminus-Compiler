#include "SemanticAnalysis.h"
#include <stdio.h>
#include <string.h>

extern Node * AST;
extern ScopeTable * SymbolTable;
extern int warns;
extern int errs;

char * IsArrayToString(int isArray);
int IsScope (Node * node);
int IsNewEntry (Node * node);
int IsOp (Node * node);
int IsAssign (Node * node);
int IsIncDec (Node * node);
int IsCmp (Node * node);
int IsUnaryCmp (Node * node);
int IsRelOp (Node * node);
int IsUnary (Node * node);
int IsArray (Node * node);
int IsArrAd (Node * node);
int IsConst (Node * node);

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

DataType WriteRefs (Node * tree, ScopeTable * table) {
    DataType dataType = unknown;
    ScopeTable * newScope = table;
    if(IsScope(tree)) {
        newScope = GetMatchingChildScope(newScope, tree->UID);
    }
    if(IsOp(tree)) {
        DataType dataTypeChildren[2] = {unknown, unknown};
        dataTypeChildren[0] = WriteRefs(tree->child[0], newScope);
        dataTypeChildren[1] = WriteRefs(tree->child[1], newScope);
        if(dataTypeChildren[0] != unknown && dataTypeChildren[1] != unknown) { // seems wrong?
            if(IsArray(tree->child[0]) || IsArray(tree->child[1])) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): The operation '%s' does not work with arrays.\n",
                    tree->lineNum,
                    tree->literal
                );
            } else if(dataTypeChildren[0] != dataTypeChildren[1]) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(dataTypeChildren[0]),
                    DataTypeToString(dataTypeChildren[1])
                );
            }
        }
        tree->dataType = dataTypeChildren[0];
        dataType = dataTypeChildren[0];
    } else if(IsAssign(tree)) {
        DataType dataTypeChildren[2] = {unknown, unknown};
        dataTypeChildren[1] = WriteRefs(tree->child[1], newScope);
        tree->isInitialized = tree->child[1]->isInitialized;
        tree->child[0]->isInitialized = tree->child[1]->isInitialized;
        // tree->isInitialized = 1;
        // tree->child[0]->isInitialized = 1;
        dataTypeChildren[0] = WriteRefs(tree->child[0], newScope);
        if(dataTypeChildren[0] != unknown && dataTypeChildren[1] != unknown) { // seems wrong?
            if(IsArray(tree->child[0]) != IsArray(tree->child[1])) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n",
                    tree->lineNum,
                    tree->literal,
                    IsArrayToString(IsArray(tree->child[0])),
                    IsArrayToString(IsArray(tree->child[1]))
                );
                dataTypeChildren[0] = unknown;
            } else if(dataTypeChildren[0] != dataTypeChildren[1]) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(dataTypeChildren[0]),
                    DataTypeToString(dataTypeChildren[1])
                );
                dataTypeChildren[0] = unknown;
            }
        }
        tree->dataType = dataTypeChildren[0];
        dataType = dataTypeChildren[0];
    } else if(IsIncDec(tree)) {
        DataType dataTypeChild = unknown;
        dataTypeChild = WriteRefs(tree->child[0], newScope);
        if(tree->child[0]->isArray) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation '%s' does not work with arrays.\n",
                tree->lineNum,
                tree->literal
            );
        }
        tree->dataType = dataTypeChild;
        dataType = dataTypeChild;
    } else if(IsCmp(tree)) {
        DataType dataTypeChildren[2] = {unknown, unknown};
        dataTypeChildren[0] = WriteRefs(tree->child[0], newScope);
        dataTypeChildren[1] = WriteRefs(tree->child[1], newScope);
        if(dataTypeChildren[0] != dataTypeChildren[1]) {
            errs = errs + 1;
            printf(
                "ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                tree->lineNum,
                tree->literal,
                DataTypeToString(dataTypeChildren[0]),
                DataTypeToString(dataTypeChildren[1])
            );
        }
        if(tree->child[0]->isArray || tree->child[1]->isArray) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation '%s' does not work with arrays.\n",
                tree->lineNum,
                tree->literal
            );
        }
        tree->dataType = boolData;
        dataType = boolData;
    } else if(IsUnaryCmp(tree)) {
        DataType dataTypeChild = unknown;
        dataTypeChild = WriteRefs(tree->child[0], newScope);
        if(tree->child[0]->isArray) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation 'not' does not work with arrays.\n",
                tree->lineNum
            );
        }
        tree->dataType = boolData;
        dataType = boolData;
    } else if(IsRelOp(tree)) {
        DataType dataTypeChildren[2] = {unknown, unknown};
        dataTypeChildren[0] = WriteRefs(tree->child[0], newScope);
        dataTypeChildren[1] = WriteRefs(tree->child[1], newScope);
        if(dataTypeChildren[0] != dataTypeChildren[1]) {
            errs = errs + 1;
            printf(
                "ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                tree->lineNum,
                tree->literal,
                DataTypeToString(dataTypeChildren[0]),
                DataTypeToString(dataTypeChildren[1])
            );
        }
        if(IsArray(tree->child[0]) != IsArray(tree->child[1])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n",
                tree->lineNum,
                tree->literal,
                IsArrayToString(IsArray(tree->child[0])),
                IsArrayToString(IsArray(tree->child[1]))
            );
        }
        tree->dataType = boolData;
        dataType = boolData;
    } else if(IsUnary(tree)) {
        DataType dataTypeChild = unknown;
        dataTypeChild = WriteRefs(tree->child[0], newScope);
        if(tree->nodeType == ntSignOp && IsArray(tree->child[0])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation 'chsign' does not work with arrays.\n",
                tree->lineNum
            );
        } else if(tree->nodeType == ntSizeofOp && !IsArray(tree->child[0])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation 'sizeof' only works with arrays.\n",
                tree->lineNum
            );
        } else if(tree->nodeType == ntQuestOp && IsArray(tree->child[0])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation '?' does not work with arrays.\n",
                tree->lineNum
            );
        }
        tree->dataType = dataTypeChild;
        dataType = dataTypeChild;
    } else if(IsArrAd(tree)) {
        DataType dataTypeChildren[2] = {unknown, unknown};
        dataTypeChildren[0] = WriteRefs(tree->child[0], newScope);
        dataTypeChildren[1] = WriteRefs(tree->child[1], newScope);
        tree->isInitialized = tree->child[0]->isInitialized;
        tree->dataType = dataTypeChildren[0];
        if(!tree->child[0]->isArray) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Cannot index nonarray '%s'.\n",
                tree->lineNum,
                tree->child[0]->literal
            );
        }
        if(tree->child[1]->isArray && tree->child[1]->child[1] == NULL) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Array index is the unindexed array '%s'.\n",
                tree->lineNum,
                tree->child[1]->literal
            );
        } else if(dataTypeChildren[1] != intData) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Array '%s' should be indexed by type int but got %s.\n",
                tree->lineNum,
                tree->child[0]->literal,
                DataTypeToString(dataTypeChildren[1])
            );
        }
        dataType = dataTypeChildren[0];
    } else {
        if(IsConst(tree)) {
            switch (tree->nodeType) {
                case ntNumConst:
                    dataType = intData;
                    break;
                case ntCharConst:
                    dataType = charData;
                    break;
                case ntBoolConst:
                    dataType = boolData;
                    break;
                default:
                    printf("uhhhhhhhhhhhh %s\n", tree->literal);
                    break;
            }
            tree->dataType = dataType;
        } else if(IsNewEntry(tree)) {
            SymbolTableEntry * newEntry = NewEntry(tree);
            if(AddEntryToScope(newEntry, newScope)) {
                dataType = newEntry->following->node->dataType;
                tree->dataType = dataType;
                tree->isArray = newEntry->following->node->isArray;
            }
        }
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
    return dataType;
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
                warns = warns + 1;
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

char * IsArrayToString(int isArray) {
    if(isArray) {
        return "";
    } else {
        return " not";
    }
}

int IsScope (Node * node) {
    if(
        node->nodeType == ntCompound ||
        node->nodeType == ntFunc ||
        node->nodeType == ntIterwComp ||
        node->nodeType == ntTowComp
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsNewEntry (Node * node) {
    if(
        node->nodeType == ntID ||
        node->nodeType == ntCall
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsOp (Node * node) {
    if(
        node->nodeType == ntOp
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsAssign (Node * node) {
    if(
        node->nodeType == ntTrueAssign
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsIncDec (Node * node) {
    if(
        node->nodeType == ntAssign
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsCmp (Node * node) {
    if(
        node->nodeType == ntOrOp ||
        node->nodeType == ntAndOp
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsUnaryCmp (Node * node) {
    if(
        node->nodeType == ntNotOp
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsRelOp (Node * node) {
    if(
        node->nodeType == ntRelOp
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

int IsArray (Node * node) {
    if(
        node->isArray == 1
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsArrAd (Node * node) {
    if(
        node->nodeType == ntArrAd
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsConst (Node * node) {
    if(
        node->nodeType == ntNumConst ||
        node->nodeType == ntCharConst ||
        node->nodeType == ntBoolConst
    ) {
        return 1;
    } else {
        return 0;
    }
}