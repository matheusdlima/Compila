// AST - Abstract Syntax Tree
//      Autor: Matheus Lima

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3){
    AST*newNode;
    newNode = (AST*) calloc(1, sizeof(AST));
    newNode->type   = type;
    newNode->symbol = symbol;
    newNode->son[0] = s0;
    newNode->son[1] = s1;
    newNode->son[2] = s2;
    newNode->son[3] = s3;
    return newNode;
}

void astPrint(AST *node, int level){
    int i = 0;
    
    if (node == 0){
        return;
    }

    for (i = 0; i < level; ++i){
        fprintf(stderr,"  ");
    }
    fprintf(stderr,"ast(");
    
    switch (node->type){
        case AST_SYMBOL: 
            fprintf(stderr,"AST_SYMBOL");
            break;
        case AST_ADD:
            fprintf(stderr, "AST_ADD"); 
            break;
        case AST_SUB: 
            fprintf(stderr, "AST_SUB"); 
            break;
        case AST_MUL: 
            fprintf(stderr, "AST_MUL"); 
            break;
        case AST_DIV: 
            fprintf(stderr, "AST_DIV"); 
            break;
        case AST_LT: 
            fprintf(stderr, "AST_LT"); 
            break;
        case AST_GT: 
            fprintf(stderr, "AST_GT"); 
            break;
        case AST_LE: 
            fprintf(stderr, "AST_LE"); 
            break;
        case AST_GE: 
            fprintf(stderr, "AST_GE"); 
            break;
        case AST_EQ: 
            fprintf(stderr, "AST_EQ"); 
            break;
        case AST_DIF: 
            fprintf(stderr, "AST_NE"); 
            break;
        case AST_AND: 
            fprintf(stderr, "AST_AND"); 
            break;
        case AST_OR: 
            fprintf(stderr, "AST_OR"); 
            break;
        case AST_NOT: 
            fprintf(stderr, "AST_NOT"); 
            break;
        case AST_ATTR: 
            fprintf(stderr, "AST_ATTR"); 
            break;
        case AST_ATTRVEC: 
            fprintf(stderr, "AST_ATTRVEC"); 
            break;
        case AST_LCMD: 
            fprintf(stderr, "AST_LCMD"); 
            break;
        case AST_IF: 
            fprintf(stderr, "AST_IF"); 
            break;
        case AST_IFELSE: 
            fprintf(stderr, "AST_IFELSE"); 
            break;
        case AST_WHILE: 
            fprintf(stderr, "AST_WHILE"); 
            break;
        case AST_READ: 
            fprintf(stderr, "AST_READ"); 
            break;
        case AST_PRINT: 
            fprintf(stderr, "AST_PRINT"); 
            break;
        case AST_RETURN: 
            fprintf(stderr, "AST_RETURN"); 
            break;
        case AST_PARENT: 
            fprintf(stderr, "AST_PARENT"); 
            break;
        case AST_ARGSLST: 
            fprintf(stderr, "AST_ARGSLST"); 
            break;
        case AST_ARGSTAIL: 
            fprintf(stderr, "AST_ARGSTAIL"); 
            break;
        case AST_TPCHAR: 
            fprintf(stderr, "AST_TPCHAR"); 
            break;
        case AST_TPINT: 
            fprintf(stderr, "AST_TPINT"); 
            break;
        case AST_TPFLOAT: 
            fprintf(stderr, "AST_TPFLOAT"); 
            break;
        case AST_TPBOOL: 
            fprintf(stderr, "AST_TPBOOL"); 
            break;
        case AST_LDEC: 
            fprintf(stderr, "AST_LDEC"); 
            break;
        case AST_DECVAR: 
            fprintf(stderr, "AST_DECVAR"); 
            break;
        case AST_DECVEC: 
            fprintf(stderr, "AST_DECVEC"); 
            break;
        case AST_DECFUNC: 
            fprintf(stderr, "AST_DECFUNC"); 
            break;
        case AST_DECGVAR: 
            fprintf(stderr, "AST_DECGVAR"); 
            break;
        case AST_DECGVEC: 
            fprintf(stderr, "AST_DECGVEC"); 
            break;
        case AST_DECGFUNC: 
            fprintf(stderr, "AST_DECGFUNC"); 
            break;
        case AST_DECTAIL: 
            fprintf(stderr, "AST_DEC_TAIL"); 
            break;
        case AST_INITVEC: 
            fprintf(stderr, "AST_INITVEC"); 
            break;
        case AST_LISTVEC: 
            fprintf(stderr, "AST_LISTVEC"); 
            break;
        case AST_PARAMLIST: 
            fprintf(stderr, "AST_PARAMLIST"); 
            break;
        case AST_PARAMTAIL: 
            fprintf(stderr, "AST_PARAMTAIL"); 
            break;
        case AST_PARAM: 
            fprintf(stderr, "AST_PARAM"); 
            break;
        case AST_CMDBLOCK: 
            fprintf(stderr, "AST_CMDBLOCK"); 
            break;
        case AST_VEC: 
            fprintf(stderr, "AST_VEC"); 
            break;
        case AST_FUNC: 
            fprintf(stderr, "AST_FUNC"); 
            break;
        default:
            fprintf(stderr,"AST_UNKNOWN");
            break;
    }

    if (node->symbol != 0){
        fprintf(stderr,",%s\n", node->symbol->text);
    } else {
        fprintf(stderr,",0\n");
    }

    for (i = 0; i < MAX_SONS; ++i){
        astPrint(node->son[i], level+1);
    }
}

