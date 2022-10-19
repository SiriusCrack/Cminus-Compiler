#include "SemanticAnalysis.h"
#include <stdio.h>
#include <stdlib.h>
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

void WriteRefs (Node * tree, ScopeTable * table) {
    ScopeTable * newScope = table;
    if(IsScope(tree)) {
        newScope = GetMatchingChildScope(newScope, tree->UID);
    }
    if(IsOp(tree)) {
        // Setup and Recursion
        DataType myDataType = unknown;
        WriteRefs(tree->child[0], newScope);
        WriteRefs(tree->child[1], newScope);
        myDataType = intData;
        // Error Checking
        if(IsArray(tree->child[0]) || IsArray(tree->child[1])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation '%s' does not work with arrays.\n",
                tree->lineNum,
                tree->literal
            );
        }
        if((tree->child[0]->dataType != unknown) && (tree->child[1]->dataType != unknown)) { //why tho??
            if(tree->child[0]->dataType != intData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(intData),
                    DataTypeToString(tree->child[0]->dataType)
                );
            }
            if(tree->child[1]->dataType != intData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(intData),
                    DataTypeToString(tree->child[1]->dataType)
                );
            }
        }
        // Self
        tree->dataType = myDataType;
    } else if(IsAssign(tree)) {
        // Setup and Recursion
        DataType myDataType = unknown;
        WriteRefs(tree->child[1], newScope);
        tree->child[0]->isInitialized = 1; // might change this to child[1] init? doesnt seem to in testData
        if(tree->child[0]->nodeType == ntArrAd) tree->child[0]->child[0]->isInitialized = 1;
        WriteRefs(tree->child[0], newScope);
        myDataType = tree->child[0]->dataType;
        // Error Checking
        if(IsArray(tree->child[0]) != IsArray(tree->child[1])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n",
                tree->lineNum,
                tree->literal,
                IsArrayToString(IsArray(tree->child[0])),
                IsArrayToString(IsArray(tree->child[1]))
            );
            myDataType = unknown;
        } else if((tree->child[0]->dataType != unknown) && (tree->child[1]->dataType != unknown)) {
            if(tree->child[0]->dataType != tree->child[1]->dataType) {
                if((tree->child[0]->dataType != unknown) && (tree->child[1]->dataType != unknown)) { //why tho??
                    errs = errs + 1;
                    printf(
                        "ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                        tree->lineNum,
                        tree->literal,
                        DataTypeToString(tree->child[0]->dataType),
                        DataTypeToString(tree->child[1]->dataType)
                    );
                    myDataType = unknown;
                }
            }
        }
        // Self
        tree->dataType = myDataType;
    } else if(IsRelOp(tree)) {
        // Setup and Recursion
        DataType myDataType = unknown;
        WriteRefs(tree->child[0], newScope);
        WriteRefs(tree->child[1], newScope);
        myDataType = boolData;
        // Error Checking
        if((tree->child[0]->dataType != unknown) && (tree->child[1]->dataType != unknown)) {
            if(tree->child[0]->dataType != tree->child[1]->dataType) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(tree->child[0]->dataType),
                    DataTypeToString(tree->child[1]->dataType)
                );
                myDataType = unknown;
            }
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
            myDataType = unknown;
        }
        // Self
        tree->dataType = myDataType;
    } else if(IsCmp(tree)) {
        // Setup and Recursion
        DataType myDataType = unknown;
        WriteRefs(tree->child[0], newScope);
        WriteRefs(tree->child[1], newScope);
        myDataType = boolData;
        // Error Checking
        if(IsArray(tree->child[0]) || IsArray(tree->child[1])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation '%s' does not work with arrays.\n",
                tree->lineNum,
                tree->literal
            );
        }
        if((tree->child[0]->dataType != unknown) && (tree->child[1]->dataType != unknown)) { // why tho???
            if(tree->child[0]->dataType != boolData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(boolData),
                    DataTypeToString(tree->child[0]->dataType)
                );
            }
            if(tree->child[1]->dataType != boolData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(boolData),
                    DataTypeToString(tree->child[1]->dataType)
                );
            }
        }
        // Self
        tree->dataType = myDataType;
    } else if(IsIncDec(tree)) {
        // Setup and Recursion
        DataType myDataType = unknown;
        WriteRefs(tree->child[0], newScope);
        myDataType = tree->child[0]->dataType;
        // Error Checking
        if(tree->child[0]->isArray) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation '%s' does not work with arrays.\n",
                tree->lineNum,
                tree->literal
            );
            myDataType = unknown;
        }
        // Self
        tree->dataType = myDataType;
    } else if(IsUnaryCmp(tree)) {
        // Setup and Recursion
        DataType myDataType = unknown;
        WriteRefs(tree->child[0], newScope);
        myDataType = boolData;
        // Error Checking
        if(tree->child[0]->isArray) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation 'not' does not work with arrays.\n",
                tree->lineNum
            );
            myDataType = unknown;
        }
        // Self
        tree->dataType = myDataType;
    } else if(IsUnary(tree)) {
        // Setup and Recursion
        DataType myDataType = unknown;
        WriteRefs(tree->child[0], newScope);
        myDataType = tree->child[0]->dataType;
        // Error Checking
        if(tree->nodeType == ntSignOp && IsArray(tree->child[0])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation 'chsign' does not work with arrays.\n",
                tree->lineNum
            );
            myDataType = unknown;
        } else if(tree->nodeType == ntSizeofOp && !IsArray(tree->child[0])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation 'sizeof' only works with arrays.\n",
                tree->lineNum
            );
            myDataType = unknown;
        } else if(tree->nodeType == ntQuestOp && IsArray(tree->child[0])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation '?' does not work with arrays.\n",
                tree->lineNum
            );
            myDataType = unknown;
        }
        // Self
        tree->dataType = myDataType;
    } else if(IsArrAd(tree)) {
        // Setup and Recursion
        DataType myDataType = unknown;
        WriteRefs(tree->child[1], newScope);
        WriteRefs(tree->child[0], newScope);
        myDataType = tree->child[0]->dataType;
        // Error Checking
        if(!tree->child[0]->isArray) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Cannot index nonarray '%s'.\n",
                tree->lineNum,
                tree->child[0]->literal
            );
            myDataType = unknown;
        }
        if(tree->child[1]->isArray && tree->child[1]->child[1] == NULL) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Array index is the unindexed array '%s'.\n",
                tree->lineNum,
                tree->child[1]->literal
            );
            myDataType = unknown;
        } else if(tree->child[1]->dataType != intData) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Array '%s' should be indexed by type int but got %s.\n",
                tree->lineNum,
                tree->child[0]->literal,
                DataTypeToString(tree->child[1]->dataType)
            );
            myDataType = unknown;
        }
        // Self
        tree->dataType = myDataType;
    } else if(IsConst(tree)) {
        DataType myDataType = unknown;
        switch (tree->nodeType) {
            case ntNumConst:
                myDataType = intData;
                break;
            case ntCharConst:
                myDataType = charData;
                break;
            case ntBoolConst:
                myDataType = boolData;
                break;
            default:
                printf("uhhhhhhhhhhhh %s\n", tree->literal);
                myDataType = unknown;
                break;
        }
        tree->dataType = myDataType;
    } else if(IsNewEntry(tree)) {
        SymbolTableEntry * newEntry = NewEntry(tree);
        int addEntryResult = 0;
        addEntryResult = AddEntryToScope(newEntry, newScope);
        if(addEntryResult == 1) {
            if(tree->entry->following->node->isInitialized || tree->isInitialized) {
                tree->entry->following->node->isInitialized = 1;
            } else {
                warns = warns + 1;
                printf(
                    "WARNING(%d): Variable '%s' may be uninitialized when used here.\n",
                    tree->lineNum,
                    tree->literal
                );
            }
            tree->dataType = tree->entry->following->node->dataType;
            tree->isArray = tree->entry->following->node->isArray;
        } else if(addEntryResult == 0) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Symbol '%s' is not declared.\n",
                tree->lineNum,
                tree->literal
            );
            free(newEntry);
        } else if(addEntryResult == 2) {
            errs = errs + 1;
            printf(
                "ERROR(%d): '%s' is a simple variable and cannot be called.\n",
                tree->lineNum,
                tree->literal
            );
            free(newEntry);
        }
    } else {
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
        if(cur->node->literal[0] != '*') {
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