//  Etapa 6 - Compiladores 2024/1
//      Autor: Matheus Lima 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asm.h"
#include "semantic.h"
#include "ast.h"
#include "hash.h"

char* getTacStrDataType(int dataType);
void generateAssemblyForCall(FILE *fout, const char *functionName, int numArgs, char *args[], char *attVar);
void generateArgumentReceival(int numArgs);

const char *argRegs[] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d", "%r13d", "%r12d", "%r15d", "%r14d", "%ebx", "%r11d", "%r10d", "%eax"};
const char *preArgRegs[] = {"%rbx", "%r14", "%r15", "%r12", "%r13"};

// ASM GENERATION
TAC* tacReverse(TAC *tac){
    TAC* t = tac;

    for (t = tac; t->prev; t = t->prev){
        t->prev->next = t;
    }

    return t;
}

char* getTacStrDataType(int dataType){
    char *typeStr = malloc(sizeof(char)*5);

    switch (dataType){
        case DATATYPE_INT: strcpy(typeStr,"INT"); break;
        case DATATYPE_REAL: strcpy(typeStr,"FLOAT"); break;
        case DATATYPE_BOOL: strcpy(typeStr, "BOOL"); break;
        case DATATYPE_CHAR: strcpy(typeStr,"CHAR"); break;
    }

    return typeStr;
}

