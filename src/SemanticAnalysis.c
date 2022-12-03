// Known Errors
/* Needs to be entirely reworked... along with SymbolTable.c.
.. Functionally, seems to work aside from initlization check,
.. but SemanticAnalysis is so poorly written, poorly separated, 
.. it would be easier to completely rewrite. */
// Strings need to be treated as character arrays, at least by PrintTable

#include "SemanticAnalysis.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Node * AST;
extern ScopeTable * SymbolTable;
extern int goffset;
extern int foffset;
extern int warns;
extern int errs;

char const * IsArrayToSemanticString(int isArray);
int IsScope (Node * node);
int IsNewEntry (Node * node);
int IsOp (Node * node);
int IsAssign (Node * node);
int IsIncDec (Node * node);
int IsCmp (Node * node);
int IsUnaryCmp (Node * node);
int IsRelOp (Node * node);
int IsCond (Node * node);
int IsUnary (Node * node);
int IsArray (Node * node);
int IsArrAd (Node * node);
int IsRange (Node * node);
int IsReturn (Node * node);
int IsBreak (Node * node);
int IsConst (Node * node);

void WriteScopes (Node * node, ScopeTable * table) {
    // Check
    if(node == NULL) {
        return;
    }
    // Action
    ScopeTable * newScope = table;
    if(IsScope(node)) { // add scope table
        newScope = NewScope(node);
        AddChildScope(table, newScope);
    } else if(node->isDecl) { // guess we're just adding stuff wherever now ok
        SymbolTableEntry * myDecl = NULL;
        SymbolTableEntry * newEntry = NewEntry(node);
        if(node->nodeType == ntFunc) {
            myDecl = FindFuncDecl(newEntry, newScope);
        } else {
            myDecl = FindReDecl(newEntry, newScope);
        }
        if(myDecl != NULL) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                node->lineNum,
                node->literal,
                myDecl->node->lineNum
            );
        } else {
            AddEntryToScope(newEntry, newScope);
        }
        if(node->isInitialized) { // roundabout way to check for that weird "var:data" grammar. should definitely move at some point.
            if(node->child[0] != NULL) {
                WriteRefs(node->child[0], newScope);
                if(
                    (node->dataType != unknown) &&
                    (node->child[0]->dataType != unknown) &&
                    (node->dataType != node->child[0]->dataType)
                ) {
                    errs = errs + 1;
                    printf(
                        "ERROR(%d): Initializer for variable '%s' of %s is of %s\n",
                        node->lineNum,
                        node->literal,
                        DataTypeToString(node->dataType),
                        DataTypeToString(node->child[0]->dataType)
                    );
                } else if(node->isArray != node->child[0]->isArray) {
                    errs = errs + 1;
                    printf(
                        "ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is%s an array and rhs is%s an array.\n",
                        node->lineNum,
                        node->literal,
                        IsArrayToSemanticString(node->isArray),
                        IsArrayToSemanticString(node->child[0]->isArray)
                    );
                } else if(!node->child[0]->isConst) {
                    errs = errs + 1;
                    printf(
                        "ERROR(%d): Initializer for variable '%s' is not a constant expression.\n",
                        node->lineNum,
                        node->literal
                    );
                }
            }
        }
        if(newScope->self == NULL) {
            node->isInitialized = 1;
        }
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
    // Check
    if(tree == NULL) {
        return;
    }
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
                    "ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(intData),
                    DataTypeToString(tree->child[0]->dataType)
                );
            }
            if(tree->child[1]->dataType != intData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(intData),
                    DataTypeToString(tree->child[1]->dataType)
                );
            }
        }
        // Self
        tree->dataType = myDataType;
        if(tree->child[0]->isConst && tree->child[1]->isConst) {
            tree->isConst = 1;
        }
    } else if(IsAssign(tree)) {
        // Setup and Recursion
        DataType myDataType = unknown;
        WriteRefs(tree->child[1], newScope);
        tree->child[0]->isInitialized = 1; // might change this to child[1]'s init? doesnt seem to in testData
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
                IsArrayToSemanticString(IsArray(tree->child[0])),
                IsArrayToSemanticString(IsArray(tree->child[1]))
            );
            myDataType = unknown;
        } else if((tree->child[0]->dataType != unknown) && (tree->child[1]->dataType != unknown)) {
            if(tree->child[0]->dataType != tree->child[1]->dataType) {
                if(tree->literal[0] == '=') {
                    errs = errs + 1;
                    printf(
                        "ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",
                        tree->lineNum,
                        tree->literal,
                        DataTypeToString(tree->child[0]->dataType),
                        DataTypeToString(tree->child[1]->dataType)
                    );
                } else if(tree->child[0]->dataType != intData) {
                    errs = errs + 1;
                    printf(
                        "ERROR(%d): '%s' requires operands of type int but lhs is of %s.\n",
                        tree->lineNum,
                        tree->literal,
                        DataTypeToString(tree->child[0]->dataType)
                    );
                } else if(tree->child[1]->dataType != intData) {
                    errs = errs + 1;
                    printf(
                        "ERROR(%d): '%s' requires operands of type int but rhs is of %s.\n",
                        tree->lineNum,
                        tree->literal,
                        DataTypeToString(tree->child[1]->dataType)
                    );
                }
            }
        }
        // Self
        tree->dataType = myDataType;
        tree->isArray = tree->child[0]->isArray;
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
                    "ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",
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
                IsArrayToSemanticString(IsArray(tree->child[0])),
                IsArrayToSemanticString(IsArray(tree->child[1]))
            );
            myDataType = unknown;
        }
        // Self
        tree->dataType = myDataType;
        if(tree->child[0]->isConst && tree->child[1]->isConst) {
            tree->isConst = 1;
        }
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
                    "ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(boolData),
                    DataTypeToString(tree->child[0]->dataType)
                );
            }
            if(tree->child[1]->dataType != boolData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n",
                    tree->lineNum,
                    tree->literal,
                    DataTypeToString(boolData),
                    DataTypeToString(tree->child[1]->dataType)
                );
            }
        }
        // Self
        tree->dataType = myDataType;
        if(tree->child[0]->isConst && tree->child[1]->isConst) {
            tree->isConst = 1;
        }
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
        if(tree->child[0]->isConst) {
            tree->isConst = 1;
        }
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
        } else if(tree->child[0]->dataType != boolData && tree->child[0]->dataType != unknown) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Unary 'not' requires an operand of type bool but was given %s.\n",
                tree->lineNum,
                DataTypeToString(tree->child[0]->dataType)
            );
            myDataType = unknown;
        }
        // Self
        tree->dataType = myDataType;
        if(tree->child[0]->isConst) {
            tree->isConst = 1;
        }
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
            // myDataType = unknown;
        } else if(tree->nodeType == ntSizeofOp && !IsArray(tree->child[0])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation 'sizeof' only works with arrays.\n",
                tree->lineNum
            );
            // myDataType = unknown;
        } else if(tree->nodeType == ntQuestOp && IsArray(tree->child[0])) {
            errs = errs + 1;
            printf(
                "ERROR(%d): The operation '?' does not work with arrays.\n",
                tree->lineNum
            );
            // myDataType = unknown;
        } else if(tree->child[0]->dataType != unknown) {
            if(tree->nodeType == ntSignOp && tree->child[0]->dataType != intData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): Unary 'chsign' requires an operand of type int but was given %s.\n",
                    tree->lineNum,
                    DataTypeToString(tree->child[0]->dataType)
                );
                // myDataType = unknown;
            } else if(tree->nodeType == ntQuestOp && tree->child[0]->dataType != intData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): Unary '?' requires an operand of type int but was given %s.\n",
                    tree->lineNum,
                    DataTypeToString(tree->child[0]->dataType)
                );
                // myDataType = unknown;
            }
        }
        // Self
        if(tree->nodeType == ntSizeofOp) myDataType = intData;
        tree->dataType = myDataType;
    } else if(IsCond(tree)) {
        // Setup and Recursion
        int i;
        for(i = 0; i < AST_MAX_CHILDREN; i++) {
            if(tree->child[i] != NULL) {
                WriteRefs(tree->child[i], newScope);
            } else {
                break;
            }
        }
        // Error Checking
        if(tree->child[0]->isArray) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Cannot use array as test condition in %s statement.\n",
                tree->lineNum,
                NodeTypeToString(tree->nodeType)
            );
        }
        if(tree->child[0]->dataType != unknown) {
            if(tree->child[0]->dataType != boolData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n",
                    tree->lineNum,
                    NodeTypeToString(tree->nodeType),
                    DataTypeToString(tree->child[0]->dataType)
                );
            }
        }
    } else if(IsRange(tree)) {
        // Setup and Recursion
        int i;
        for(i = 0; i < AST_MAX_CHILDREN; i++) {
            if(tree->child[i] != NULL) {
                WriteRefs(tree->child[i], newScope);
            } else {
                break;
            }
        }
        // Error Checking
        for(i = 0; i < AST_MAX_CHILDREN; i++) {
            if(tree->child[i] != NULL) {
                if(tree->child[i]->isArray) {
                    errs = errs + 1;
                    printf(
                        "ERROR(%d): Cannot use array in position %d in range of for statement.\n",
                        tree->lineNum,
                        i+1
                    );
                }
                if(tree->child[i]->dataType != unknown) {
                    if(tree->child[i]->dataType != intData) {
                        errs = errs + 1;
                        printf( // why is "type int" a string in example? weird
                            "ERROR(%d): Expecting type int in position %d in range of for statement but got %s.\n",
                            tree->lineNum,
                            i+1,
                            DataTypeToString(tree->child[i]->dataType)
                        );
                    }
                }
            } else {
                break;
            }
        }
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
        }
        if(tree->child[1]->isArray && tree->child[1]->child[1] == NULL) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Array index is the unindexed array '%s'.\n",
                tree->lineNum,
                tree->child[1]->literal
            );
        }
        if((tree->child[0]->dataType != unknown) && (tree->child[1]->dataType != unknown)) {
            if(tree->child[1]->dataType != intData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): Array '%s' should be indexed by type int but got %s.\n",
                    tree->lineNum,
                    tree->child[0]->literal,
                    DataTypeToString(tree->child[1]->dataType)
                );
            }
        }
        // Self
        tree->dataType = myDataType;
    } else if(IsReturn(tree)) {
            if(tree->child[0] != NULL) {
                WriteRefs(tree->child[0], newScope);
                tree->dataType = tree->child[0]->dataType;
                tree->isArray = tree->child[0]->isArray;
            } else {
                tree->dataType = voidData;
            }
            SymbolTableEntry * myFunc = FindMyFunc(newScope);
            myFunc->node->hasReturn = 1;
            // Error Checking
            if(tree->isArray) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): Cannot return an array.\n",
                    tree->lineNum
                );
            } else if(myFunc->node->dataType == voidData && tree->dataType != voidData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): Function '%s' at line %d is expecting no return value, but return has a value.\n",
                    tree->lineNum,
                    myFunc->node->literal,
                    myFunc->node->lineNum
                );
            } else if(myFunc->node->dataType != voidData && tree->dataType == voidData) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): Function '%s' at line %d is expecting to return %s but return has no value.\n",
                    tree->lineNum,
                    myFunc->node->literal,
                    myFunc->node->lineNum,
                    DataTypeToString(myFunc->node->dataType)
                );
            } else if(myFunc->node->dataType != tree->dataType) {
                errs = errs + 1;
                printf(
                    "ERROR(%d): Function '%s' at line %d is expecting to return %s but returns %s.\n",
                    tree->lineNum,
                    myFunc->node->literal,
                    myFunc->node->lineNum,
                    DataTypeToString(myFunc->node->dataType),
                    DataTypeToString(tree->dataType)
                );
            }
    } else if(IsBreak(tree)) {
        // Error Checking
        if(FindLoop(newScope) == NULL) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Cannot have a break statement outside of loop.\n",
                tree->lineNum
            );
        }
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
            case ntStringConst:
                myDataType = charData; // unsure
                tree->isArray = 1;
                break;
            default:
                printf("uhhhhhhhhhhhh %s\n", tree->literal);
                myDataType = unknown;
                break;
        }
        tree->dataType = myDataType;
    } else if(IsNewEntry(tree)) {
        if(tree->child[0] != NULL) {
            WriteRefs(tree->child[0], newScope);
        }
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
                tree->entry->following->node->isInitialized = 1;
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
        } else if(addEntryResult == 3) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Cannot use function '%s' as a variable.\n",
                tree->lineNum,
                tree->literal
            );
            free(newEntry);
        } else if(addEntryResult == 4) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n",
                tree->lineNum,
                tree->literal,
                tree->entry->following->node->lineNum
            );
        } else if(addEntryResult == 5) {
            errs = errs + 1;
            printf(
                "ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n",
                tree->lineNum,
                tree->literal,
                tree->entry->following->node->lineNum
            );
        }
    } else {
        int i;
        for(i = 0; i < AST_MAX_CHILDREN; i++) {
            if(tree->child[i] != NULL) {
                WriteRefs(tree->child[i], newScope);
            }
        }
    }
    if(tree->nodeType == ntFunc) {
        if(!tree->hasReturn) {
            if(tree->dataType != voidData) {
                warns = warns + 1;
                printf(
                    "WARNING(%d): Expecting to return %s but function '%s' has no return statement.\n",
                    tree->lineNum,
                    DataTypeToString(tree->dataType),
                    tree->literal
                );
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
                if(table->child[i]->self->node->child[0] == NULL) {
                    table->child[i]->isIO = 1;
                    return;
                }
            }
        } else {
            break;
        }
    }
    errs = errs + 1;
    printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
}

