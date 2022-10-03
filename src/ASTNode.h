#ifndef _NODE_GUARD
#define _NODE_GUARD
#include "Token.h"

#define MAX_CHILDREN 3

typedef enum {
    ntVar,
    ntStaticVar,
    ntFunc, 
    ntParm, 
    ntCompound, 
    ntAssign,
    ntID,
    ntNumConst,
    ntCharConst,
    ntBoolConst,
    ntReturn,
    ntOp, 
    ntCall,
    ntIf,
    ntVarArray,
    ntParmArray,
    ntIter,
    ntAssignInc,
    ntAssignDec,
    ntBreak,
    ntTo,
    ntRange,
    ntSignOp,
    ntNotOp,
    ntOrOp,
    ntAndOp,
    ntArrAd,
    ntSizeofOp,
    ntQuestOp
} NodeType;

typedef struct Node Node;
struct Node {
    // Connections
    Node * child[MAX_CHILDREN];
    int childCount;
    Node * sibling;

    // Info
    char * literal;
    int tokenClass;
    int lineNum;
    int siblingLevel;
    NodeType nodeType;
    // optional
    char * dataType;
    
    // Data
    union {
        int integer;
        char character;
        char * str;
    } value;
};

void specPrint(char *);
Node * NewNode (Token, NodeType, int);
Node * AddSibling (Node *, Node *, int);
Node * AddChild (Node *, Node *, int);
void PrintTree (Node *, int, int);
#endif