void setVariablesValues(FILE *fout, AST* node){
    if (!node) return;

    int charData;

	if (node->type == AST_DECVAR) { 
		if(node->son[0]->type == AST_TPFLOAT) {
			fprintf(fout, "\t.globl _FLOAT%s\n_FLOAT%s:\t.float	%s\n", node->symbol->text, node->symbol->text, node->son[1]->symbol->text);
		} else if (node->son[0]->type == AST_TPINT) {
			fprintf(fout, "\t.globl _INT%s\n_INT%s:\t.long	%s\n", node->symbol->text, node->symbol->text, node->son[1]->symbol->text);
		} else if (node->son[0]->type == AST_TPBOOL) {
			fprintf(fout, "\t.globl _BOOL%s\n_BOOL%s:\t.long    %d\n", node->symbol->text, node->symbol->text, strcmp(node->son[1]->symbol->text, "true") ? 0:1);
		} else if (node->son[0]->type == AST_TPCHAR) {
            if (node->son[1]->symbol->text[0] == '\'')
                charData = (int)(node->son[1]->symbol->text[1]);
            else charData = atoi(node->son[1]->symbol->text);

			fprintf(fout, "\t.globl _CHAR%s\n_CHAR%s:\t.long	%d\n", node->symbol->text, node->symbol->text, charData);
		}
	} else if(node->type == AST_DECVEC){
        if (node->son[2]){
            fprintf(fout,
            "\t.globl\t_%s%s\n"
            "_%s%s:\n", getTacStrDataType(node->symbol->dataType), node->symbol->text, getTacStrDataType(node->symbol->dataType), node->symbol->text);
        } else {
            fprintf(fout, "\t.comm\t_%s%s,%d,4\n", getTacStrDataType(node->symbol->dataType), node->symbol->text, 4*atoi(node->son[1]->symbol->text));
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
    
    int jumpFalseCount = 0;
    int jumpTrueCount = 0;
    int jumpEndCount = 0;

    char strReadFunc[20];

    int argIndex = 0;
    char * argList[100];
    int funcCallList[500];
    int funcCallIndex = 0;
    
    fout = fopen("out.s", "w");

    // Init
    fprintf(fout, "## FIXED INIT\n"
    ".section	__TEXT,__cstring,cstring_literals\n"
    "printIntStr: .asciz	\"%%d\\n\"\n"
    "printFloatStr: .asciz	\"%%f\\n\"\n"
    "readIntStr: .asciz	\"%%d\"\n"
    "readFloatStr: .asciz	\"%%f\"\n"
	"printStr: .asciz	\"%%s\"\n");
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
                funcCallIndex = 0;
                break;
            case TAC_ENDFUN: 
                fprintf(fout, 
                "## TAC_ENDFUN\n");
                
                for (int i = 0; i < funcCallIndex; i++){
                    fprintf(fout, 
                        "\taddq	$%d, %%rsp\n", funcCallList[i]);
                }
                    fprintf(fout,
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
                        "\tleaq	printIntStr(%%rip), %%rdi\n");
                    if (tac->res->type == SYMBOL_VARIABLE)
                        fprintf(fout, "\tmovl	_CHAR%s(%%rip), %%esi\n", tac->res->text);
                    else
                        fprintf(fout, "\tmovl	_CHAR%d(%%rip), %%esi\n", tac->res->text[1]);
                    fprintf(fout,
                        "\tmovb	$0, %%al\n"
                        "\tcallq	_printf\n\n");
                } else if (tac->res->dataType == DATATYPE_REAL){
                    fprintf(fout, 
                    "## TAC_PRINTREAL\n"
                        "\tmovss	_FLOAT%s(%%rip), %%xmm0\n"
                        "\tcvtss2sd	%%xmm0, %%xmm0\n"
                        "\tleaq	printFloatStr(%%rip), %%rdi\n"
                        "\tmovb	$1, %%al\n"
                        "\tcallq	_printf\n\n", tac->res->text);
                } else if (tac->res->dataType == DATATYPE_BOOL){
                    fprintf(fout, 
                    "## TAC_PRINTBOOL\n"
                        "\tmovb	_BOOL%s(%%rip), %%al\n"
                        "\tandb	$1, %%al\n"
                        "\tmovzbl	%%al, %%esi\n"
                        "\tleaq	printIntStr(%%rip), %%rdi\n"
                        "\tmovb	$0, %%al\n"
                        "\tcallq	_printf\n\n", tac->res->text);
                } else if (tac->res->dataType == DATATYPE_STRING){
                    fprintf(fout, 
                    "## TAC_PRINTSTR\n"
                        "\tleaq	printStr(%%rip), %%rdi\n"
                        "\tleaq	_STRING%lu(%%rip), %%rsi\n"
                        "\tmovb	$0, %%al\n"
                        "\tcallq	_printf\n\n", hashString(tac->res->text));
                }
                break;
            case TAC_VEC: 
                fprintf(fout, 
                    "## TAC_VEC\n"
                        "\txorl	%%eax, %%eax\n"
                        "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                        "\tmovl	_%s%s+%d(%%rip), %%edx\n"
                        "\tmovl	%%edx, (%%rcx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, 4*atoi(tac->op2->text));
                break;
            case TAC_ATTRVEC: 
                fprintf(fout, 
                    "## TAC_ATTRVEC\n"
                        "\txorl	%%eax, %%eax\n"
                        "\tmovl	_%s%s(%%rip), %%esi\n"
                        "\tmovslq	_%s%s(%%rip), %%rdx\n"
                        "\tleaq	_%s%s(%%rip), %%rcx\n"
                        "\tmovl	%%esi, (%%rcx,%%rdx,4)\n\n", getTacStrDataType(tac->op2->dataType), tac->op2->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->res->dataType), tac->res->text);
            case TAC_COPY:
                fprintf(fout, 
                    "## TAC_COPY\n"
                        "\txorl	%%eax, %%eax\n"
                        "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                        "\tmovl	_%s%s(%%rip), %%edx\n"
                        "\tmovl	%%edx, (%%rcx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType),tac->op1->text);
                break;
            case TAC_ADD:
                if (tac->res->dataType == DATATYPE_REAL){
                    fprintf(fout,
                    "## TAC_ADD\n"
                        "\txorl	%%eax, %%eax\n"
                        "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                        "\tmovss	_%s%s(%%rip), %%xmm0\n"
                        "\taddss	_%s%s(%%rip), %%xmm0\n"
                        "\tmovss	%%xmm0, (%%rcx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text);
                } else {
                    fprintf(fout,
                        "## TAC_ADD"
                            "\txorl	%%eax, %%eax\n"
                            "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                            "\tmovl	_%s%s(%%rip), %%edx\n"
                            "\taddl	_%s%s(%%rip), %%edx\n"
                            "\tmovl	%%edx, (%%rcx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text);
                }
                break;
            case TAC_SUB:
                if (tac->res->dataType == DATATYPE_REAL){
                    fprintf(fout,
                    "## TAC_SUB"
                        "\txorl	%%eax, %%eax\n"
                        "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                        "\tmovss	_%s%s(%%rip), %%xmm0\n"
                        "\tsubss	_%s%s(%%rip), %%xmm0\n"
                        "\tmovss	%%xmm0, (%%rcx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text);
                } else {
                    fprintf(fout,
                        "## TAC_SUB"
                            "\txorl	%%eax, %%eax\n"
                            "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                            "\tmovl	_%s%s(%%rip), %%edx\n"
                            "\tsubl	_%s%s(%%rip), %%edx\n"
                            "\tmovl	%%edx, (%%rcx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text);
                }
                break;
            case TAC_MUL:
                if (tac->res->dataType == DATATYPE_REAL){
                    fprintf(fout,
                    "## TAC_MUL"
                        "\txorl	%%eax, %%eax\n"
                        "\tmovq	_%s%s@GOTPCREL(%%rip), %%rdx\n"
                        "\tmovss	_%s%s(%%rip), %%xmm0\n"
                        "\tmulss	_%s%s(%%rip), %%xmm0\n"
                        "\tmovss	%%xmm0, (%%rdx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text);
                } else {
                    fprintf(fout,
                        "## TAC_MUL"
                            "\txorl	%%eax, %%eax\n"
                            "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                            "\tmovl	_%s%s(%%rip), %%edx\n"
                            "\timull	_%s%s(%%rip), %%edx\n"
                            "\tmovl	%%edx, (%%rcx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text);
                }
                break;
            case TAC_DIV:
                if (tac->res->dataType == DATATYPE_REAL){
                    fprintf(fout,
                    "## TAC_DIV"
                        "\txorl	%%eax, %%eax\n"
                        "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                        "\tmovss	_%s%s(%%rip), %%xmm0\n"
                        "\tdivss	_%s%s(%%rip), %%xmm0\n"
                        "\tmovss	%%xmm0, (%%rcx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text);
                } else {
                    fprintf(fout,
                        "## TAC_DIV"
                            "\txorl	%%eax, %%eax\n"
                            "\tmovl	%%eax, -4(%%rbp)\n"
                            "\tmovq	_%s%s@GOTPCREL(%%rip), %%rcx\n"
                            "\tmovl	_%s%s(%%rip), %%eax\n\tcltd\n"
                            "\tidivl	_%s%s(%%rip)\n"
                            "\tmovl   %%eax, %%edx\n"
                            "\tmovl   -4(%%rbp), %%eax\n"
                            "\tmovl	%%edx, (%%rcx)\n\n", getTacStrDataType(tac->res->dataType), tac->res->text, getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text);
                }
                break;
            case TAC_GREAT:
                fprintf(fout,
                "## TAC GREATER\n"
                    "\tmovl    _%s%s(%%rip), %%eax\n"
                    "\tcmpl    _%s%s(%%rip), %%eax\n"
                    "\tsetg    %%al\n"
                    "\tmovzbl  %%al, %%eax\n"
                    "\tmovl    %%eax, _%s%s(%%rip)\n\n", getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_LESS:
                fprintf(fout,
                "## TAC LESS\n"
                    "\tmovl    _%s%s(%%rip), %%eax\n"
                    "\tcmpl    _%s%s(%%rip), %%eax\n"
                    "\tsetl    %%al\n"
                    "\tmovzbl  %%al, %%eax\n"
                    "\tmovl    %%eax, _%s%s(%%rip)\n\n", getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_GE:
                fprintf(fout,
                "## TAC GE\n"
                    "\tmovl    _%s%s(%%rip), %%eax\n"
                    "\tcmpl    _%s%s(%%rip), %%eax\n"
                    "\tsetge    %%al\n"
                    "\tmovzbl  %%al, %%eax\n"
                    "\tmovl    %%eax, _%s%s(%%rip)\n\n", getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_LE:
                fprintf(fout,
                "## TAC LE\n"
                    "\tmovl    _%s%s(%%rip), %%eax\n"
                    "\tcmpl    _%s%s(%%rip), %%eax\n"
                    "\tsetle    %%al\n"
                    "\tmovzbl  %%al, %%eax\n"
                    "\tmovl    %%eax, _%s%s(%%rip)\n\n", getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_EQ:
                fprintf(fout,
                "## TAC EQ\n"
                    "\tmovl    _%s%s(%%rip), %%eax\n"
                    "\tcmpl    _%s%s(%%rip), %%eax\n"
                    "\tsete    %%al\n"
                    "\tmovzbl  %%al, %%eax\n"
                    "\tmovl    %%eax, _%s%s(%%rip)\n\n", getTacStrDataType(tac->op1->dataType), tac->op1->text, getTacStrDataType(tac->op2->dataType), tac->op2->text, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_DIF:
                fprintf(fout,
                "## TAC DIF\n"
                    "\tmovl    $%s, %%eax\n"
                    "\tcmpl    $%s, %%eax\n"
                    "\tsetne    %%al\n"
                    "\tmovzbl  %%al, %%eax\n"
                    "\tmovl    %%eax, _%s%s(%%rip)\n"
                    "\tmovl    $0, _%%eax\n\n", tac->op1->text, tac->op2->text, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_AND:
                ++jumpFalseCount;
                ++jumpEndCount;

                fprintf(fout,
                "## TAC AND\n"
                    "\tmovl    $%d, %%eax\n"
                    "\ttestl   %%eax, %%eax\n"
                    "\tje      .Lfalse%d\n"
                    "\tmovl    $%d, %%eax\n"
                    "\ttestl   %%eax, %%eax\n"
                    "\tje      .Lfalse%d\n"
                    "\tmovl    $1, %%eax\n"
                    "\tjmp     .Lend%d\n"
                ".Lfalse%d:\n"
                    "\tmovl    $0, %%eax\n"
                ".Lend%d:\n"
                    "\tmovl    %%eax, _%s%s(%%rip)\n\n", strcmp(tac->op1->text,"true") ? 0:1, jumpFalseCount, strcmp(tac->op2->text,"true") ? 0:1, jumpFalseCount, jumpEndCount, jumpFalseCount, jumpEndCount, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_OR:
                ++jumpTrueCount;
                ++jumpEndCount;

                fprintf(fout,
                "## TAC OR\n"
                    "\tmovl    $%d, %%eax\n"
                    "\ttestl   %%eax, %%eax\n"
                    "\tjnz     .Ltrue%d\n"
                    "\tmovl    $%d, %%eax\n"
                    "\tjmp     .Lend%d\n"
                ".Ltrue%d:\n"
                    "\tmovl    $1, %%eax\n"
                ".Lend%d:\n"
                    "\tmovl    %%eax, _%s%s(%%rip)\n\n", strcmp(tac->op1->text,"true") ? 0:1, jumpTrueCount, strcmp(tac->op2->text,"true") ? 0:1, jumpEndCount, jumpTrueCount, jumpEndCount, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_NOT:
                fprintf(fout,
                "## TAC NOT\n"
                    "\tmovl    _BOOL%s(%%rip), %%eax\n"
                    "\txorl    $1, %%eax\n"
                    "\tmovl    %%eax, _%s%s(%%rip)\n\n", tac->op1->text, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_LABEL:
                fprintf(fout, 
                "## TAC LABEL\n"
                ".%s:\n\n", tac->res->text);
                break;
            case TAC_JUMP:
                fprintf(fout, 
                "## TAC JUMP\n"
                "\tjmp .%s\n\n", tac->res->text);
                break;
            case TAC_JFALSE:
                fprintf(fout,
                "## TAC JFALSE\n" 
                    "\tmovl _%s%s(%%rip), %%eax\n"
                    "\ttestl %%eax, %%eax\n"
                    "\tjz   .%s\n\n", getTacStrDataType(tac->op1->dataType), tac->op1->text, tac->res->text);
                break;
            case TAC_RETURN:
                fprintf(fout, 
                "## TAC RETURN\n"
                    "\tmovl	_%s%s(%%rip), %%eax\n\n", getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_READ:
                if (tac->res->dataType == DATATYPE_REAL){
                    strcpy(strReadFunc, "readFloatStr");
                } else {
                    strcpy(strReadFunc, "readIntStr");
                }
                fprintf(fout,
                    "## TAC READ\n"
                        "\tleaq	%s(%%rip), %%rdi\n"
                        "\tleaq	_%s%s(%%rip), %%rsi\n"
                        "\tmovl	$0, %%eax\n"
                        "\tcallq	_scanf\n\n", strReadFunc, getTacStrDataType(tac->res->dataType), tac->res->text);
                break;
            case TAC_ARG:
                argList[argIndex] = (char*) calloc(1, sizeof(tac->res->text));
                
                strcpy(argList[argIndex], getTacStrDataType(tac->res->dataType));
                strcat(argList[argIndex], tac->res->text);
                ++argIndex;

                break;
            case TAC_CALL:
                generateAssemblyForCall(fout, tac->op1->text, argIndex, argList, strcat(getTacStrDataType(tac->res->dataType), tac->res->text));
                funcCallList[funcCallIndex] = 8*(argIndex-1);
                funcCallIndex++;

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

void generateAssemblyForCall(FILE *fout, const char *functionName, int numArgs, char *args[], char *attVar) {
    int i;
    int lastIndex;
    int stack_offset = 44 + (numArgs-14)*4;
    
    // Para armazenar os argumentos extras que não cabem nos registradores
    char *stackSpills[numArgs > 14 ? numArgs - 14: 0];

    fprintf(fout, "## TAC CALL\n");

    if (numArgs > 9){
        for (i = 0; i < numArgs - 9 && i < 5; i++){
            fprintf(fout, "\tpushq\t%s\n", preArgRegs[i]);
        }
    }

    fprintf(fout, "\tsubq\t$%d, %%rsp\n", 8*(numArgs-1));
    
    if (numArgs > 14){
        for (i = 0; i < numArgs; i++) {
            if (i < 13) {
                // Até 13 argumentos podem ser movidos diretamente para registradores
                fprintf(fout, "\tmovl\t_%s(%%rip), %s\n", args[i], argRegs[i]);
            } else {
                // Armazenar o argumento extra temporariamente na pilha
                fprintf(fout, "\tmovl\t_%s(%%rip), %%eax\n", args[i]);
                fprintf(fout, "\tmovl\t%%eax, -%d(%%rbp)\t\t## 4-byte Spill\n", stack_offset);
                
                stackSpills[i - 13] = (char *)malloc(40);
                sprintf(stackSpills[i - 13], "\tmovl\t-%d(%%rbp), %%eax\t\t## 4-byte Reload\n", stack_offset);
                stack_offset -= 4;
            }
        }

        // Move argumentos da pilha para os registradores, ou diretamente para o espaço da pilha
        for (i = 0; i < numArgs - 13; i++) {
            fprintf(fout, "%s", stackSpills[i]);
            if ((i+1) != (numArgs - 13)){
                fprintf(fout, "\tmovl\t%%eax, %d(%%rsp)\n", i * 8);
            }
            free(stackSpills[i]);
        }
        lastIndex = i - 1;
        // Adiciona os últimos argumentos nos registradores à pilha
        for (i = 6; i < 14 && i < numArgs; i++) {
            fprintf(fout, "\tmovl\t%s, %d(%%rsp)\n", argRegs[i], lastIndex * 8);
            ++lastIndex;
        }
    } else {
        for (i = 0; i < numArgs; i++) {
            // Até 6 argumentos podem ser movidos diretamente para registradores
            fprintf(fout, "\tmovl\t_%s(%%rip), %s\n", args[i], argRegs[i]);
        }
    }

    // Chamada da função
    fprintf(fout, "\tcall\t_%s\n"
                  "\tmovl\t%%eax, _%s(%%rip)\n\n", functionName, attVar);
}
