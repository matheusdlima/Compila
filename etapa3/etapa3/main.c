//  Etapa 3 - Compiladores 2024/1
//      Autor: Matheus Lima  

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex();
extern char *yytext;
extern FILE *yyin;

extern void initMe(void);
extern int  getLineNumber(void);
extern int  isRunning(void);
extern void hashPrint(void);
extern int  yyparse(void);
extern AST *getAST(void);

int main (int argc, char **argv){
    int token;
    FILE *output;

	if (argc < 3){
		fprintf(stderr, "Call: ./etapa3 input.txt output.txt\n");
		exit(1);
    }

    if ((yyin = fopen(argv[1], "r")) == 0){
        fprintf(stderr, "Fail to open file %s\n", argv[1]);
		exit(1);
    }

    if ((output = fopen(argv[2], "w+")) == 0){
        fprintf(stderr, "Fail to open file %s\n", argv[2]);
		exit(1);
    }

    initMe();

    yyparse();

    printf("Compilation succefull!\n");
    printf("File has %d lines\n", getLineNumber());
    
    //printf("\nPrinting HashTable:\n");
    //hashPrint();

    fprintf(stderr, "Uncompiling!\n");

	astUncompile(getAST(), output);

    fprintf(stderr, "Uncompiling finished!\n");

	fclose(output);

    exit(0);
}