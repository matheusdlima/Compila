%{
    //  Etapa 1 - Compiladores 2024/1
    //      Autor: Matheus Lima  

    #include <stdio.h>
	#include <stdlib.h>

    int yylex();
	int yyerror(char *message);
    extern int getLineNumber();
%}

%token KW_CHAR      
%token KW_INT       
%token KW_FLOAT     
%token KW_BOOL      

%token KW_IF        
%token KW_ELSE      
%token KW_WHILE     
%token KW_READ      
%token KW_PRINT     
%token KW_RETURN    

%token OPERATOR_LE  
%token OPERATOR_GE  
%token OPERATOR_EQ  
%token OPERATOR_DIF 

%token TK_IDENTIFIER

%token LIT_INT      
%token LIT_CHAR     
%token LIT_REAL     
%token LIT_FALSE    
%token LIT_TRUE     
%token LIT_STRING   

%token TOKEN_ERROR

%%

programa:  decl
        ;
        
decl: dec resto
    |
    ;

resto: ',' dec resto
    | 
    ;

dec: KW_INT TK_IDENTIFIER
   |  KW_INT TK_IDENTIFIER '(' ')' body
        
        
body: '{' lcmd '}'
    ; 

lcmd: cmd lcmd
    |
    ;

cmd: TK_IDENTIFIER '=' expr 
    ;

expr: LIT_INT
    | TK_IDENTIFIER
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr OPERATOR_DIF expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_LE expr
    | '(' expr ')'
    ;

%%

int yyerror (char *message) {
    fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
    exit(3);
}

