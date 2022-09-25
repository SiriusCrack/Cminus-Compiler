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
    if (vector->nodePtr == NULL) {
        vector->nodePtr = newNode;
        return;
    } else if (vector->next == NULL) {
        vector->next = NewNodeVector();
        vector->next->nodePtr = newNode;
        return;
    } else {
        NodeVector * cur = vector;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = NewNodeVector();
        cur->next->nodePtr = newNode;
        return;
    }
}

void UnpackVector (NodeVector * nodeVector, char * data) {
    NodeVector * prev = NULL;
    NodeVector * cur = nodeVector;
    while (cur != NULL) {
        cur->nodePtr->dataType = data;
        printf("stored %s in %s\n", data, cur->nodePtr->value.str);
        prev = cur;
        if (cur->next != NULL) {
            cur = cur->next;
        } else {
            cur = NULL;
        }
        free(prev);
    }
}