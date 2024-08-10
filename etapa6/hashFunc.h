//  Etapa 6 - Compiladores 2024/1
//      Autor: Matheus Lima                  

#ifndef HASHFUNCTION_HEADER
#define HASHFUNCTION_HEADER

#define HASHFUNC_SIZE 997

#define SYMBOL_LIT_INTEGER   1
#define SYMBOL_LIT_REAL      2
#define SYMBOL_LIT_CHAR      3
#define SYMBOL_LIT_STRING    4
#define SYMBOL_LIT_FALSE     5
#define SYMBOL_LIT_TRUE      6
#define SYMBOL_IDENTIFIER    7
#define SYMBOL_VARIABLE      8
#define SYMBOL_FUNCTION      9
#define SYMBOL_VECTOR       10
#define SYMBOL_PARAM        11
#define SYMBOL_LABLE        12

#define DATATYPE_CHAR   1
#define DATATYPE_INT    2
#define DATATYPE_REAL   3
#define DATATYPE_STRING 4
#define DATATYPE_BOOL   5

typedef struct argFunc{
  char *name;
  struct argFunc *next;
} argFunc;

typedef struct hashFunc_node{
    int type;
    int dataType;
    char *name;
    struct argFunc *firstArg;
} HASHFUNC_NODE;

HASHFUNC_NODE *TableFunc[HASHFUNC_SIZE];
void hashFuncInit();
HASHFUNC_NODE *hashFuncInsert(char* name);
int hashFuncAddress(char *name);
void setNewArg(char * argName, HASHFUNC_NODE* node);

HASHFUNC_NODE **getTableFunc();
HASHFUNC_NODE *getFuncNode(char *name);

#endif