//  Etapa 1 - Compiladores 2024/1
//      Autor: Matheus Lima 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

HASH_NODE*Table[HASH_SIZE];

void hashInit(){
    int i;
    
    for (i = 0; i < HASH_SIZE; i++)
        Table[i] = 0;
}

int hashAddress(char *text){
    int i;
    int address = 1;
    
    for (i = 0; i < strlen(text); i++)
        address = (address * text[i]) % HASH_SIZE + 1;

    return address - 1;
}

HASH_NODE *hashFind(char *text){
    HASH_NODE *node;
    int address = hashAddress(text);

    for (node = Table[address]; node; node = node-> next){
        if (strcmp(node->text, text) == 0){
            return node;
        }
    }
    return NULL;        
}

HASH_NODE *hashInsert(char *text, int type){
    int address;
    HASH_NODE *newNode;
    
    address = hashAddress(text);
    
    if ((newNode = hashFind(text)) != 0)
        return newNode;

    newNode = (HASH_NODE*) calloc(1 , sizeof(HASH_NODE));

    newNode->type = type;
    newNode->text = (char*) calloc(strlen(text)+1, sizeof(char));

    strcpy(newNode->text, text);
    newNode->next = Table[address];

    Table[address] = newNode;

    return newNode;
}

void hashPrint(){
    int i;
    HASH_NODE *node;

    for (i = 0; i < HASH_SIZE; i++)
        for (node = Table[i]; node; node = node->next)
            printf("Table[%d] has %s\n", i, node->text);
}