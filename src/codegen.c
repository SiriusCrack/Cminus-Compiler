#include "codegen.h"
#include <stdio.h>
#include <string.h>
#include "emitcode.h"

extern Node *AST;
extern FILE *code;
extern int goffset;

int toffset;
int mainAddress;
int stupidParamWorkaround = 0;

static void walkAST (Node *node);
static void walkChildren (Node *node);

static void generateCode (Node *node);
static void generateFunction (Node *node);
static void generateCompound (Node *node);
static void generateCall (Node *node);
static void generateCallParams (Node *node);
static void generateArrayDecl (Node *node);
static void generateID (Node *node);
static void generateReturn (Node *node);
static void generateAssign (Node *node);
static void generateOperator (Node *node);
static void generateUnaryOperator (Node *node);
static void generateConstant (Node *node);
static void generateIO ();
static void generateInit ();

void CodeGen() {
    toffset = 0;
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
        case ntCompoundwFunc: { generateCompound(node); break; }
        case ntCall: { generateCall(node); break; }
        case ntVar:
        case ntStaticVar:
        case ntVarArray: { generateArrayDecl(node); break; }
        case ntID: { generateID(node); break; }
        case ntReturn: { generateReturn(node); break; }
        case ntTrueAssign:
        case ntAssign: { generateAssign(node); break; }
        case ntAndOp:
        case ntOrOp:
        case ntRelOp:
        case ntOp: { generateOperator(node); break; }
        case ntSizeofOp:
        case ntSignOp:
        case ntQuestOp:
        case ntNotOp: { generateUnaryOperator(node); break; }
        case ntBoolConst:
        case ntNumConst:
        case ntCharConst:
        case ntStringConst: { generateConstant(node); break; }
    }
}

