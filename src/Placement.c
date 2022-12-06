#include "Placement.h"
#include <stdio.h>
#include <string.h>

extern Node *AST;
extern int goffset;
extern int foffset;

void walkAST (Node *node);
void placeNode (Node *node);

void Placement() {
    walkAST(AST);
}

void walkAST(Node *node) {
    if(node == NULL) { return; }
    // printf("ln%d g%d, f%d\n", node->lineNum, goffset, foffset);
    placeNode(node);
    walkAST(node->sibling);
}

void placeNode(Node *node) {
    if(node->isDecl) {
        if(node->nodeType == ntFunc) {
            node->referenceType = rtGlobal;
            node->size = -2;
            for(Node *cursor = node->child[0]; cursor != NULL; cursor = cursor->sibling) {
                node->size -= cursor->size;
            }
            node->location = 0;
            int foffsetOld = foffset;
            foffset = -2;
            for(int i = 0; i < AST_MAX_CHILDREN; i++) {
                walkAST(node->child[i]);
            }
            foffset = foffsetOld;
        } else if(node->nodeType == ntParm || node->nodeType == ntParmArray) {
            node->referenceType = rtParameter;
            walkAST(node->child[0]);
            node->location = foffset;
            foffset -= node->size;
        } else if(node->nodeType == ntVar || node->nodeType == ntVarArray || node->nodeType == ntStaticVar) {
            for(int i = 0; i < AST_MAX_CHILDREN; i++) {
                walkAST(node->child[i]);
            }
            if(node->referenceType == rtStatic || node->referenceType == rtGlobal) {
                node->location = goffset;
                if(node->isArray) { node->location -= 1; }
                goffset -= node->size;
            } else {
                node->referenceType = rtLocal;
                node->location = foffset;
                if(node->isArray) {
                    node->location -= 1;
                }
                foffset -= node->size;
            }
        }
    } else {
        if(node->nodeType == ntCompound || node->nodeType == ntCompoundwFunc || node->nodeType == ntTo || node->nodeType == ntTowComp) {
            node->size = foffset;
            for(Node *cursor = node->child[0]; cursor != NULL ; cursor = cursor->sibling) {
                node->size -= cursor->size;
            }
            node->location = 0;
            int foffsetOld = foffset;
            for(int i = 0; i < AST_MAX_CHILDREN; i++) {
                walkAST(node->child[i]);
            }
            foffset = foffsetOld;
        } else if(node->nodeType == ntID) {
            if(node->entry->following->node == NULL) {
                printf("failed\n");
            }
            node->referenceType = node->entry->following->node->referenceType;
            node->location = node->entry->following->node->location;
            node->size = node->entry->following->node->size;
        } else if(node->nodeType == ntStringConst) {
            node->referenceType = rtGlobal;
            node->location = goffset - 1;
            goffset -= node->size;
        } else {
            for(int i = 0; i < AST_MAX_CHILDREN; i++) {
                walkAST(node->child[i]);
            }
        }
    }
}