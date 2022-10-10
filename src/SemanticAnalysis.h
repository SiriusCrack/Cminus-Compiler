#ifndef _SEMANTICANALYSIS_H_
#define _SEMANTICANALYSIS_H_
#include "ASTNode.h"
#include "SymbolTable.h"

void WriteScopes (Node * tree, ScopeTable * table);
void WriteRefs (Node * tree, ScopeTable * table);
void CheckMain (ScopeTable *table);
void CheckUse (ScopeTable *table);
#endif