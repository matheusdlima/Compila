//  Etapa 6 - Compiladores 2024/1
//      Autor: Matheus Lima 

#include <stdio.h>
#include <string.h>
#include "asm.h"
#include "semantic.h"
#include "ast.h"
#include "hash.h"

// ASM GENERATION
TAC* tacReverse(TAC *tac){
    TAC* t = tac;

    for (t = tac; t->prev; t = t->prev){
        t->prev->next = t;
    }

    return t;
}

void setVariablesValues(FILE *fout, AST* node){
    if (!node) return;

    int charData;

	if (node->type == AST_DECVAR) { 
		if(node->son[0]->type == AST_TPFLOAT) {
			fprintf(fout, "_FLOAT%s:\t.float	%s\n", node->symbol->text, node->son[1]->symbol->text);
		} else if (node->son[0]->type == AST_TPINT) {
			fprintf(fout, "_INT%s:\t.long	%s\n", node->symbol->text, node->son[1]->symbol->text);
		} else if (node->son[0]->type == AST_TPBOOL) {
			fprintf(fout, "_%s%s:\t.long	%d\n", strcmp(node->son[1]->symbol->text, "true") ? "FALSE" : "TRUE", node->symbol->text, strcmp(node->son[1]->symbol->text, "true") ? 0 : 1);
		} else if (node->son[0]->type == AST_TPCHAR) {
            if (node->son[1]->symbol->text[0] == '\'')
                charData = (int)(node->son[1]->symbol->text[1]);
            else charData = atoi(node->son[1]->symbol->text);

			fprintf(fout, "_CHAR%s:\t.long	%d\n", node->symbol->text, charData);
		}
	} 
    // else if (node->type == AST_PARAM){  // Params are global variables!
    	
    //     if(node->son[0]->type == AST_TPFLOAT) {
	// 		fprintf(fout, "\t.float	0\n");
	// 	}
	// 	else {
	// 		fprintf(fout, "\t.long	0\n");
	// 	}
    //} 
    else if(node->type == AST_DECVEC){
        if (node->son[2]){
            fprintf(fout,
            "\t.globl\t_%s\n"
            "_%s:\n", node->symbol->text, node->symbol->text);
        }

        for(AST* aux = node->son[2]; aux; aux = aux->son[1]) {
            if(node->son[0]->type == AST_TPFLOAT){
                fprintf(fout, "\t.float	%s\n", aux->son[0]->symbol->text);
		    } else {
                fprintf(fout, "\t.long	%s\n", aux->son[0]->symbol->text);
            }
        }
	}

	for(int i = 0; i < MAX_SONS; i++){
		setVariablesValues(fout, node->son[i]);
	}
}

void generateASM(TAC* first, AST *root){
    FILE *fout;

    fout = fopen("out.s", "w");

    // Init
    fprintf(fout, "## FIXED INIT\n"
    ".section	__TEXT,__cstring,cstring_literals\n"
    "printIntStr: .asciz	\"%%d\\n\"\n"
    "printFloatStr: .asciz	\"%%f\\n\"\n"
	"printStr: .asciz	\"%%s\\n\"\n");
    setLitStrings(fout);
    fprintf(fout, "\n.section	__TEXT,__text,regular,pure_instructions\n\n");

    // Each TAC

    for (TAC* tac = first; tac; tac = tac->next){
        switch (tac->type){
            case TAC_BEGINFUN: 
                fprintf(fout, 
                "## TAC_BEGINFUN\n"                     
                    "\t.globl	_%s\n"
                "_%s:\n"                  
                    "\tpushq	%%rbp\n"
                    "\tmovq	%%rsp, %%rbp\n\n", tac->res->text, tac->res->text);
                break;
            case TAC_ENDFUN: 
                fprintf(fout, 
                "## TAC_ENDFUN\n"
                    "\tpopq	%%rbp\n"
                    "\tretq\n\n");
                break;
            case TAC_PRINT:
                if (tac->res->dataType == DATATYPE_INT) { 
                    fprintf(fout, 
                    "## TAC_PRINTINT\n"
                        "\tleaq	printIntStr(%%rip), %%rdi\n"
                        "\tmovl	_INT%s(%%rip), %%esi\n"
                        "\tmovb	$0, %%al\n"
                        "\tcallq	_printf\n\n", tac->res->text);
                } else if (tac->res->dataType == DATATYPE_CHAR){
                   fprintf(fout, 
                    "## TAC_PRINTCHAR\n"
                        "\tleaq	printIntStr(%%rip), %%rdi\n"
                        "\tmovl	_CHAR%d(%%rip), %%esi\n"
                        "\tmovb	$0, %%al\n"
                        "\tcallq	_printf\n\n", tac->res->text[1]); 
                } else if (tac->res->dataType == DATATYPE_REAL){
                    fprintf(fout, 
                    "## TAC_PRINTREAL\n"
                        "\tmovss	_FLOAT%s(%%rip), %%xmm0\n"
                        "\tcvtss2sd	%%xmm0, %%xmm0\n"
                        "\tleaq	printFloatStr(%%rip), %%rdi\n"
                        "\tmovb	$1, %%al\n"
                        "\tcallq	_printf\n"
                        "\txorl	%%eax, %%eax\n\n", tac->res->text);
                } else if (tac->res->dataType == DATATYPE_BOOL){
                    fprintf(fout, 
                    "## TAC_PRINTBOOL\n"
                        "\tmovb	_BOOL%s(%%rip), %%al\n"
                        "\tandb	$1, %%al\n"
                        "\tmovzbl	%%al, %%esi\n"
                        "\tleaq	printIntStr(%%rip), %%rdi\n"
                        "\tmovb	$0, %%al\n"
                        "\tcallq	_printf\n"
                        "\txorl	%%eax, %%eax\n\n", tac->res->text);
                } else if (tac->res->dataType == DATATYPE_STRING){
                    fprintf(fout, 
                    "## TAC_PRINTSTR\n"
                        "\tleaq	printStr(%%rip), %%rdi\n"
                        "\tleaq	_STRING%s(%%rip), %%rsi\n"
                        "\tmovb	$0, %%al\n"
                        "\tcallq	_printf\n"
                        "\txorl	%%eax, %%eax\n\n", remove_quotes(tac->res->text));
                }
                break;
            case TAC_VEC:
                fprintf(stderr, "%s %s %d\n", tac->res->text, tac->op1->text, 4*atoi(tac->op2->text));
                char type[5];
                switch (tac->res->dataType){
                    case DATATYPE_INT: strcpy(type,"INT"); break;
                    case DATATYPE_REAL: strcpy(type,"FLOAT"); break;
                    case DATATYPE_BOOL: 
                        if (strcmp(tac->res->text,"true"))
                            strcpy(type, "TRUE");
                        else
                            strcpy(type, "FALSE");
                        break;
                    case DATATYPE_CHAR: strcpy(type,"CHAR"); break;
                }
                 
                fprintf(fout, 
                    "## TAC_VET"
                    "\txorl	%%eax, %%eax\n"
                    "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                    "\tmovl	_%s+%d(%%rip), %%edx\n"
                    "\tmovl	%%edx, (%%rcx)\n\n", type, tac->res->text, tac->op1->text, 4*atoi(tac->op2->text));
          break;
        }
    }

    // Data variables
    fprintf(fout,
    "# DATA SECTION\n"
	"\t.section	__DATA,__data\n\n");
    setLitValues(fout);
    setVariablesValues(fout, root);
    printASM(fout);

    // Each tac
    fclose(fout);
}
