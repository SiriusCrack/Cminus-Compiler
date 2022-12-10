#include "codegen.h"
#include <stdio.h>
#include <string.h>
#include "emitcode.h"

extern Node *AST;
extern FILE * code;

int toffset = 0;
int returnAddress = 0;
int mainAddress = 0;

static void walkAST (Node *node);
static void walkChildren (Node *node);

static void generateCode (Node *node);
static void generateFunction (Node *node);
static void generateCompound (Node *node);
static void generateCall (Node *node);
static void generateCallParam (Node *node);
static void generateReturn (Node *node);
static void generateAssign (Node *node);
static void generateConstant (Node *node);
static void generateIO ();
static void generateInit ();

void CodeGen() {
    generateIO();
    walkAST(AST);
    generateInit();
}

void walkAST(Node * node) {
    if(node == NULL) { return; }
    if(node->isIO) { walkAST(node->sibling); return; }
    generateCode(node);
    walkAST(node->sibling);
}

void walkChildren(Node *node) {
    for(int child = 0; child < AST_MAX_CHILDREN; child++) {
        walkAST(node->child[child]);
    }
}

void generateCode(Node * node) {
    switch(node->nodeType) {
        case ntFunc: { generateFunction(node); break; }
        case ntCompound:
        case ntCompoundwFunc: { generateFunction(node); break; }
        case ntCall: { generateCall(node); break; }
        case ntReturn: { generateReturn(node); break; }
        case ntTrueAssign: { generateAssign(node); break; }
        case ntNumConst: { generateConstant(node); break; }
    }
}

void generateFunction(Node *node) {
    int temptoffset = toffset;
    fprintf(code, "* FUNCTION %s\n", node->literal);
    toffset = node->size;
    fprintf(code, "* TOFF set: %d\n", toffset);
    returnAddress = emitWhereAmI();
    if(strcmp("main", node->literal) == 0) { mainAddress = returnAddress; }
    emitRM("ST", 3, -1, 1, "Store return address");
    walkChildren(node);
    fprintf(code, "* Add standard closing in case there is no return statement\n");
    emitRM("LDC", 2, 0, 6, "Set return value to 0");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    fprintf(code, "* END FUNCTION %s\n", node->literal);
    toffset = temptoffset;
}

void generateCompound(Node *node) {
    fprintf(code, "* COMPOUND\n");
    int temptoffset = toffset;
    toffset = node->size;
    fprintf(code, "* TOFF set: %d\n", toffset);
    fprintf(code, "* Compound Body\n");
    walkChildren(node);
    toffset = temptoffset;
    fprintf(code, "* TOFF set: %d\n", toffset);
    fprintf(code, "* END COMPOUND\n");
}

void generateCall(Node *node) {
    // ghostframe call jump return thing not correct
    fprintf(code, "* EXPRESSION\n");
    fprintf(code, "* CALL %s\n", node->entry->following->node->literal);
    int ghostFrame = -emitWhereAmI();
    emitRM("ST", 1, toffset, 1, "Store fp in ghost frame for _");
    int temptoffset = toffset;
    toffset--;
    fprintf(code, "* TOFF dec: %d\n", toffset);
    walkChildren(node);
    toffset--;
    fprintf(code, "* TOFF dec: %d\n", toffset);
    fprintf(code, "* Param end %s\n", node->entry->following->node->literal);
    toffset = temptoffset;
    emitRM("LDA", 1, toffset, 1, "Ghost frame becomes new active frame");
    emitRM("LDA", 3, 1, 7, "Return address in ac");
    emitRM("JMP", 7, ghostFrame, 7, "CALL _");
    emitRM("LDA", 3, 0, 2, "Save the result in ac");
    fprintf(code, "* Call end %s\n", node->entry->following->node->literal);
    fprintf(code, "* TOFF set: %d\n", toffset);
}

