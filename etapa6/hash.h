//  Etapa 3 - Compiladores 2024/1
//      Autor: Matheus Lima                  

#include <stdio.h>

#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

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

typedef struct hash_node{
    int type;
    int dataType;
    char *text;
    struct hash_node* next;
} HASH_NODE;

void hashInit();
int  hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint();
int hashCheckUndeclared();
HASH_NODE *makeTemp();
HASH_NODE *makeLabel();

// ASM GENERATE FUNCTIONS
void printASM(FILE* fout);
void setLitValues(FILE* fout);
char* remove_quotes(const char *str);
void setLitStrings(FILE* fout);

#endif