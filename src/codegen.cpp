#include "codegen.h"
#include <stdio.h>
#include "emitcode.h"

void generateCode (Node *node);
void generateFunction (Node *node);

void WalkAST(Node * node) {
    if(node == NULL) { return; }
    generateCode(node);
    for(int i = 0; i < AST_MAX_CHILDREN; i++) {
        WalkAST(node->child[i]);
    }
    WalkAST(node->sibling);
}

void generateCode(Node * node) {
    if(node->nodeType == ntFunc) { generateFunction(node); }
}

void generateFunction(Node *node) {
    emitRM("ST", 3, -1, 1, NO_COMMENT);
    emitRM("ST", 3, -1, 1, "nice");
}