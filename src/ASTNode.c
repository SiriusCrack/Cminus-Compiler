#include "ASTNode.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int NodeUID;
extern int PrintDebugFlag;
extern int PrintTreeFlag;
extern int PrintAnnotatedTreeFlag;
extern int PrintPlacementTreeFlag;

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
        newNode->isIO = 0;
        newNode->hasReturn = 0;
        newNode->dataType = unknown;
        newNode->size = 0;
        newNode->location = 0;
        newNode->location = 0;
        newNode->referenceType = rtNone;
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

Node * AddSibling(Node * node, Node * sibling) {
    if(node == NULL) { return sibling; }
    else if(node->sibling != NULL) { AddSibling(node->sibling, sibling); }
    else {
        node->sibling = sibling;
        if(sibling != NULL) {
            sibling->prevSibling = node;
            sibling->siblingLevel = sibling->prevSibling->siblingLevel + 1;
        }
    }
    return node;
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

char const * IsArrayToASTString(int isArray) {
    switch(isArray) {
        case 1:
            return "is array ";
        default:
            return "";
    }
}

char const * IsArrayToOfString(int isArray) {
    switch(isArray) {
        case 1:
            return "array of ";
        default:
            return "";
    }
}

char const * IsStaticToString(ReferenceType referenceType) {
    switch(referenceType) {
        case rtStatic:
            return "static ";
        default:
            return "";
    }
}

char const * ReferenceTypeToMemPrint(ReferenceType referenceType) {
    switch(referenceType) {
        case rtLocal:
            return "Local";
        case rtGlobal:
            return "Global";
        case rtParameter:
            return "Parameter";
        case rtStatic:
            return "LocalStatic";
        case rtNone:
            return "None";
        default:
            return "unknown";
    }
}

char const * NodeTypeToString(NodeType nodeType) {
    switch(nodeType) {
        case ntIter:
            return "while";
        case ntIf:
            return "if";
        default:
            return "unknown";
    }
}

char const * DataTypeToString (DataType dataType) {
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

void SetDataType (char const *dataType, Node *node) { // depreciated. dataTypeliteral no longer used
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

void PrintPlacementTree (Node * AST, int level) {
    if(PrintPlacementTreeFlag != 1) {
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
                    printf("Var: %s of %s%stype %s ", cur->value.str, IsStaticToString(cur->referenceType), IsArrayToOfString(cur->isArray), cur->dataTypeLiteral);
                    break;
                case ntStaticVar:
                    printf("Var: %s of static %stype %s ", cur->value.str, IsArrayToOfString(cur->isArray), cur->dataTypeLiteral);
                    break;
                case ntFunc:
                    printf("Func: %s returns %s ", cur->value.str, DataTypeToString(cur->dataType));
                    break;
                case ntParm:
                    printf("Parm: %s of %s ", cur->value.str, DataTypeToString(cur->dataType));
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
                    printf("Id: %s of %s%stype %s ", cur->value.str, IsStaticToString(cur->entry->following->node->referenceType), IsArrayToOfString(cur->isArray), cur->entry->following->node->dataTypeLiteral);
                    break;
                case ntNumConst:
                    printf("Const %d of %s ", cur->value.integer, DataTypeToString(cur->dataType));
                    break;
                case ntCharConst:
                    printf("Const \'%c\' of %s ", cur->value.character, DataTypeToString(cur->dataType));
                    break;
                case ntStringConst:
                    printf("Const \"%s\" of array of %s ", cur->value.str, DataTypeToString(cur->dataType));
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
                    printf("Var: %s of array of type %s ", cur->value.str, cur->dataTypeLiteral);
                    break;
                case ntParmArray:
                    printf("Parm: %s of array of type %s ", cur->value.str, cur->dataTypeLiteral);
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

            if(cur->size != 0) printf("[mem: %s loc: %d size: %d] ", ReferenceTypeToMemPrint(cur->referenceType), cur->location, cur->size);
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
                    PrintPlacementTree(cur->child[c], level+1);
                }
            }
            cur = cur->sibling;
        } while (cur != NULL);
        return;
    }
}