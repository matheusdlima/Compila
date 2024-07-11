%{
    //  Etapa 3 - Compiladores 2024/1
    //      Autor: Matheus Lima  

    #include <stdio.h>
	#include <stdlib.h>
    #include "hash.h"
    #include "ast.h"

    int yylex();
	int yyerror(char *message);
    extern int getLineNumber();    

    AST *root;
%}

%union{
    HASH_NODE *symbol;
    AST *ast;
}

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

%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INT      
%token<symbol> LIT_CHAR     
%token<symbol> LIT_REAL     
%token<symbol> LIT_FALSE    
%token<symbol> LIT_TRUE     
%token<symbol> LIT_STRING   

%token TOKEN_ERROR

%type<ast> program
%type<ast> decList
%type<ast> decGlobal
%type<ast> decTail
%type<ast> decGlobalVar
%type<ast> decGlobalVec
%type<ast> initVec
%type<ast> litList
%type<ast> decFunc
%type<ast> paramList
%type<ast> paramTail
%type<ast> param
%type<ast> cmdBlock
%type<ast> lCmd
%type<ast> cmd
%type<ast> printElements
%type<ast> expr
%type<ast> argsList
%type<ast> argsTail

%type<symbol> type
%type<symbol> literal


%left '|' '&' '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'

%start program

%%
// Utils
type: KW_CHAR       { $$ = astCreate(AST_TPCHAR, 0, 0, 0, 0, 0); }
    | KW_INT        { $$ = astCreate(AST_TPINT, 0, 0, 0, 0, 0); }
    | KW_FLOAT      { $$ = astCreate(AST_TPFLOAT, 0, 0, 0, 0, 0); }
    | KW_BOOL       { $$ = astCreate(AST_TPBOOL, 0, 0, 0, 0, 0); }
    ;

literal: LIT_INT    { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
       | LIT_CHAR   { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); } 
       | LIT_REAL   { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); } 
       | LIT_FALSE  { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
       | LIT_TRUE   { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); } 
       ;

// Program
program: decList        { root = $$; astPrint(root, 0); }
       ;
        
decList: decGlobal decTail      { $$ = astCreate(AST_LDEC, 0, $1, $2, 0, 0); }
       |                        { $$ = 0; }
       ;

decGlobal: decGlobalVar ';'     { $$ = astCreate(AST_DECGVAR, 0, $1, 0, 0, 0); }
         | decGlobalVec ';'     { $$ = astCreate(AST_DECGVEC, 0, $1, 0, 0, 0); }
         | decFunc              { $$ = astCreate(AST_DECGFUNC, 0, $1, 0, 0, 0); }
         ;

decTail: decGlobal decTail      { $$ = astCreate(AST_DECTAIL, 0, $1, $2, 0, 0); }
       |                        { $$ = 0; }
       ;

decGlobalVar: type TK_IDENTIFIER ':' literal        { $$ = astCreate(AST_DECVAR, $2, $1, $4, 0, 0); }
            ;

decGlobalVec: type TK_IDENTIFIER '[' LIT_INT ']' initVec        { $$ = astCreate(AST_DECVEC, $2, $1, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $6, 0); }
            ;

initVec: ':' literal litList    { $$ = astCreate(AST_INITVEC, 0, $2, $3, 0, 0);}
       |                        { $$ = 0; }
       ;

litList: literal litList	{ $$ = astCreate(AST_LISTVEC, 0, $1, $2, 0, 0); }
       |                    { $$ = 0; }
       ;

decFunc: type TK_IDENTIFIER '(' paramList ')' cmdBlock      { $$ = astCreate(AST_DECFUNC, $2, $1, $4, $6, 0); }
       ;
        
paramList: param paramTail      { $$ = astCreate(AST_PARAMLIST, 0, $1, $2, 0, 0); }
         |                      { $$ = 0; }
         ;

paramTail: ',' param paramTail      { $$ = astCreate(AST_PARAMTAIL, 0, $2, $3, 0, 0);}
        |                           { $$ = 0; }
        ;

param: type TK_IDENTIFIER       { $$ = astCreate(AST_PARAM, $2, $1, 0, 0, 0); }
     ;