void generateFunction(Node *node) {
    int temptoffset = toffset;
    fprintf(code, "* FUNCTION %s\n", node->literal);
    toffset = node->size;
    fprintf(code, "* TOFF set: %d\n", toffset);
    node->tmAddress = emitWhereAmI();
    if(strcmp("main", node->literal) == 0) { mainAddress = node->tmAddress; }
    emitRM("ST", 3, -1, 1, "Store return address");
    walkChildren(node);
    fprintf(code, "* Add standard closing in case there is no return statement\n");
    emitRM("LDC", 2, 0, 6, "Set return value to 0");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    toffset = temptoffset; // correct? unclear
    // fprintf(code, "* TOFF set: %d\n", toffset); // not in examples
    fprintf(code, "* END FUNCTION %s\n", node->literal);
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

void generateCall(Node *node) { //probably finished
    fprintf(code, "* EXPRESSION\n");
    fprintf(code, "* CALL %s\n", node->entry->following->node->literal);
    int temptoffset = toffset;
    emitRM("ST", 1, toffset, 1, "Store fp in ghost frame for _");
    toffset--;
    fprintf(code, "* TOFF dec: %d\n", toffset);
    generateCallParams(node->child[0]);
    toffset--;
    fprintf(code, "* TOFF dec: %d\n", toffset);
    fprintf(code, "* Param end %s\n", node->entry->following->node->literal);
    toffset = temptoffset;
    emitRM("LDA", 1, toffset, 1, "Ghost frame becomes new active frame");
    emitRM("LDA", 3, 1, 7, "Return address in ac");
    if(node->entry == NULL) { printf("call0\n"); if(node->entry->following == NULL) { printf("call1\n"); if(node->entry->following->node == NULL) { printf("call2\n"); } } }
    int jumpAddress = -(emitWhereAmI() - node->entry->following->node->tmAddress);
    emitRM("JMP", 7, jumpAddress, 7, "CALL _");
    emitRM("LDA", 3, 0, 2, "Save the result in ac");
    fprintf(code, "* Call end %s\n", node->entry->following->node->literal);
    fprintf(code, "* TOFF set: %d\n", toffset);
}

void generateCallParams(Node *node) {
    if(node == NULL) { return; }
    toffset--;
    fprintf(code, "* TOFF dec: %d\n", toffset);
    fprintf(code, "* Param _\n");
    int temptoffset = toffset;
    stupidParamWorkaround = 1;
    generateCode(node);
    stupidParamWorkaround = 0;
    toffset = temptoffset;
    emitRM("ST", 3, toffset, 1, "Push parameter");
    //dec toffset again maybe?
    generateCallParams(node->sibling);
}

void generateArrayDecl(Node *node) {
    if(!node->isArray) { return; }
    int referenceType = 0;
    if(
        node->referenceType != rtGlobal &&
        node->nodeType != ntStaticVar
    ) { referenceType = 1; }
    emitRM("LDC", 3, node->size-1, 0, "");
    emitRM("ST", 3, node->location+1, referenceType, "");
}

void generateID(Node *node) { // figure out when to call
    if(!stupidParamWorkaround) { return; }
    if(node->nodeType != ntArrAd) { return; }
    int referenceType = 0;
    if(node->entry == NULL) { printf("ID0\n"); if(node->entry->following == NULL) { printf("ID1\n"); if(node->entry->following->node == NULL) { printf("ID2\n"); } } }
    if(
        node->referenceType != rtGlobal && 
        node->entry->following->node->nodeType != ntStaticVar
    ) { referenceType = 1; }
    emitRM("LD", 3, node->location, referenceType, "Load variable _");
}

void generateReturn(Node *node) {
    fprintf(code, "* RETURN\n");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
}

void generateAssign(Node *node) {
    if(!stupidParamWorkaround) {
        fprintf(code, "* EXPRESSION\n");
    }
    int temptoffset = toffset;
    walkAST(node->child[0]);
    // emitRM("ST", 3, toffset, 1, "ass");
    // if(stupidParamWorkaround) {
    //     toffset--;
    //     fprintf(code, "* TOFF dec: %d\n", toffset);
    // }
    walkAST(node->child[1]);
    // if(stupidParamWorkaround) {
    //     toffset++;
    //     fprintf(code, "* TOFF inc: %d\n", toffset);
    // }
    if(strlen(node->literal) > 1) {
        emitRM("LD", 4, toffset, 1, "fakeass");
        if(strcmp("+=", node->literal) == 0) { emitRO("ADD", 3, 4, 3, ""); } else
        if(strcmp("-=", node->literal) == 0) { emitRO("SUB", 3, 4, 3, ""); } else
        if(strcmp("++", node->literal) == 0) { emitRM("LDC", 3, 1, 0, ""); emitRO("ADD", 3, 4, 3, ""); } else
        if(strcmp("--", node->literal) == 0) { emitRM("LDC", 3, 1, 0, ""); emitRO("SUB", 3, 4, 3, ""); }
    }
    int address = 0;
    int referenceType = 0;
    if(node->child[0]->entry == NULL) { printf("ass0\n"); if(node->child[0]->entry->following == NULL) { printf("ass1\n"); if(node->child[0]->entry->following->node == NULL) { printf("ass2\n"); } } }
    if(node->child[0]->nodeType != ntArrAd) { address = node->child[0]->location; } 
    if(
        node->child[0]->referenceType != rtGlobal &&
        node->child[0]->entry->following->node->nodeType != ntStaticVar
    ) { referenceType = 1; }
    emitRM("ST", 3, address, referenceType, "Store variable _");
    toffset = temptoffset;
}

void generateOperator(Node *node) {
    walkAST(node->child[0]);
    emitRM("ST", 3, toffset, 1, "Push left side");
    toffset--;
    fprintf(code, "* TOFF dec: %d\n", toffset);
    walkAST(node->child[1]);
    toffset++;
    fprintf(code, "* TOFF inc: %d\n", toffset);
    emitRM("LD", 4, toffset, 1, "Pop left into ac1");
    switch(node->nodeType) {
        case ntAndOp: { emitRO("AND", 3, 4, 3, "Op AND"); break; }
        case ntOrOp: { emitRO("OR", 3, 4, 3, "Op OR"); break; }
        case ntRelOp: {
            if(strcmp("<", node->literal) == 0) { emitRO("TLT", 3, 4, 3, "Op <"); } else
            if(strcmp(">", node->literal) == 0) { emitRO("TGT", 3, 4, 3, "Op >"); } else
            if(strcmp("<=", node->literal) == 0) { emitRO("TLE", 3, 4, 3, "Op <="); } else
            if(strcmp(">=", node->literal) == 0) { emitRO("TGE", 3, 4, 3, "Op >="); } else
            if(strcmp("==", node->literal) == 0) { emitRO("TEQ", 3, 4, 3, "Op =="); } else
            if(strcmp("!=", node->literal) == 0) { emitRO("TNE", 3, 4, 3, "Op !="); }
            break;
        }
        case ntOp: {
            if(strcmp("+", node->literal) == 0) { emitRO("ADD", 3, 4, 3, "Op +"); } else
            if(strcmp("-", node->literal) == 0) { emitRO("SUB", 3, 4, 3, "Op -"); } else
            if(strcmp("*", node->literal) == 0) { emitRO("MUL", 3, 4, 3, "Op *"); } else
            if(strcmp("/", node->literal) == 0) { emitRO("DIV", 3, 4, 3, "Op /"); } else
            if(strcmp("%", node->literal) == 0) { emitRO("MOD", 3, 4, 3, "Op %"); }
            break;
        }
    }
}

void generateUnaryOperator(Node *node) {
    walkAST(node->child[0]);
    switch(node->nodeType) {
        case ntSizeofOp: { fprintf(code, "~~~~~~sizeof~~~~~~\n"); break; } //??
        case ntSignOp: { emitRO("NEG", 3, 3, 3, "Op unary -"); break; }
        case ntQuestOp: { emitRO("RND", 3, 3, 6, "Op ?"); break; }
        case ntNotOp: { emitRM("LDC", 4, 1, 6, "Load 1"); emitRO("XOR", 3, 3, 4, "Op XOR to get logical not"); break; }
    }
}

void generateConstant(Node *node) {
    switch(node->nodeType) {
        case ntBoolConst: { emitRM("LDC", 3, node->value.integer, 6, "Load Boolean constant"); break; }
        case ntNumConst: { emitRM("LDC", 3, node->value.integer, 6, "Load integer constant"); break; }
        case ntCharConst: { emitRM("LDC", 3, node->value.character, 6, "Load char constant"); break; }
    }
}

void generateInit() {
    fprintf(code, "%3d:  %5s  %lld,%lld(%lld)\t%s %s\n", 0, "JMP", 7, emitWhereAmI()-1, 7, "Jump to init [backpatch]", "");
    fprintf(code, "* INIT\n");
    emitRM("LDA", 1, goffset, 0, "set first frame at end of globals");
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