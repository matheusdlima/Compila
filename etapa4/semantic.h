// Semantic

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdbool.h>
#include "hash.h"
#include "ast.h"

extern int SemanticErrors;

int checkSemantics(AST* root);
void checkAndSetDeclarations(AST *node);
void checkUndeclared();
void checkOperands(AST *node);
void setNodeTypes(AST *node);
void checkNature(AST *node);
void checkFunc(AST *node);
void checkReturnTypes(AST *node);
void isValidReturn(AST *node, int nodeDataType, char nodeName[20]);

int getSemanticErrors();
int setDataType(int sonType);
int isCompatibleDataType(int dt1, int dt2);
int isInteger(int dt);
int isNumerical(int dt);
bool checkVectorElements(AST *node, int dt, int vectorLenght,int nElements, char *nameVector);
void printCheck(AST *node);
void auxPrintCheck(AST *node);
int isRelationalOp(int nodetype);
int isAritmeticOp(int nodetype);
int isLogicalOp(int nodetype);
AST* getDecFunc(char *name, AST *node);
bool verifyArgumentsCount(AST *node, AST *decFunc);
int getArgumentsCount(AST *node);
void calledArgsCompare(AST *node, AST *decFunc, char funcName[20]);

#endif