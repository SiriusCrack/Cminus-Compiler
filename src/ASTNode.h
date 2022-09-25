#include "scanType.h"

#define MAX_CHILDREN 3

#ifndef NODE_GUARD
#define NODE_GUARD

struct Node {
    // Connections
    struct Node * child[MAX_CHILDREN];
    struct Node * sibling;

    // Info
    int tokenClass;
    int lineNum;
    int siblingCount;
    char * nodeType;
    
    // Data
    union {
        int integer;
        char character;
        char * str;
    } value;
};

typedef struct Node Node;
#endif

Node * NewNode (Token);
Node * AddSibling (Node *, Node *);
void PrintAST (Node *);