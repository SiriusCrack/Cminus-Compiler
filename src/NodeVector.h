#ifndef _VECTOR_GUARD
#define _VECTOR_GUARD
#include "ASTNode.h"

struct NodeVector {
    Node * nodePtr;
    struct NodeVector * next;
};

typedef struct NodeVector NodeVector;

NodeVector * NewNodeVector();
void AddToVector (NodeVector *, Node *);
Node * UnpackVector (NodeVector *, char *);

#endif