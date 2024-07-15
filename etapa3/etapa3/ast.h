// AST - Abstract Syntax Tree
//      Autor: Matheus Lima

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 4

#define AST_SYMBOL     1
#define AST_ADD        2
#define AST_SUB        3
#define AST_MUL        4
#define AST_DIV        5
#define AST_LT         6
#define AST_GT         7
#define AST_LE         8
#define AST_GE         9
#define AST_EQ         10
#define AST_DIF        11
#define AST_AND        12
#define AST_OR         13
#define AST_NOT        14
#define AST_ATTR       15
#define AST_ATTRVEC    16
#define AST_LCMD       17
#define AST_IF         18
#define AST_IFELSE     19  
#define AST_WHILE      20 
#define AST_READ       21 
#define AST_PRINT      22 
#define AST_RETURN     23 
#define AST_PARENT     24 
#define AST_ARGSLST    25 
#define AST_ARGSTAIL   26 
#define AST_TPCHAR     27 
#define AST_TPINT      28 
#define AST_TPFLOAT    29 
#define AST_TPBOOL     30 
#define AST_LDEC       31 
#define AST_DECVAR     32 
#define AST_DECVEC     33 
#define AST_DECFUNC    34 
#define AST_DECGVAR    35 
#define AST_DECGVEC    36 
#define AST_DECGFUNC   37 
#define AST_DECTAIL    38 
#define AST_INITVEC    39 
#define AST_LISTVEC    40 
#define AST_PARAMLIST  41 
#define AST_PARAMTAIL  42 
#define AST_PARAM      43 
#define AST_CMDBLOCK   44
#define AST_VEC        45
#define AST_FUNC       46
#define AST_TYPEPRINT  47
#define AST_SEMICOLON  48

typedef struct astnode
{
    int type;
    HASH_NODE *symbol;
    struct astnode *son[MAX_SONS];
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST *node, int level);
void astUncompile(AST *root, FILE *file);

#endif
