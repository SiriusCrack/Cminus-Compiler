#ifndef _SEMANTICANALYSIS_H_
#define _SEMANTICANALYSIS_H_
#include "ASTNode.h"
#include "SymbolTable.h"

void WriteScopes (Node * tree, ScopeTable * table);
int IsScope (Node * node);
#endif