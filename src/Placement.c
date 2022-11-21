#include "Placement.h"
#include <stdio.h>
#include <string.h>

extern int goffset;
extern int foffset;

int MyIsScope (Node * node);

void DoPlacement(Node * node, ScopeTable * table) {
    // printf("ln%d g%d, f%d\n", node->lineNum, goffset, foffset);
    ScopeTable * newScope = table;
    if(MyIsScope(node)) {
        newScope = node->entry->scope;
    }
    if(node->nodeType == ntCompound || node->nodeType == ntCompoundwFunc) {
        // Traverse
        node->size = goffset;
        for(int i = 0; i < AST_MAX_CHILDREN; i++) {
            if(node->child[i] != NULL) {
                DoPlacement(node->child[i], newScope);
            }
        }
        // Size
        // Location
        node->location = 0;
        node->referenceType = rtNone;
    } else if(node->isDecl) {
        if(node->nodeType == ntFunc) {
            node->size = -2;
            // Traverse
            int foffsetOld = foffset;
            // goffset += node->size;
            foffset = node->size;
            for(int i = 0; i < AST_MAX_CHILDREN; i++) {
                if(node->child[i] != NULL) {
                    DoPlacement(node->child[i], newScope);
                }
            }
            foffset = foffsetOld;
            // Location
            node->location = 0;
            node->referenceType = rtGlobal;
            // Size
            if(node->child[0] != NULL) {
                node->size -= node->child[0]->size;
                Node * cur = node->child[0];
                while(cur->sibling != NULL) {
                    cur = cur->sibling;
                    node->size -= cur->size;
                }
            }
        } else if(node->nodeType == ntParm || node->nodeType == ntParmArray) {
            // Traverse
            if(node->child[0] != NULL) {
                DoPlacement(node->child[0], newScope);
            }
            // Location
            // if(node->isArray) foffset -= 1;
            node->location = foffset;
            node->referenceType = rtParameter;
            foffset -= node->size;
        } else if(node->nodeType == ntVar || node->nodeType == ntVarArray || node->nodeType == ntStaticVar) {
            int *offset;
            if(node->referenceType == rtStatic || newScope->isGlobal) {
                offset = &goffset;
                node->referenceType = rtGlobal;
            } else if(node->nodeType == ntStaticVar) {
                offset = &goffset;
                node->referenceType = rtLocal;
            } else {
                offset = &foffset;
                if(node->referenceType != rtStatic) node->referenceType = rtLocal;
            }
            if(node->isArray) {
                // printf("%d %d %d\n", node->isDecl, node->lineNum, node->childCount);
                *offset -= 1;
                for(int i = 0; i < AST_MAX_CHILDREN; i++) {
                    if(node->child[i] != NULL) {
                        DoPlacement(node->child[i], newScope);
                    }
                }
            }
            node->location = *offset;
            if(node->nodeType == ntStaticVar) node->referenceType = rtStatic;
            *offset -= node->size;
            if(node->isArray) *offset += 1;
        } else {
            printf("shouldnt get here\n");
        }
    } else if(node->nodeType == ntStringConst) {
        // Location
        node->location = goffset;
        node->referenceType = rtGlobal;
        goffset -= node->size;
    } else if(node->nodeType == ntID) {
        // Location
        node->location = node->entry->following->node->location;
        node->referenceType = node->entry->following->node->referenceType;
        // Size
        node->size = node->entry->following->node->size;
    } else {
        for(int i = 0; i < AST_MAX_CHILDREN; i++) {
            if(node->child[i] != NULL) {
                DoPlacement(node->child[i], newScope);
            }
        }
    }
    if(node->sibling != NULL) {
        DoPlacement(node->sibling, table);
    }
}

int MyIsScope (Node * node) {
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