void generateCallParam(Node *node) {
    if(node == NULL) { return; }
    toffset--;
    fprintf(code, "* TOFF dec: %d\n", toffset);
    fprintf(code, "* Param 1\n");
    if(node->nodeType == ntID) {
        emitRM("LD", 3, -2, 1, "Load variable _");
        emitRM("ST", 3, toffset, 1, "Push parameter");
        return;
    }
    switch(node->dataType) {
        case intData:
            emitRM("LDC", 3, node->value.integer, 6, "Load integer constant");
            emitRM("ST", 3, toffset, 1, "Push parameter");
            break;
        case boolData:
            emitRM("LDC", 3, node->value.integer, 6, "Load Boolean constant");
            emitRM("ST", 3, toffset, 1, "Push parameter");
            break;
    }
}

void generateReturn(Node *node) {
    fprintf(code, "* RETURN\n");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
}

void generateAssign(Node *node) {
    fprintf(code, "* EXPRESSION\n");
    emitRM("LDC", 3, node->child[1]->value.integer, 6, "Load integer constant");
    emitRM("ST", 3, toffset, 1, "Store variable _");
}

void generateConstant(Node *node) {
    fprintf(code, "* EXPRESSION\n");
    emitRM("LDC", 3, node->value.integer, 6, "Load integer constant");
}

void generateInit() {
    fprintf(code, "%3d:  %5s  %lld,%lld(%lld)\t%s %s\n", 0, "JMP", 7, emitWhereAmI()-1, 7, "Jump to init [backpatch]", "");
    fprintf(code, "* INIT\n");
    emitRM("LDA", 1, 0, 0, "set first frame at end of globals");
    emitRM("ST", 1, 0, 1, "store old fp (point to self)");
    fprintf(code, "* INIT GLOBALS AND STATICS\n");
    fprintf(code, "* END INIT GLOBALS AND STATICS\n");
    emitRM("LDA", 3, 1, 7, "Return address in ac");
    emitRM("JMP", 7, mainAddress-(emitWhereAmI()+1), 7, "Jump to main");
    emitRO("HALT", 0, 0, 0, "DONE!");
    fprintf(code, "* END INIT\n");
}

void generateIO() {
    emitSkip(1);
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION input\n");
    emitRM("ST", 3, -1, 1, "Store return address");
    emitRO("IN", 2, 2, 2, "Grab int input");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    fprintf(code, "* END FUNCTION input\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION output\n");
    emitRM("ST", 3, -1, 1, "Store return address");
    emitRM("LD", 3, -2, 1, "Load parameter");
    emitRO("OUT", 3, 3, 3, "Output integer");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    fprintf(code, "* END FUNCTION output\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION inputb\n");
    emitRM("ST", 3, -1, 1, "Store return address");
    emitRO("INB", 2, 2, 2, "Grab bool input");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    fprintf(code, "* END FUNCTION inputb\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION outputb\n");
    emitRM("ST", 3, -1, 1, "Store return address");
    emitRM("LD", 3, -2, 1, "Load parameter");
    emitRO("OUTB", 3, 3, 3, "Output bool");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    fprintf(code, "* END FUNCTION outputb\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION inputc\n");
    emitRM("ST", 3, -1, 1, "Store return address");
    emitRO("INC", 2, 2, 2, "Grab char input");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    fprintf(code, "* END FUNCTION inputc\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION outputc\n");
    emitRM("ST", 3, -1, 1, "Store return address");
    emitRM("LD", 3, -2, 1, "Load parameter");
    emitRO("OUTC", 3, 3, 3, "Output char");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    fprintf(code, "* END FUNCTION outputc\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
    fprintf(code, "* FUNCTION outnl\n");
    emitRM("ST", 3, -1, 1, "Store return address");
    emitRO("OUTNL", 3, 3, 3, "Output a newline");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    fprintf(code, "* END FUNCTION outnl\n");
    fprintf(code, "* \n");
    fprintf(code, "* ** ** ** ** ** ** ** ** ** ** ** **\n");
}