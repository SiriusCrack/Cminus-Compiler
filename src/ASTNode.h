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

typedef enum {
    rtUnknown,
    rtNone,
    rtLocal,
    rtGlobal,
    rtStatic,
    rtParameter
} ReferenceType;

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
    int isLoop;
    int isConst;
    int hasReturn;
    DataType dataType;
    int size;
    int location;
    ReferenceType referenceType;
    char *dataTypeLiteral; // should probably get rid of this, but would reworking PrintTree()
    
    // Data
    union {
        int integer;
        char character;
        char * str;
    } value;
};

Node * NewNode (Token, NodeType);
Node * AddSibling (Node * treePtr, Node * newSibling);
Node * AddChild (Node * treePtr, Node * newChild);
char * IsArrayToASTString(int isArray);
char * NodeTypeToString(NodeType nodeType);
char * DataTypeToString (DataType dataType);
void SetDataType (char *dataType, Node *node);
void PrintTree (Node *, int);
void PrintAnnotatedTree (Node *, int);
void PrintPlacementTree (Node *, int);
#endif