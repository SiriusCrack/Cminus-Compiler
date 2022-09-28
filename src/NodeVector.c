#include "NodeVector.h"
#include <stdio.h>
#include <stdlib.h>

NodeVector * NewNodeVector() {
    NodeVector * newNodeVector = (NodeVector *) malloc(sizeof(NodeVector));
    newNodeVector->nodePtr = NULL;
    newNodeVector->next = NULL;
    return newNodeVector;
}

void AddToVector (NodeVector * vector, Node * newNode) {
    NodeVector * prev = NULL;
    if(vector->nodePtr == NULL) {
        vector->nodePtr = newNode;
        printf("added %s to empty vector\n", newNode->literal);
    } else if(vector->next == NULL) {
        vector->next = NewNodeVector();
        prev = vector;
        vector->next->nodePtr = newNode;
        printf("added %s to %s vector\n", newNode->literal, vector->nodePtr->literal);
    } else {
        NodeVector * cur = vector;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = NewNodeVector();
        prev = cur;
        cur->next->nodePtr = newNode;
        printf("added %s to %s vector after %s\n", newNode->literal, vector->nodePtr->literal, cur->nodePtr->literal);
    }
    if(prev != NULL) {
        prev->nodePtr = AddSibling(prev->nodePtr, newNode);
    }
}

Node * UnpackVector (NodeVector * nodeVector, char * data) {
    NodeVector * prev = NULL;
    NodeVector * cur = nodeVector;
    Node * rootNode = nodeVector->nodePtr;
    while (cur != NULL) {
        cur->nodePtr->dataType = data;
        printf("stored %s in %s\n", data, cur->nodePtr->value.str);
        prev = cur;
        if(cur->next != NULL) {
            cur = cur->next;
        } else {
            cur = NULL;
        }
        prev->nodePtr = NULL;
        prev->next = NULL;
        free(prev);
    }
    return rootNode;
}