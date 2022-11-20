#include "Placement.h"
#include <stdio.h>
#include <string.h>

extern int goffset;
extern int foffset;

void DoPlacement(Node * node) {
    if(node->nodeType == ntCompound) {
        // Size
        node->size = foffset;
        if(node->child[0] != NULL) {
            node->size += node->child[0]->size;
            Node * cur = node->child[0];
            while(cur->sibling != NULL) {
                cur = cur->sibling;
                node->size += cur->sibling->size;
            }
        }
        // Location
        node->location = 0;
        // Traverse
        int foffsetOld = foffset;
        foffset = 0;
        for(int i = 0; i < AST_MAX_CHILDREN; i++) {
            if(node->child[i] != NULL) {
                DoPlacement(node->child[i]);
            }
        }
        foffset = foffsetOld;
    }
}