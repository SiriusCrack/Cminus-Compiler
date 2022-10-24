#include "SymbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int PrintSymTblFlag;
extern int warns;
extern int errs;

SymbolTableEntry * FindFuncDecl (SymbolTableEntry *entry, ScopeTable *scope);

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
        newScope->depth = 0;
        newScope->isIO = 0;
        newScope->self = NULL;
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
        newScope->depth = 0;
        newScope->isIO = 0;
        newScope->self = NewEntry(node);
        newScope->symbolTable = NULL;
        node->entry = newScope->self;
        return newScope;
    }
}

ScopeTable * GetMatchingChildScope (ScopeTable * scopeTable, int nodeUID) {
    int i;
    for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
        if(scopeTable->child[i]->self->node->UID == nodeUID) {
            return scopeTable->child[i];
        }
    }
    printf("child with UID%d not found\n", nodeUID);
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
        printf("entry [%d]: %d%s i=%d a=%d\n", cur->node->lineNum, cur->node->isDecl, cur->node->literal, cur->node->isInitialized, cur->node->isArray);
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
        newEntry->node = node;
        newEntry->following = NULL;
        int i;
        for(i = 0; i < ENTRY_MAX_FOLLOWERS; i++) {
            newEntry->followers[i] = NULL;
        }
        newEntry->isDecl = node->isDecl;
        node->entry = newEntry;
        return newEntry;
    }
}

int AddEntryToScope (SymbolTableEntry * entry, ScopeTable * scope) { //awful spaghetti mess. should probably separate ntCalls from other IDs
    int errResult = 1;
    // Connect to decl
    if(!entry->isDecl) {
        SymbolTableEntry * myDecl = NULL;
        if(entry->node->nodeType == ntCall) {
            myDecl = FindFuncDecl(entry, scope);
            if(myDecl == NULL) {
                myDecl = FindDecl(entry, scope);
                if(myDecl != NULL) {
                    entry->following = myDecl;
                    int i;
                    for(i = 0; i < ENTRY_MAX_FOLLOWERS; i++) {
                        if(myDecl->followers[i] == NULL) {
                            myDecl->followers[i] = entry;
                        }
                    }
                    return 2;
                }
            } else {
                entry->node->dataType = myDecl->node->dataType;
                int i;
                Node * declParams[10];
                for(i = 0; i < 10; i++) {
                    declParams[i] = NULL;
                }
                Node * myParams[10];
                for(i = 0; i < 10; i++) {
                    myParams[i] = NULL;
                }
                int declParamCount = 0;
                if(myDecl->node->child[0] != NULL) {
                    declParams[declParamCount] = myDecl->node->child[0];
                    declParamCount++;
                    Node * cur = myDecl->node->child[0];
                    while(cur->sibling != NULL) {
                        cur = cur->sibling;
                        declParams[declParamCount] = cur;
                        declParamCount++;
                    }
                }
                int myParamCount = 0;
                if(entry->node->child[0] != NULL) {
                    myParams[myParamCount] = entry->node->child[0];
                    myParamCount++;
                    Node * cur = entry->node->child[0];
                    while(cur->sibling != NULL) {
                        cur = cur->sibling;
                        myParams[myParamCount] = cur;
                        myParamCount++;
                    }
                }
                int minParamCount = 0;
                if(declParamCount > myParamCount) {
                    errResult = 4;
                    minParamCount = myParamCount;
                } else if(declParamCount < myParamCount) {
                    errResult = 5;
                    minParamCount = declParamCount;
                } else {
                    minParamCount = declParamCount;
                }
                for(i = 0; i < minParamCount; i++) {
                    if(declParams[i]->dataType != unknown) {
                        myParams[i]->dataType = declParams[i]->dataType;
                        if(declParams[i]->dataType != myParams[i]->dataType) {
                            errs = errs + 1;
                            printf(
                                "ERROR(%d): Expecting %s in parameter %i of call to '%s' declared on line %d but got %s.\n",
                                myParams[i]->lineNum,
                                DataTypeToString(declParams[i]->dataType),
                                i+1,
                                myDecl->node->literal,
                                myDecl->node->lineNum,
                                DataTypeToString(myParams[i]->dataType)
                            );
                        }
                        if(declParams[i]->isArray != myParams[i]->isArray) {
                            if(declParams[i]->isArray && !myParams[i]->isArray) {
                                errs = errs + 1;
                                printf(
                                    "ERROR(%d): Expecting array in parameter %i of call to '%s' declared on line %d.\n",
                                    myParams[i]->lineNum,
                                    i+1,
                                    myDecl->node->literal,
                                    myDecl->node->lineNum
                                );
                            } else if(!declParams[i]->isArray && myParams[i]->isArray) {
                                errs = errs + 1;
                                printf(
                                    "ERROR(%d): Not expecting array in parameter %i of call to '%s' declared on line %d.\n",
                                    myParams[i]->lineNum,
                                    i+1,
                                    myDecl->node->literal,
                                    myDecl->node->lineNum
                                );
                            }
                        }
                    }
                }
            }
        } else {
            if(FindFuncDecl(entry, scope) != NULL) { //used func as a var 
                myDecl = FindFuncDecl(entry, scope);
                entry->following = myDecl;
                int i;
                for(i = 0; i < ENTRY_MAX_FOLLOWERS; i++) {
                    if(myDecl->followers[i] == NULL) {
                        myDecl->followers[i] = entry;
                    }
                }
                return 3;
            } else {
                myDecl = FindDecl(entry, scope);
            }
        }
        if(myDecl != NULL) {
            entry->following = myDecl;
            int i;
            for(i = 0; i < ENTRY_MAX_FOLLOWERS; i++) {
                if(myDecl->followers[i] == NULL) {
                    myDecl->followers[i] = entry;
                }
            }
        } else {
            return 0;
        }
    }
    // Add to scope
    if(scope->symbolTable == NULL) {
        scope->symbolTable = entry;
        return errResult;
    } else {
        // Abomination of a traversal if i ever saw one
        SymbolTableEntry * cur = scope->symbolTable;
        while(1) { // removed duplicate check. should probably rework  edit: still havent re-added dCheck... seems fine
            if(cur->next != NULL) {
                cur = cur->next;
            } else {
                cur->next = entry;
                return errResult;
            }
        }
    }
}

