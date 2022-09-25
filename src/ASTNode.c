#include "ASTNode.h"
#include "scanType.h"
#include "NodeVector.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node * NewNode (Token token) {
    Node * newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Out of memory error at line %d\n", token.lineNum);
        return NULL;
    } else {
        int i;
        for (i = 0; i < MAX_CHILDREN; i++) {
            newNode->child[i] = NULL;
        }
        newNode->sibling = NULL;
        newNode->tokenClass = token.tokenClass;
        newNode->lineNum = token.lineNum;
        newNode->siblingCount = 0;
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
        return newNode;
    }
}

Node * AddSibling (Node * treePtr, Node * newSibling) {
    if (treePtr == NULL) {
        treePtr = newSibling;
        return treePtr;
    } else {
        Node * cur = treePtr;
        while(cur->sibling != NULL) {
            cur = cur->sibling;
        }
        newSibling->siblingCount = cur->siblingCount + 1;
        cur->sibling = newSibling;
        return treePtr;
    }
}

Node * AddChild (Node * treePtr, Node * newChild) {
    if (treePtr == NULL) {
        printf("adding child to null, dummy\n");
        return treePtr;
    } else{
        Node * cur = treePtr;
        int i = 0;
        while(cur->child[i] != NULL) {
            i++;
        }
        cur->child[i] = newChild;
        return treePtr;
    }
}

void PrintAST (Node * AST, int level) {
    if (AST == NULL) {
        printf("empty tree\n");
        return;
    } else {
        Node * cur = AST;
        do {
            if (cur->siblingCount > 0) {
                int i = 0;
                for(i = 0;i < level; i++) {
                    printf(".   ");
                }
                printf("Sibling: %d  ", cur->siblingCount);
            }
            switch (cur->nodeType) {
                case ntVar:
                    printf("Var: %s of type %s ", cur->value.str, cur->dataType);
                    break;
                case ntFunc:
                    printf("Func: %s returns type %s ", cur->value.str, cur->dataType);
                    break;
                case ntParm:
                    printf("Parm: %s of type %s ", cur->value.str, cur->dataType);
                    break;
                case ntCompound:
                    printf("Compound ");
                    break;
                case ntAssign:
                    printf("Assign: = ");
                    break;
                case ntID:
                    printf("Id: %s ", cur->value.str);
                    break;
                case ntConst:
                    printf("Const %d ", cur->value.integer);
                    break;
                case ntReturn:
                    printf("Return ", cur->value.integer);
                    break;
                default:
                    printf("unknown node\n");
                    break;
                }
            printf("[line: %d]", cur->lineNum);
            printf("\n");
            int c = 0;
            while(cur->child[c] != NULL) {
                int i = 0;
                for(i = 0;i < level+1; i++) {
                    printf(".   ");
                }
                printf("Child: %d  ", c);
                PrintAST(cur->child[c], level+1);
                c++;
            }
            cur = cur->sibling;
        } while (cur != NULL);
        return;
    }
}