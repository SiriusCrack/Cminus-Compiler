#ifndef _NODE_GUARD
#define _NODE_GUARD
#include "scanType.h"

#define MAX_CHILDREN 3

typedef enum {
    ntVar, 
    ntFunc, 
    ntParm, 
    ntCompound, 
    ntAssign, 
    ntID, 
    ntConst, 
    ntReturn, 
    ntEmpty, 
    ntOp, 
    ntCall,
    ntIf,
    ntVarArray,
    ntParmArray,
    ntIter,
    ntAssignInc,
    ntAssignDec
} NodeType;

typedef struct Node Node;
struct Node {
    // Connections
    Node * child[MAX_CHILDREN];
    Node * sibling;

    // Info
    char * literal;
    int tokenClass;
    int lineNum;
    int siblingCount;
    NodeType nodeType;
    // Optional
    char * dataType;
    
    // Data
    union {
        int integer;
        char character;
        char * str;
    } value;
};


Node * NewNode (Token);
Node * AddSibling (Node *, Node *);
Node * AddChild (Node *, Node *);
void PrintTree (Node *, int, int);
char * NodeTypeToString(NodeType);
#endif