//  Etapa 3 - Compiladores 2024/1
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
    if (newNode->type == SYMBOL_LIT_CHAR) 
        newNode->dataType = DATATYPE_CHAR;
    else if (newNode->type == SYMBOL_LIT_INTEGER) 
        newNode->dataType = DATATYPE_INT;
    else if (newNode->type == SYMBOL_LIT_REAL) 
        newNode->dataType = DATATYPE_REAL;
    else if (newNode->type == SYMBOL_LIT_STRING) 
        newNode->dataType = DATATYPE_STRING;
    else if (newNode->type == SYMBOL_LIT_FALSE || newNode->type == SYMBOL_LIT_TRUE) 
        newNode->dataType = DATATYPE_BOOL;

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
            printf("Table[%d] has %s of type %d and data type %d\n", i, node->text, node->type, node->dataType);
}

int hashCheckUndeclared(){
    int i;
    int undeclared = 0;
    HASH_NODE *node;

    for (i = 0; i < HASH_SIZE; i++){
        for (node = Table[i]; node; node = node->next){
            if (node->type == SYMBOL_IDENTIFIER){
                fprintf(stderr,"Error %s\n", node->text);
                undeclared++;
            }
        }
    }
    return undeclared;
}

HASH_NODE *makeTemp(){
    static int serial = 0;
    char buffer[256] = "";

    sprintf(buffer, "mYWeeirT_emp%d", serial++);
    return hashInsert(buffer, SYMBOL_VARIABLE);
}

HASH_NODE *makeLabel(){
    static int serial = 0;
    char buffer[256] = "";

    sprintf(buffer, "mYLabe_l%d", serial++);
    return hashInsert(buffer, SYMBOL_LABLE);
}
