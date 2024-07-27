//  Etapa 5 - Compiladores 2024/1
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
extern int checkSemanticErrors();

int main (int argc, char **argv){
    int token;
    FILE *output;

	if (argc < 3){
		fprintf(stderr, "Call: ./etapa4 input.txt output.txt\n");
		exit(1);
    }

    if ((yyin = fopen(argv[1], "r")) == 0){
        fprintf(stderr, "Fail to open file %s\n", argv[1]);
		exit(2);
    }

    if ((output = fopen(argv[2], "w+")) == 0){
        fprintf(stderr, "Fail to open file %s\n", argv[2]);
		exit(2);
    }

    initMe();

    yyparse();
    
    printf("\nPrinting HashTable:\n");
    hashPrint();

    fprintf(stderr, "\nUncompiling!\n");

	astUncompile(getAST(), output);

    fprintf(stderr, "Uncompiling finished!\n");

	fclose(output);

    checkSemanticErrors();
    
    printf("\nCompilation succefull with no semantic errors!\n");
    printf("File has %d lines\n", getLineNumber());

    return 0;
}