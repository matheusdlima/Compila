//  Etapa 1 - Compiladores 2024/1
//      Autor: Matheus Lima  

#include <stdio.h>
#include <stdlib.h>

int yylex();
extern char *yytext;
extern FILE *yyin;

extern void initMe(void);
extern int  getLineNumber(void);
extern int  isRunning(void);
extern void hashPrint(void);
extern int  yyparse(void);

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

    yyparse();

    printf("Compilation succefull!\n");
    printf("File has %d lines\n", getLineNumber());
    
    printf("\nPrinting HashTable:\n");
    hashPrint();

    exit(0);
}