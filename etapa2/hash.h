//  Etapa 2 - Compiladores 2024/1
//      Autor: Matheus Lima                  

#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

#define SYMBOL_LIT_INTEGER   1
#define SYMBOL_LIT_REAL      2
#define SYMBOL_LIT_CHAR      3
#define SYMBOL_LIT_STRING    4
#define SYMBOL_LIT_LIT_FALSE 5
#define SYMBOL_LIT_LIT_TRUE  6
#define SYMBOL_IDENTIFIER    7

typedef struct hash_node{
    int type;
    char *text;
    struct hash_node* next;
} HASH_NODE;

void hashInit();
int  hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint();

#endif