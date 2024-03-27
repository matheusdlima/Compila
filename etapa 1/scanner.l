%{
    //  Etapa 1 - Compiladores 2024/1
    //      Matheus Lima                   
    
    //#include "main.c"
    #include "tokens.h"

    int running = 1;
/* identifier  { return TK_IDENTIFIER; } 

 { return LIT_INT; } 
 { return LIT_CHAR; } 
 { return LIT_REAL; } 
 { return LIT_FALSE; } 
 { return LIT_TRUE; } 
 { return LIT_STRING; } */
%}

alfa        [A-Za-z_]
alfanumeric [a-zA-Z0-9_]+
identifier  {alfa}({alfanumeric}*)

%%

char    { return KW_CHAR; } 
int     { return KW_INT; } 
float   { return KW_FLOAT; } 
bool    { return KW_BOOL; } 

if      { return KW_IF; } 
else    { return KW_ELSE; } 
while   { return KW_WHILE; } 
read    { return KW_READ; } 
print   { return KW_PRINT; } 
return  { return KW_RETURN; } 
     
[-+*/,;:()][{}%<>&|~=]  { return yytext[0]; }

"<="      { return OPERATOR_LE; } 
">="      { return OPERATOR_GE; } 
"=="      { return OPERATOR_EQ; } 
"!="      { return OPERATOR_DIF; } 

[ \t]

. { return TOKEN_ERROR; } 




%%

int main (int argc, char **argv){
int tok;

while (running){
    tok = yylex();
    if (running == 0) break;

    switch (tok){
        case KW_INT: printf("Encontrei KW_INT\n"); break;
        case KW_FLOAT: printf("Encontrei KW_FLOAT\n"); break;
        case TOKEN_ERROR: printf("ERROR\n"); break;
        default: printf("Encontrei %c\n", yytext[0]); break;
    }
}

printf("Main done!\n");

}

int yywrap(){
    running = 0;
    return 1;
}