cmdBlock: '{' lCmd '}'      { $$ = astCreate(AST_CMDBLOCK, 0, $2, 0, 0, 0); }
        ; 

lCmd: cmd lCmd      { $$ = astCreate(AST_LCMD,0,$1,$2,0,0);}
    |               { $$ = 0;}
    ;
      
cmd: TK_IDENTIFIER '=' expr ';'                 { $$ = astCreate(AST_ATTR, $1, $3, 0, 0, 0); }
   | TK_IDENTIFIER '[' expr ']' '=' expr ';'    { $$ = astCreate(AST_ATTRVEC, $1, $3, $6, 0, 0); }
   | KW_IF '(' expr ')' cmd                     { $$ = astCreate(AST_IF, 0, $3, $5, 0, 0); }
   | KW_IF '(' expr ')' cmd KW_ELSE cmd         { $$ = astCreate(AST_IFELSE, 0, $3, $5, $7, 0); }
   | KW_WHILE '(' expr ')' cmd                  { $$ = astCreate(AST_WHILE, 0, $3, $5, 0, 0); }
   | KW_READ type TK_IDENTIFIER ';'             { $$ = astCreate(AST_READ, $3, $2, 0, 0, 0); }
   | KW_PRINT printElements ';'                 { $$ = astCreate(AST_PRINT, 0, $2, 0, 0, 0); }
   | KW_RETURN expr ';'                         { $$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0); }
   | cmdBlock                                   { $$ = $1; }
   | ';'                                        { $$ = astCreate(AST_SEMICOLON, 0, 0, 0, 0, 0);; }
   ;

printElements: LIT_STRING       { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
             | type expr        { $$ = astCreate(AST_TYPEPRINT, 0, $1, $2, 0, 0); }
             ;

expr: literal                           { $$ = $1; }
    | TK_IDENTIFIER                     { $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
    | TK_IDENTIFIER '[' expr ']'        { $$ = astCreate(AST_VEC,$1,$3,0,0,0); }
    | TK_IDENTIFIER '(' argsList ')'    { $$ = astCreate(AST_FUNC,$1,0,0,0,0); }
    | expr '+' expr                     { $$ = astCreate(AST_ADD,0,$1,$3,0,0);}
    | expr '-' expr                     { $$ = astCreate(AST_SUB,0,$1,$3,0,0);}
    | expr '*' expr                     { $$ = astCreate(AST_MUL, 0, $1, $3, 0, 0); }
    | expr '/' expr                     { $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0); }
    | expr '<' expr                     { $$ = astCreate(AST_LT, 0, $1, $3, 0, 0); }
    | expr '>' expr                     { $$ = astCreate(AST_GT, 0, $1, $3, 0, 0); }
    | expr OPERATOR_LE expr             { $$ = astCreate(AST_LE, 0, $1, $3, 0, 0); }
    | expr OPERATOR_GE expr             { $$ = astCreate(AST_GE, 0, $1, $3, 0, 0); }
    | expr OPERATOR_EQ expr             { $$ = astCreate(AST_EQ, 0, $1, $3, 0, 0); }
    | expr OPERATOR_DIF expr            { $$ = astCreate(AST_DIF, 0, $1, $3, 0, 0); }
    | expr '&' expr                     { $$ = astCreate(AST_AND, 0, $1, $3, 0, 0); }
    | expr '|' expr                     { $$ = astCreate(AST_OR, 0, $1, $3, 0, 0); }
    | '~' expr                          { $$ = astCreate(AST_NOT, 0, $2, 0, 0, 0); }
    | '(' expr ')'                      { $$ = astCreate(AST_PARENT, 0, $2, 0, 0, 0); }
    ;

argsList: expr argsTail     { $$ = astCreate(AST_ARGSLST, 0, $1, $2, 0, 0); }
        |                   { $$ = 0; }
        ;

argsTail: ',' expr argsTail     { $$ = astCreate(AST_ARGSTAIL, 0, $2, $3, 0, 0); }
       |                        { $$ = 0; }
       ;

%%

int yyerror (char *message) {
    fprintf(stderr, "Syntax error detected at line %d.\n", getLineNumber());
    exit(3);
}

AST* getAST(){
	return root;
}