void CheckUse (ScopeTable *table) {
    if(!table->isIO) {
        if(table->self != NULL) {
            if(table->self->node->nodeType == ntFunc) {
                if(strcmp(table->self->node->literal, "main")) {
                    if(table->self->followers[0] == NULL) {
                        warns = warns + 1;
                        printf(
                            "WARNING(%d): The function '%s' seems not to be used.\n",
                            table->self->node->lineNum,
                            table->self->node->literal
                        );
                    }
                }
            }
        }
    }
    int i = 0;
    SymbolTableEntry *cur = table->symbolTable;
    while(cur != NULL) {
        if(cur->node->literal[0] != '*') {
            if(cur->isDecl) {
                if(cur->followers[0] == NULL) {
                    if(cur->node->nodeType == ntParm || cur->node->nodeType == ntParmArray) {
                        warns = warns + 1;
                        printf(
                            "WARNING(%d): The parameter '%s' seems not to be used.\n",
                            cur->node->lineNum,
                            cur->node->literal
                        );
                    } else {
                        warns = warns + 1;
                        printf(
                            "WARNING(%d): The variable '%s' seems not to be used.\n",
                            cur->node->lineNum,
                            cur->node->literal
                        );
                    }
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

char const * IsArrayToSemanticString(int isArray) {
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
        node->nodeType == ntIter ||
        node->nodeType == ntTo
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

int IsCond (Node * node) {
    if(
        node->nodeType == ntIter ||
        node->nodeType == ntIf
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

int IsRange (Node * node) {
    if(
        node->nodeType == ntRange
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsReturn (Node * node) {
    if(
        node->nodeType == ntReturn
    ) {
        return 1;
    } else {
        return 0;
    }
}

int IsBreak (Node * node) {
    if(
        node->nodeType == ntBreak
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
        node->nodeType == ntStringConst ||
        node->nodeType == ntBoolConst
    ) {
        return 1;
    } else {
        return 0;
    }
}