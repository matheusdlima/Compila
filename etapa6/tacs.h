//  Etapa 5 - Compiladores 2024/1
//      Autor: Matheus Lima 

#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL  1
#define TAC_ADD     2
#define TAC_COPY    3
#define TAC_JFALSE  4
#define TAC_LABEL   5
#define TAC_SUB     6
#define TAC_MUL     7
#define TAC_DIV     8 
#define TAC_GREAT   9 
#define TAC_LESS    10
#define TAC_EQ      11
#define TAC_GE      12
#define TAC_LE      13
#define TAC_DIF     14
#define TAC_AND     15
#define TAC_OR      16
#define TAC_NOT     17
#define TAC_CALL    18
#define TAC_ARG     19
#define TAC_VEC     20
#define TAC_ATTRVEC 21  
#define TAC_BEGINFUN  22
#define TAC_ENDFUN    23
#define TAC_READ      24
#define TAC_PRINT     25
#define TAC_RETURN    26
#define TAC_JUMP      27

typedef struct tac_node{
    int type;
    HASH_NODE * res;
    HASH_NODE * op1;
    HASH_NODE * op2;
    struct tac_node* prev;
    struct tac_node* next;
} TAC;

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC* tac);
TAC* tacJoin(TAC* l1, TAC* l2);

// CODE GENERATION
TAC* generateCode(AST *node, HASH_NODE *currentWhileLabel);

#endif