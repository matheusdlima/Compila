//  Etapa 1 - Compiladores 2024/1
//      Autor: Matheus Lima                  

#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

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