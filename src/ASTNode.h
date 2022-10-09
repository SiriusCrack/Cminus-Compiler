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

typedef enum {
    unknown,
    voidData,
    boolData,
    charData,
    intData
} DataType;

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
    DataType dataType;
    char *dataTypeLiteral; // should probably get rid of this, but would reworking PrintTree()
    
    // Data
    union {
        int integer;
        char character;
        char * str;
    } value;
};

Node * NewNode (Token, NodeType);
Node * AddSibling (Node *, Node *);
Node * AddChild (Node *, Node *);
void SetDataType (char *dataType, Node *node);
void PrintTree (Node *, int);
#endif