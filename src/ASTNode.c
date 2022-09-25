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
                newNode->value.str = token.value.str;
        }
        return newNode;
    }
}

Node * AddSibling (Node * AST, Node * newSibling) {
    if (AST == NULL) {
        AST = newSibling;
        return AST;
    } else {
        Node * cur = AST;
        while(cur->sibling != NULL) {
            cur = AST->sibling;
        }
        newSibling->siblingCount = cur->siblingCount + 1;
        cur->sibling = newSibling;
        return AST;
    }
}

void PrintAST (Node * AST) {
    if (AST == NULL) {
        printf("empty tree\n");
        return;
    } else {
        Node * cur = AST;
        do {
            if (cur->siblingCount > 0) {
                printf("Sibling: %d ", cur->siblingCount);
            }
            printf("%s: ", cur->nodeType);
            printf("%s of type %s ", cur->value.str, cur->dataType);
            printf("[line: %d]", cur->lineNum);
            printf("\n");
            cur = cur->sibling;
        } while (cur != NULL);
        return;
    }
}