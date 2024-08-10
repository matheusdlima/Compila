//  Etapa 6 - Compiladores 2024/1
//      Autor: Matheus Lima                  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashFunc.h"

void hashFuncPrint();

void hashFuncInit(void){
    int i;

    for(i = 0; i < HASHFUNC_SIZE; i++)
        TableFunc[i] = 0;
}

HASHFUNC_NODE *hashFuncInsert(char* name){
    int address;
    HASHFUNC_NODE * node;

    address = hashFuncAddress(name);
    node = (HASHFUNC_NODE*) calloc(1, sizeof(HASHFUNC_NODE));

    node->name = (char*) calloc(strlen(name)+1, sizeof(char));
    strcpy(node->name, name);

    node->firstArg = NULL;
    TableFunc[address] = node;
    
    fprintf(stderr, "hashFuncInsert %s %s\n", name, TableFunc[address]->name);

    return node;
}

int hashFuncAddress(char *name){
    int i;
    int address = 1;

    for (i = 0; i < strlen(name); i++){
        address = (address * name[i]) % HASHFUNC_SIZE + 1;
    }
    
    fprintf(stderr, "hashFuncAddress %s %d\n", name, address -1);

    return address - 1;
}

void setNewArg(char *argName, HASHFUNC_NODE* node){
  argFunc *arg = node->firstArg;
  if (arg == NULL) {
    node->firstArg = (argFunc*) malloc(sizeof(argFunc));
    arg = node->firstArg;
  } else {
    while (arg->next != NULL){
      arg = arg->next;
    }
    arg->next = (argFunc*) malloc(sizeof(argFunc));
    arg = arg->next;
  }
  
  arg->next = NULL;
  arg->name = calloc(strlen(argName) + 1, sizeof(char));
  strcpy(arg->name, argName);
}

HASHFUNC_NODE **getTableFunc(){
    return TableFunc;
}

HASHFUNC_NODE *getFuncNode(char *name){
    HASHFUNC_NODE *node;
    int address = hashFuncAddress(name);
    hashFuncPrint();
    fprintf(stderr, "getFuncNode achou %s %s\n", name, TableFunc[address]->name);

    // for (node = TableFunc[address]; node; node = node->firstArg){
    //     if (strcmp(node->name, name) == 0){
    //         fprintf(stderr, "getFuncNode achou %s %s\n", name, node->name);
            
    //         return node;
    //     }
    // }

    return TableFunc[address];
}

void hashFuncPrint(){
    int i;
    HASHFUNC_NODE *node;

    for (i = 0; i < HASHFUNC_SIZE; i++){
        fprintf(stderr, "hashFuncPrint achou %d\n", i);

        //printf("Table[%d] has %s of type %d and data type %d\n", i, TableFunc[i]->name, TableFunc[i]->type, TableFunc[i]->dataType);
        }
}
