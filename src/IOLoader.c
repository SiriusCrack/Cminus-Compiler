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
    Node *node = NewNode(token, nodeType);
    node->isIO = 1;
    return node;
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
    tree->dataType = intData;
    AddSibling(tree, fudgeNode("output", ntFunc));
    tree->sibling->dataType = voidData;
    AddChild(tree->sibling, fudgeNode("*dummy*", ntParm));
    tree->sibling->child[0]->dataType = intData;

    AddSibling(tree, fudgeNode("inputb", ntFunc));
    tree->sibling->sibling->dataType = boolData;
    AddSibling(tree, fudgeNode("outputb", ntFunc));
    tree->sibling->sibling->sibling->dataType = voidData;
    AddChild(tree->sibling->sibling->sibling, fudgeNode("*dummy*", ntParm));
    tree->sibling->sibling->sibling->child[0]->dataType = boolData;

    AddSibling(tree, fudgeNode("inputc", ntFunc));
    tree->sibling->sibling->sibling->sibling->dataType = charData;
    AddSibling(tree, fudgeNode("outputc", ntFunc));
    tree->sibling->sibling->sibling->sibling->sibling->dataType = voidData;
    AddChild(tree->sibling->sibling->sibling->sibling->sibling, fudgeNode("*dummy*", ntParm));
    tree->sibling->sibling->sibling->sibling->sibling->child[0]->dataType = charData;

    AddSibling(tree, fudgeNode("outnl", ntFunc));
    tree->sibling->sibling->sibling->sibling->sibling->sibling->dataType = voidData;

    fudgeTable(tree, SymbolTable);
    tree->dataType = intData;
    return tree;
}