SymbolTableEntry * FindDecl(SymbolTableEntry * entry, ScopeTable * scope) {
    // Search this scope
    if(scope->symbolTable != NULL) {
        SymbolTableEntry * cur = scope->symbolTable;
        while(cur != NULL) {
            if(cur->isDecl) {
                if(strcmp(cur->node->literal, entry->node->literal) == 0) { // found match
                    return cur;
                }
            }
            cur = cur->next;
        }
    }
    // Scope Traversal
    if(scope->parent != NULL) { // traverse up
        return FindDecl(entry, scope->parent);
    } else { // you've reached the top
        return NULL;
    }
}

SymbolTableEntry * FindReDecl(SymbolTableEntry * entry, ScopeTable * scope) {
    // Search this scope
    if(scope->symbolTable != NULL) {
        SymbolTableEntry * cur = scope->symbolTable;
        while(cur != NULL) {
            if(cur->isDecl) {
                if(strcmp(cur->node->literal, entry->node->literal) == 0) { // found match
                    return cur;
                }
            }
            cur = cur->next;
        }
    }
    // Search forloop decls
    if(scope->self != NULL) {
        if(scope->self->node->nodeType == ntCompound) {
            if(scope->parent != NULL) { // traverse up
                if(scope->parent->self != NULL) { //check not global 
                    if(scope->parent->self->node->nodeType == ntTo) {
                        SymbolTableEntry * cur = scope->parent->symbolTable;
                        while(cur != NULL) {
                            if(cur->isDecl) {
                                if(strcmp(cur->node->literal, entry->node->literal) == 0) { // found match
                                    return cur;
                                }
                            }
                            cur = cur->next;
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

SymbolTableEntry * FindLoop(ScopeTable * scope) {
    if(scope->parent != NULL) { // traverse up
        if(scope->self->node->isLoop) {
            return scope->self;
        }
        return FindLoop(scope->parent);
    } else { // you've reached the top
        return NULL;
    }
}

SymbolTableEntry * FindMyFunc (ScopeTable * scope) {
    if(scope->parent != NULL) { // traverse up
        if(scope->self->node->nodeType == ntFunc) {
            return scope->self;
        }
        return FindMyFunc(scope->parent);
    } else { // you've reached the top
        return NULL;
    }
}

SymbolTableEntry * FindFuncDecl (SymbolTableEntry *entry, ScopeTable *scope) {
    if(scope->parent == NULL) {
        printf("stop, you're in global lol\n");
        return NULL;
    }
    ScopeTable *parentScope = scope->parent;
    int i;
    for(i = 0; i < SCOPE_MAX_CHILDREN; i++) {
        if(parentScope->child[i] != NULL) {
            if(strcmp(entry->node->literal, parentScope->child[i]->self->node->literal) == 0) { // found match
                return parentScope->child[i]->self;
            }
        } else {
            break;
        }
    }
    if(parentScope->parent != NULL) {
        return FindFuncDecl(entry, parentScope);
    } else {
        return NULL;
    }
}