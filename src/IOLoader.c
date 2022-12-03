#include "IOLoader.h"
#include <stdio.h>
#include <string.h>

extern ScopeTable * SymbolTable;

Node * fudgeNode (char const * literal, NodeType nodeType) {
    Token token;
    token.tokenClass = ID;
    token.lineNum = -1;
    token.literal = strdup(literal);
    token.value.str = strdup(literal);
    return NewNode(token, nodeType);
}

Node * fudgeTable (Node * node, ScopeTable * table) {
    ScopeTable * newScope = table;
    if(node->nodeType == ntFunc) {
        node->isDecl = 1;
        node->isInitialized = 1;
        node->dataType = voidData;
        newScope = NewScope(node);
        newScope->isIO = 1;
        AddChildScope(table, newScope);
    } else if (node->nodeType == ntParm) {
        node->isDecl = 1;
        SymbolTableEntry * newEntry = NewEntry(node);
        AddEntryToScope(newEntry, newScope);
    }
    int i;
    for(i = 0; i < AST_MAX_CHILDREN; i++) {
        if(node->child[i] != NULL) {
            fudgeTable(node->child[i], newScope);
        }
    }
    if(node->sibling != NULL) {
        fudgeTable(node->sibling, table);
    }
    return NULL;
}

Node * LoadIO () {
    Node * tree;
    tree = fudgeNode("input", ntFunc);
    AddSibling(tree, fudgeNode("inputb", ntFunc));
    AddSibling(tree, fudgeNode("inputc", ntFunc));
    AddSibling(tree, fudgeNode("output", ntFunc));
    AddChild(tree->sibling->sibling->sibling, fudgeNode("*dummy*", ntParm));
    AddSibling(tree, fudgeNode("outputb", ntFunc));
    AddChild(tree->sibling->sibling->sibling->sibling, fudgeNode("*dummy*", ntParm));
    AddSibling(tree, fudgeNode("outputc", ntFunc));
    AddChild(tree->sibling->sibling->sibling->sibling->sibling, fudgeNode("*dummy*", ntParm));
    AddSibling(tree, fudgeNode("outnl", ntFunc));
    fudgeTable(tree, SymbolTable);
    tree->dataType = intData;
    return tree;
}
