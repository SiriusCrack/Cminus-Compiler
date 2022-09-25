#ifndef _NODE_GUARD
#define _NODE_GUARD
#include "scanType.h"

#define MAX_CHILDREN 3

struct Node {
    // Connections
    struct Node * child[MAX_CHILDREN];
    struct Node * sibling;

    // Info
    int tokenClass;
    int lineNum;
    int siblingCount;
    char * nodeType;
    // Optional
    char * dataType;
    
    // Data
    union {
        int integer;
        char character;
        char * str;
    } value;
};

typedef struct Node Node;

Node * NewNode (Token);
Node * AddSibling (Node *, Node *);
void PrintAST (Node *);
#endif