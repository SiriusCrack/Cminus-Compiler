#include "ASTNode.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int NodeUID;
extern int PrintDebugFlag;
extern int PrintTreeFlag;
extern int PrintAnnotatedTreeFlag;

Node * NewNode (Token token, NodeType nodeType) {
    Node * newNode = (Node *) malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Out of memory error at line %d\n", token.lineNum);
        return NULL;
    } else {
        newNode->parent = NULL;
        int i;
        for (i = 0; i < AST_MAX_CHILDREN; i++) {
            newNode->child[i] = NULL;
        }
        newNode->childCount = 0;
        newNode->prevSibling = NULL;
        newNode->sibling = NULL;
        newNode->entry = NULL;
        newNode->UID = NodeUID;
        NodeUID = NodeUID+1;
        newNode->literal = strdup(token.literal);
        free(token.literal);
        newNode->tokenClass = token.tokenClass;
        newNode->lineNum = token.lineNum;
        newNode->siblingLevel = 0;
        newNode->nodeType = nodeType;
        newNode->isDecl = 0;
        newNode->isInitialized = 0;
        newNode->isArray = 0;
        newNode->isLoop = 0;
        newNode->isConst = 0;
        newNode->hasReturn = 0;
        newNode->dataType = unknown;
        switch (token.tokenClass) {
            case NUMCONST:
                newNode->value.integer = token.value.integer;
                break;
            case ID:
                newNode->value.str = strdup(token.value.str);
                free(token.value.str);
                break;
            case CHARCONST:
                newNode->value.character = token.value.character;
                break;
            case STRINGCONST:
                newNode->value.str = strdup(token.value.str);
                free(token.value.str);
                break;
            case BOOLCONST:
                newNode->value.integer = token.value.integer;
                break;
            default:
                newNode->value.str = strdup(token.value.str);
                free(token.value.str);
        }
        if(PrintDebugFlag == 1) printf("made node %s\n", newNode->literal);
        return newNode;
    }
}

Node * AddSibling (Node * treePtr, Node * newSibling) {
    if(treePtr == NULL) {
        if(PrintDebugFlag == 1) printf("started row with %s\n", newSibling->literal);
        treePtr->siblingLevel = 0;
        return newSibling;
    } else {
        Node * cur = treePtr;
        while(cur->sibling != NULL) {
            cur = cur->sibling;
        }
        newSibling->siblingLevel = cur->siblingLevel + 1;
        cur->sibling = newSibling;
        newSibling->prevSibling = cur;
        if(PrintDebugFlag == 1) printf("added %s as sibling to %s\n", newSibling->literal, cur->literal);
        cur = newSibling;
        int i = cur->siblingLevel;
        while(cur->sibling != NULL) { // walks to the end of siblingList, even though we should've just added the last sibling? seems redundant. oh well, it's worked so far...
            i = i + 1;
            cur = cur->sibling;
            cur->siblingLevel = i;
        }
        return treePtr;
    }
}

Node * AddChild (Node * treePtr, Node * newChild) {
    if(treePtr == NULL) {
        printf("adding child to null, dummy\n");
        return treePtr;
    } else {
        if(newChild != NULL) {
            treePtr->child[treePtr->childCount] = newChild;
            newChild->parent = treePtr;
            if(PrintDebugFlag == 1) printf("added %s as child to %s\n", newChild->literal, treePtr->literal);
        } else {
            if(PrintDebugFlag == 1) printf("added null as child to %s\n", treePtr->literal);
        }
        treePtr->childCount = treePtr->childCount+1;
        return treePtr;
    }
}

char * IsArrayToASTString(int isArray) {
    switch(isArray) {
        case 1:
            return "is array ";
        default:
            return "";
    }
}

char * NodeTypeToString(NodeType nodeType) {
    switch(nodeType) {
        case ntIter:
            return "while";
        case ntIf:
            return "if";
        default:
            return "unknown";
    }
}

char * DataTypeToString (DataType dataType) {
    switch(dataType) {
        case voidData:
            return "type void";
        case boolData:
            return "type bool";
        case charData:
            return "type char";
        case intData:
            return "type int";
        default:
            return "unknown";
    }
}

void SetDataType (char *dataType, Node *node) { // depreciated. dataTypeliteral no longer used
    if(strcmp(dataType, "void") == 0) {
        node->dataType = voidData;
    } else if(strcmp(dataType, "bool") == 0) {
        node->dataType = boolData;
    } else if(strcmp(dataType, "char") == 0) {
        node->dataType = charData;
    } else if(strcmp(dataType, "int") == 0) {
        node->dataType = intData;
    } else {
        printf("Attempted to set invalid datatype\n");
        return;
    }
    node->dataTypeLiteral = dataType;
}

