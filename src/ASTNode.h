#ifndef _ASTNODE_H_
#define _ASTNODE_H_
#include "Token.h"

#define AST_MAX_CHILDREN 3

typedef enum {
    ntVar,
    ntStaticVar,
    ntFunc, 
    ntParm, 
    ntCompound,
    ntCompoundwFunc,
    ntAssign,
    ntID,
    ntNumConst,
    ntCharConst,
    ntStringConst,
    ntBoolConst,
    ntReturn,
    ntOp, 
    ntCall,
    ntIf,
    ntVarArray,
    ntParmArray,
    ntIter,
    ntIterwComp,
    ntTo,
    ntTowComp,
    ntAssignInc,
    ntAssignDec,
    ntBreak,
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
    Node * parent;
    Node * child[AST_MAX_CHILDREN];
    int childCount;
    Node * prevSibling;
    Node * sibling;

    // Info
    int UID;
    char * literal;
    int tokenClass;
    int lineNum;
    int siblingLevel;
    NodeType nodeType;
    int isDecl;
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
Node * NewNode (Token, NodeType);
Node * AddSibling (Node *, Node *);
Node * AddChild (Node *, Node *);
void PrintTree (Node *, int);
#endif