#ifndef _ASTNODE_H_
#define _ASTNODE_H_
#include "Token.h"
#include "SymbolTable.h"

#define AST_MAX_CHILDREN 3

typedef enum {
    ntVar,
    ntStaticVar,
    ntFunc, 
    ntParm, 
    ntCompound,
    ntCompoundwFunc,
    ntAssign,
    ntTrueAssign,
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
    ntRelOp,
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

typedef struct SymbolTableEntry SymbolTableEntry;

typedef struct Node Node;
struct Node {
    // Connections
    Node * parent;
    Node * child[AST_MAX_CHILDREN];
    int childCount;
    Node * prevSibling;
    Node * sibling;
    SymbolTableEntry * entry;

    // Info
    int UID;
    char * literal;
    int tokenClass;
    int lineNum;
    int siblingLevel;
    NodeType nodeType;
    int isDecl;
    int isInitialized;
    int isArray;
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
char * DataTypeToString (DataType dataType);
void SetDataType (char *dataType, Node *node);
void PrintTree (Node *, int);
void PrintAnnotatedTree (Node *, int);
#endif