void PrintTree (Node * AST, int level) {
    if(PrintTreeFlag != 1) {
        return;
    } else if(AST == NULL) {
        printf("empty tree\n");
        return;
    } else {
        Node * cur = AST;
        do {
            if(cur->siblingLevel > 0) {
                int i = 0;
                for(i = 0;i < level; i++) {
                    printf(".   ");
                }
                printf("Sibling: %d  ", cur->siblingLevel);
            }
            switch (cur->nodeType) {
                case ntVar:
                    if(cur->isDecl) {
                        printf("Var: %s of type %s ", cur->value.str, cur->dataTypeLiteral);
                    } else {
                        printf("Var: %s ", cur->value.str);
                    }
                    break;
                case ntStaticVar:
                    if(cur->isDecl) {
                        printf("Var: %s of static type %s ", cur->value.str, cur->dataTypeLiteral);
                    } else {
                        printf("Var: %s ", cur->value.str);
                    }
                    break;
                case ntFunc:
                    if(cur->isDecl) {
                        printf("Func: %s returns type %s ", cur->value.str, cur->dataTypeLiteral);
                    } else {
                        printf("Func: %s ", cur->value.str);
                    }
                    break;
                case ntParm:
                    if(cur->isDecl) {
                        printf("Parm: %s of type %s ", cur->value.str, cur->dataTypeLiteral);
                    } else {
                        printf("Parm: %s ", cur->value.str);
                    }
                    break;
                case ntCompound:
                    printf("Compound ");
                    break;
                case ntCompoundwFunc:
                    printf("Compound ");
                    break;
                case ntAssign:
                    printf("Assign: %s ", cur->value.str);
                    break;
                case ntTrueAssign:
                    printf("Assign: %s ", cur->value.str);
                    break;
                case ntID:
                    printf("Id: %s ", cur->value.str);
                    break;
                case ntNumConst:
                    printf("Const %d ", cur->value.integer);
                    break;
                case ntCharConst:
                    printf("Const \'%c\' ", cur->value.character);
                    break;
                case ntStringConst:
                    printf("Const \"%s\" ", cur->value.str);
                    break;
                case ntBoolConst:
                    if(cur->value.integer == 1) {
                        printf("Const true ");
                    } else {
                        printf("Const false ");
                    }
                    break;
                case ntReturn:
                    printf("Return ");
                    break;
                case ntOp:
                    printf("Op: %s ", cur->value.str);
                    break;
                case ntRelOp:
                    printf("Op: %s ", cur->value.str);
                    break;
                case ntCall:
                    printf("Call: %s ", cur->value.str);
                    break;
                case ntIf:
                    printf("If ");
                    break;
                case ntVarArray:
                    if(cur->isDecl) {
                        printf("Var: %s of array of type %s ", cur->value.str, cur->dataTypeLiteral);
                    } else {
                        printf("Var: %s ", cur->value.str);
                    }
                    break;
                case ntParmArray:
                    if(cur->isDecl) {
                        printf("Parm: %s of array of type %s ", cur->value.str, cur->dataTypeLiteral);
                    } else {
                        printf("Parm: %s ", cur->value.str);
                    }
                    break;
                case ntArrAd:
                    printf("Op: [ ");
                    break;
                case ntIter:
                    printf("While ");
                    break;
                case ntIterwComp:
                    printf("While ");
                    break;
                case ntTo:
                    printf("For ");
                    break;
                case ntTowComp:
                    printf("For ");
                    break;
                case ntBreak:
                    printf("Break ");
                    break;
                case ntRange:
                    printf("Range ");
                    break;
                case ntSignOp:
                    printf("Op: chsign ");
                    break;
                case ntNotOp:
                    printf("Op: not ");
                    break;
                case ntOrOp:
                    printf("Op: or ");
                    break;
                case ntAndOp:
                    printf("Op: and ");
                    break;
                case ntSizeofOp:
                    printf("Op: sizeof ");
                    break;
                case ntQuestOp:
                    printf("Op: ? ");
                    break;
                default:
                    printf("unknown node\n");
                    break;
                }
            printf("[line: %d]", cur->lineNum);
            printf("\n");
            int c;
            for(c = 0; c < cur->childCount; c++) {
                if(cur->child[c] != NULL) {
                    int i = 0;
                    for(i = 0;i < level+1; i++) {
                        printf(".   ");
                    }
                    printf("Child: %d  ", c);
                    PrintTree(cur->child[c], level+1);
                }
            }
            cur = cur->sibling;
        } while (cur != NULL);
        return;
    }
}

