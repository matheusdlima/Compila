%{
    //  Etapa 2 - Compiladores 2024/1
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

%left '|' '&' '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'

%start program

%%
// Utils
type: KW_CHAR 
    | KW_INT  
    | KW_FLOAT
    | KW_BOOL 
    ;

literal: LIT_INT   
       | LIT_CHAR  
       | LIT_REAL  
       | LIT_FALSE 
       | LIT_TRUE
       ;

// Program
program: decList
       ;
        
decList: decGlobal decTail
       |
       ;

decGlobal: decGlobalVar ';'
         | decGlobalVec ';'
         | decFunc
         ;

decTail: decGlobal decTail
    | 
    ;

decGlobalVar: type TK_IDENTIFIER ':' literal 
            ;

decGlobalVec: type TK_IDENTIFIER '[' LIT_INT ']' initVec 
            ;

initVec: ':' literal litList
       |
       ;

litList: literal litList
       |
       ;

decFunc: type TK_IDENTIFIER '(' paramList ')' cmdBlock
       ;
        
paramList: param paramTail
         |
         ;

paramTail: ',' param paramTail
        |
        ;

param: type TK_IDENTIFIER
     ;

cmdBlock: '{' lCmd '}'
        ; 

lCmd: cmd lCmdTail
    ;

lCmdTail: ';' cmd lCmdTail
      | 
      ;

cmd: TK_IDENTIFIER '=' expr 
   | TK_IDENTIFIER '[' expr ']' '=' expr
   | KW_IF '(' expr ')' cmd
   | KW_IF '(' expr ')' cmd KW_ELSE cmd
   | KW_WHILE '(' expr ')' cmd   
   | KW_READ type TK_IDENTIFIER
   | KW_PRINT printElements
   | KW_RETURN expr
   | cmdBlock cmd
   |
   ;

printElements: LIT_STRING
             | type expr
             ;

expr: literal
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' expr ']'
    | TK_IDENTIFIER '(' argsList ')'
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr '&' expr
    | expr '|' expr
    | expr '~' expr
    | expr OPERATOR_DIF expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_LE expr
    ;

argsList: expr argsTail
        |
        ;

argsTail: ',' expr argsTail
       |
       ;

%%

int yyerror (char *message) {
    fprintf(stderr, "Syntax error detected at line %d.\n", getLineNumber());
    exit(3);
}