void astUncompile(AST *node, FILE *file){
    
    if(node == NULL){
        return;
    }

    switch(node->type){
    case AST_LDEC :
        astUncompile(node->son[0], file);
        astUncompile(node->son[1], file);
        break;

    case AST_DECVAR :
        astUncompile(node->son[0], file);
        fprintf(file, " %s : ", node->symbol->text);
        astUncompile(node->son[1], file);
        break;

    case AST_DECVEC :
        astUncompile(node->son[0], file);
        fprintf(file, " %s[", node->symbol->text);
        astUncompile(node->son[1], file);
        fprintf(file, "]");      
        astUncompile(node->son[2], file);
        break;

    case AST_DECFUNC :
        astUncompile(node->son[0], file);
        fprintf(file, " %s(", node->symbol->text);
        astUncompile(node->son[1], file);
        fprintf(file, ")");      
        astUncompile(node->son[2], file);
        break;

    case AST_TPCHAR :
        fprintf(file, "char");
        break;

    case AST_TPINT :
        fprintf(file, "int");
        break;

    case AST_TPFLOAT :
        fprintf(file, "float");
        break;

    case AST_TPBOOL :
        fprintf(file, "bool");
        break;

    case AST_SYMBOL :
        fprintf(file, " %s ", node->symbol->text);
        break;

    case AST_INITVEC :
        fprintf(file, " : ");
        astUncompile(node->son[0], file);
        fprintf(file, " ");
        astUncompile(node->son[1], file);
        break;

    case AST_LISTVEC :
        astUncompile(node->son[0], file);
        fprintf(file, " ");
        astUncompile(node->son[1], file);
        break;

    case AST_PARAMLIST :
        astUncompile(node->son[0], file);
        astUncompile(node->son[1], file);
        break;

    case AST_PARAMTAIL :
        fprintf(file, ", ");
        astUncompile(node->son[0], file);
        astUncompile(node->son[1], file);
        break;

    case AST_PARAM :
        astUncompile(node->son[0], file);
        fprintf(file, " ");
        fprintf(file, "%s", node->symbol->text);
        break;

    case AST_CMDBLOCK :
        fprintf(file, "{\n");
        astUncompile(node->son[0], file);
        fprintf(file, "}");
        break;

    case AST_LCMD :
        astUncompile(node->son[0], file);
        astUncompile(node->son[1], file);
        break;

    case AST_ATTR :
        fprintf(file, "%s = ", node->symbol->text);
        astUncompile(node->son[0], file);
        fprintf(file, ";\n");
        break;

    case AST_ATTRVEC :
        fprintf(file, "%s[", node->symbol->text);
        astUncompile(node->son[0], file);
        fprintf(file, "] = ");
        astUncompile(node->son[1], file);
        fprintf(file, ";\n");
        break;

    case AST_READ :
        fprintf(file, "read ");
        astUncompile(node->son[0], file);
        fprintf(file, " %s", node->symbol->text);
        fprintf(file, ";\n");
        break;

    case AST_PRINT :
        fprintf(file, "print ");
        astUncompile(node->son[0], file);
        fprintf(file, ";\n");
        break;

    case AST_RETURN :
        fprintf(file, "return ");
        astUncompile(node->son[0], file);
        fprintf(file, ";\n");
        break;

    case AST_IF :
        fprintf(file, "if(");
        astUncompile(node->son[0], file);
        fprintf(file, ")\n");
        astUncompile(node->son[1], file);
        break;

    case AST_WHILE :
        fprintf(file, "while(");
        astUncompile(node->son[0], file);
        fprintf(file, ")");
        astUncompile(node->son[1], file);
        break;

    case AST_IFELSE :
        fprintf(file, "if(");
        astUncompile(node->son[0], file);
        fprintf(file, ")\n");
        astUncompile(node->son[1], file);
        fprintf(file, "else\n");
        astUncompile(node->son[2], file);
        break;

    case AST_VEC :
        fprintf(file, "%s[", node->symbol->text);
        astUncompile(node->son[0], file);
        fprintf(file, "]");
        break;

    case AST_FUNC :
        fprintf(file, "%s(", node->symbol->text);
        astUncompile(node->son[0], file);
        fprintf(file, ")");
        break;

    case AST_ADD :
        astUncompile(node->son[0], file);
        fprintf(file, " + ");
        astUncompile(node->son[1], file);
        break;

    case AST_SUB :
        astUncompile(node->son[0], file);
        fprintf(file, " - ");
        astUncompile(node->son[1], file);
        break;

    case AST_MUL :
        astUncompile(node->son[0], file);
        fprintf(file, " * ");
        astUncompile(node->son[1], file);
        break;

    case AST_DIV :
        astUncompile(node->son[0], file);
        fprintf(file, " / ");
        astUncompile(node->son[1], file);
        break;

    case AST_LT :
        astUncompile(node->son[0], file);
        fprintf(file, " < ");
        astUncompile(node->son[1], file);
        break;

    case AST_GT :
        astUncompile(node->son[0], file);
        fprintf(file, " > ");
        astUncompile(node->son[1], file);
        break;

    case AST_EQ :
        astUncompile(node->son[0], file);
        fprintf(file, " == ");
        astUncompile(node->son[1], file);
        break;

    case AST_GE :
        astUncompile(node->son[0], file);
        fprintf(file, " >= ");
        astUncompile(node->son[1], file);
        break;

    case AST_LE :
        astUncompile(node->son[0], file);
        fprintf(file, " <= ");
        astUncompile(node->son[1], file);
        break;

    case AST_DIF :
        astUncompile(node->son[0], file);
        fprintf(file, " != ");
        astUncompile(node->son[1], file);
        break;

    case AST_AND :
        astUncompile(node->son[0], file);
        fprintf(file, " and ");
        astUncompile(node->son[1], file);
        break;

    case AST_OR :
        astUncompile(node->son[0], file);
        fprintf(file, " or ");
        astUncompile(node->son[1], file);
        break;

    case AST_NOT :
        fprintf(file, "not ");
        astUncompile(node->son[0], file);
        break;

    case AST_PARENT :
        fprintf(file, "(");
        astUncompile(node->son[0], file);
        fprintf(file, ")");
        break;

    case AST_ARGSLST :
        astUncompile(node->son[0], file);
        astUncompile(node->son[1], file);
        break;

    case AST_ARGSTAIL :
        fprintf(file, ", ");
        astUncompile(node->son[0], file);
        astUncompile(node->son[1], file);
        break;

    case AST_DECGVAR: 
        astUncompile(node->son[0], file);
        fprintf(file, ";\n");
        break;

    case AST_DECGVEC: 
        astUncompile(node->son[0], file);
        fprintf(file, ";\n");
        break;

    case AST_DECGFUNC: 
        astUncompile(node->son[0], file);
        break;
    
    case AST_DECTAIL: 
        astUncompile(node->son[0], file);
        astUncompile(node->son[1], file);
        break;
    
    case AST_TYPEPRINT: 
        astUncompile(node->son[0], file);
        fprintf(file, " ");
        astUncompile(node->son[1], file);
        break;
    
    case AST_SEMICOLON: 
        fprintf(file, ";\n");
        break;
    }
}
