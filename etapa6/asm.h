//  Etapa 6 - Compiladores 2024/1
//      Autor: Matheus Lima 

#ifndef ASM_H
#define ASM_H

#include "tacs.h"
#include "ast.h"

// ASM GENERATION
TAC* tacReverse(TAC *tac);
void setVariablesValues(FILE *out, AST* node);
void generateASM(TAC* first, AST *root);

#endif