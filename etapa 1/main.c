//  Etapa 1 - Compiladores 2024/1
//      Autor: Matheus Lima  

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

int yylex();
extern char *yytext;
extern FILE *yyin;

extern void initMe(void);
extern int  getLineNumber(void);
extern int  isRunning(void);
extern void hashPrint(void);

int main (int argc, char **argv){
    int token;

	if (argc < 2){
		fprintf(stderr, "Call: ./etapa1 input.txt\n");
		exit(1);
    }

    if ((yyin = fopen(argv[1], "r")) == 0){
        fprintf(stderr, "Fail to open file %s\n", argv[1]);
		exit(1);
    }

    initMe();

    while (isRunning()){
        token = yylex();
        if (isRunning() == 0) break;

        switch (token){
            case KW_INT:   printf("Find KW_INT\n"); break;
            case KW_FLOAT: printf("Find KW_FLOAT\n"); break;
            case KW_CHAR:  printf("Find KW_CHAR\n"); break;
            case KW_BOOL:  printf("Find KW_BOOL\n"); break;
            
            case KW_IF:     printf("Find KW_IF\n"); break;
            case KW_ELSE:   printf("Find KW_ELSE\n"); break;
            case KW_WHILE:  printf("Find KW_WHILE\n"); break;
            case KW_READ:   printf("Find KW_READ\n"); break;
            case KW_PRINT:  printf("Find KW_PRINT\n"); break;
            case KW_RETURN: printf("Find KW_RETURN\n"); break;
            
            case OPERATOR_LE:  printf("Find OPERATOR_LE\n"); break;
            case OPERATOR_GE:  printf("Find OPERATOR_GE\n"); break;
            case OPERATOR_EQ:  printf("Find OPERATOR_EQ\n"); break;
            case OPERATOR_DIF: printf("Find OPERATOR_DIF\n"); break;

            case TK_IDENTIFIER: printf("Find TK_IDENTIFIER\n"); break;

            case LIT_INT:    printf("Find LIT_INT\n"); break;
            case LIT_CHAR:   printf("Find LIT_CHAR\n"); break;
            case LIT_REAL:   printf("Find LIT_REAL\n"); break;
            case LIT_STRING: printf("Find LIT_STRING\n"); break;
            case LIT_FALSE:  printf("Find LIT_FALSE\n"); break;
            case LIT_TRUE:   printf("Find LIT_TRUE\n"); break;
            
            case TOKEN_ERROR: printf("ERROR\n"); break;
            default: printf("Find %c\n", yytext[0]); break;
        }
    }
    printf("Main done!\n");
    printf("File has %d lines\n", getLineNumber());
    
    printf("\nPrinting HashTable:\n");
    hashPrint();

    exit(0);
}