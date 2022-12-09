#include "codegen.h"
#include <stdio.h>
#include "emitcode.h"

extern Node *AST;
extern FILE * code;

static void walkAST (Node * node);
void generateCode (Node *node);
void generateFunction (Node *node);
void generateIO ();

void CodeGen() {
    generateIO();
    walkAST(AST);
}

void walkAST(Node * node) {
    if(node == NULL) { return; }
    if(node->isIO) { walkAST(node->sibling); return; }
    generateCode(node);
    for(int i = 0; i < AST_MAX_CHILDREN; i++) {
        walkAST(node->child[i]);
    }
    walkAST(node->sibling);
}

void generateCode(Node * node) {
    printf("nice\n");
    if(node->nodeType == ntFunc) { generateFunction(node); }
}

void generateFunction(Node *node) {
    emitRM("ST", 3, -1, 1, NO_COMMENT, "");
    emitRM("ST", 3, -1, 1, "nice", "");
}

void generateIO() {
    emitSkip(1);
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION input\n");
    emitRM("ST", 3, -1, 1, "Store return address", "");
    emitRO("IN", 2, 2, 2, "Grab int input", "");
    emitRM("LD", 3, -1, 1, "Load return address", "");
    emitRM("LD", 1, 0, 1, "Adjust fp", "");
    emitRM("JMP", 7, 0, 3, "Return", "");
    fprintf(code, "* END FUNCTION input\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION output\n");
    emitRM("ST", 3, -1, 1, "Store return address", "");
    emitRM("LD", 3, -2, 1, "Load parameter", "");
    emitRO("OUT", 3, 3, 3, "Output integer", "");
    emitRM("LD", 3, -1, 1, "Load return address", "");
    emitRM("LD", 1, 0, 1, "Adjust fp", "");
    emitRM("JMP", 7, 0, 3, "Return", "");
    fprintf(code, "* END FUNCTION output\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION inputb\n");
    emitRM("ST", 3, -1, 1, "Store return address", "");
    emitRO("INB", 2, 2, 2, "Grab bool input", "");
    emitRM("LD", 3, -1, 1, "Load return address", "");
    emitRM("LD", 1, 0, 1, "Adjust fp", "");
    emitRM("JMP", 7, 0, 3, "Return", "");
    fprintf(code, "* END FUNCTION inputb\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION outputb\n");
    emitRM("ST", 3, -1, 1, "Store return address", "");
    emitRM("LD", 3, -2, 1, "Load parameter", "");
    emitRO("OUTB", 3, 3, 3, "Output bool", "");
    emitRM("LD", 3, -1, 1, "Load return address", "");
    emitRM("LD", 1, 0, 1, "Adjust fp", "");
    emitRM("JMP", 7, 0, 3, "Return", "");
    fprintf(code, "* END FUNCTION outputb\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION inputc\n");
    emitRM("ST", 3, -1, 1, "Store return address", "");
    emitRO("INC", 2, 2, 2, "Grab char input", "");
    emitRM("LD", 3, -1, 1, "Load return address", "");
    emitRM("LD", 1, 0, 1, "Adjust fp", "");
    emitRM("JMP", 7, 0, 3, "Return", "");
    fprintf(code, "* END FUNCTION inputc\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION outputc\n");
    emitRM("ST", 3, -1, 1, "Store return address", "");
    emitRM("LD", 3, -2, 1, "Load parameter", "");
    emitRO("OUTC", 3, 3, 3, "Output char", "");
    emitRM("LD", 3, -1, 1, "Load return address", "");
    emitRM("LD", 1, 0, 1, "Adjust fp", "");
    emitRM("JMP", 7, 0, 3, "Return", "");
    fprintf(code, "* END FUNCTION outputc\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION outnl\n");
    emitRM("ST", 3, -1, 1, "Store return address", "");
    emitRO("OUTNL", 3, 3, 3, "Output a newline", "");
    emitRM("LD", 3, -1, 1, "Load return address", "");
    emitRM("LD", 1, 0, 1, "Adjust fp", "");
    emitRM("JMP", 7, 0, 3, "Return", "");
    fprintf(code, "* END FUNCTION outnl\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
}