void PrintAnnotatedTree (Node * AST, int level) {
    if(PrintAnnotatedTreeFlag != 1) {
        return;
    } else if(AST == NULL) {
        printf("empty tree\n");
        return;
    } else {
        Node * cur = AST;
        do {
            if(cur->siblingLevel > 0) {
                int i = 0;
                for(i = 0;i < level; i++) {
                    printf(".   ");
                }
                printf("Sibling: %d  ", cur->siblingLevel);
            }
            switch (cur->nodeType) {
                case ntVar:
                    printf("Var: %s %sof type %s ", cur->value.str, IsArrayToASTString(cur->isArray), cur->dataTypeLiteral);
                    break;
                case ntStaticVar:
                    printf("Var: %s %sof type %s ", cur->value.str, IsArrayToASTString(cur->isArray), cur->dataTypeLiteral);
                    break;
                case ntFunc:
                    printf("Func: %s returns type %s ", cur->value.str, cur->dataTypeLiteral);
                    break;
                case ntParm:
                    printf("Parm: %s of type %s ", cur->value.str, cur->dataTypeLiteral);
                    break;
                case ntCompound:
                    printf("Compound ");
                    break;
                case ntCompoundwFunc:
                    printf("Compound ");
                    break;
                case ntAssign:
                    printf("Assign: %s of %s ", cur->value.str, DataTypeToString(cur->dataType));
                    break;
                case ntTrueAssign:
                    printf("Assign: %s of %s ", cur->value.str, DataTypeToString(cur->dataType));
                    break;
                case ntID:
                    printf("Id: %s of %s ", cur->value.str, DataTypeToString(cur->dataType));
                    break;
                case ntNumConst:
                    printf("Const %d of %s ", cur->value.integer, DataTypeToString(cur->dataType));
                    break;
                case ntCharConst:
                    printf("Const \'%c\' of %s ", cur->value.character, DataTypeToString(cur->dataType));
                    break;
                case ntStringConst:
                    printf("Const \"%s\" of %s ", cur->value.str, DataTypeToString(cur->dataType));
                    break;
                case ntBoolConst:
                    if(cur->value.integer == 1) {
                        printf("Const true of type bool ");
                    } else {
                        printf("Const false of type bool ");
                    }
                    break;
                case ntReturn:
                    printf("Return ");
                    break;
                case ntOp:
                    printf("Op: %s of %s ", cur->value.str, DataTypeToString(cur->dataType));
                    break;
                case ntRelOp:
                    printf("Op: %s of %s ", cur->value.str, DataTypeToString(cur->dataType));
                    break;
                case ntCall:
                    printf("Call: %s of %s ", cur->value.str, DataTypeToString(cur->dataType));
                    break;
                case ntIf:
                    printf("If ");
                    break;
                case ntVarArray:
                    printf("Var: %s is array of type %s ", cur->value.str, cur->dataTypeLiteral);
                    break;
                case ntParmArray:
                    printf("Parm: %s is array of type %s ", cur->value.str, cur->dataTypeLiteral);
                    break;
                case ntArrAd:
                    printf("Op: [ of %s ", DataTypeToString(cur->dataType));
                    break;
                case ntIter:
                    printf("While ");
                    break;
                case ntIterwComp:
                    printf("While ");
                    break;
                case ntTo:
                    printf("For ");
                    break;
                case ntTowComp:
                    printf("For ");
                    break;
                case ntBreak:
                    printf("Break ");
                    break;
                case ntRange:
                    printf("Range ");
                    break;
                case ntSignOp:
                    printf("Op: chsign of %s ", DataTypeToString(cur->dataType));
                    break;
                case ntNotOp:
                    printf("Op: not of %s ", DataTypeToString(cur->dataType));
                    break;
                case ntOrOp:
                    printf("Op: or of %s ", DataTypeToString(cur->dataType));
                    break;
                case ntAndOp:
                    printf("Op: and of %s ", DataTypeToString(cur->dataType));
                    break;
                case ntSizeofOp:
                    printf("Op: sizeof of %s ", DataTypeToString(cur->dataType));
                    break;
                case ntQuestOp:
                    printf("Op: ? of %s ", DataTypeToString(cur->dataType));
                    break;
                default:
                    printf("unknown node\n");
                    break;
                }
            printf("[line: %d]", cur->lineNum);
            printf("\n");
            int c;
            for(c = 0; c < cur->childCount; c++) {
                if(cur->child[c] != NULL) {
                    int i = 0;
                    for(i = 0;i < level+1; i++) {
                        printf(".   ");
                    }
                    printf("Child: %d  ", c);
                    PrintAnnotatedTree(cur->child[c], level+1);
                }
            }
            cur = cur->sibling;
        } while (cur != NULL);
        return;
    }
}