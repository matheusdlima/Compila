%{
    //  Etapa 3 - Compiladores 2024/1
    //      Autor: Matheus Lima                   

    #include "hash.h"
    #include "ast.h"
    #include "y.tab.h"

    int Running     = 1;
    int lineNumber  = 1;
%}

alfa        [A-Za-z_]
alfanumeric [a-zA-Z0-9_]+
numeric     [0-9]+
identifier  {alfa}({alfanumeric}*)
string      \"([^"\n]|\\.)*[^\\]\"

%x COMMENT

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
     
[-+*/,;:()\[\]{}%<>&|~=]  { return yytext[0]; }

"<="      { return OPERATOR_LE; } 
">="      { return OPERATOR_GE; } 
"=="      { return OPERATOR_EQ; } 
"!="      { return OPERATOR_DIF; } 

"false"                                         { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_FALSE); return LIT_FALSE; } 
"true"                                          { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_TRUE); return LIT_TRUE; } 

{identifier}                                    { yylval.symbol = hashInsert(yytext, SYMBOL_IDENTIFIER); return TK_IDENTIFIER; } 

{numeric}                                       { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_INTEGER);
                                                      return LIT_INT; } 
'.'                                             { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_CHAR); return LIT_CHAR; } 
{numeric}+\.{numeric}*|{numeric}*\.{numeric}+   { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_REAL); return LIT_REAL; } 
{string}                                        { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_STRING); return LIT_STRING; }

[ \t]
"\n"   { lineNumber ++; }

"//".*
"/*"        { BEGIN(COMMENT); }

. { return TOKEN_ERROR; } 

<COMMENT>"*/"  { BEGIN(INITIAL); }
<COMMENT>"\n"  { lineNumber ++; }
<COMMENT>.

%%

int isRunning(void){
	return Running;
}

int getLineNumber(void){
	return lineNumber;
}

void initMe(void){
    hashInit();
}

int yywrap(){
    Running = 0;
    return 1;
}