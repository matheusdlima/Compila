//  Etapa 5 - Compiladores 2024/1
//      Autor: Matheus Lima 

#include "tacs.h"

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2){
    TAC* newTac = 0;
    newTac = (TAC*) calloc(1, sizeof(TAC));
    newTac->type = type;
    newTac->res = res;
    newTac->op1 = op1;
    newTac->op2 = op2;
    newTac->prev = 0;
    newTac->next = 0;
    
    return newTac;
}

void tacPrint(TAC* tac){
    if ((!tac) || (tac->type == TAC_SYMBOL)) return;

    fprintf(stderr, "TAC(");

    switch(tac->type){
        case TAC_ADD:
            fprintf(stderr, "TAC_ADD");
            break;
        case TAC_SUB:
            fprintf(stderr, "TAC_SUB");
            break;
        case TAC_MUL:
            fprintf(stderr, "TAC_MUL");
            break;
        case TAC_DIV:
            fprintf(stderr, "TAC_DIV");
            break;
        case TAC_GREAT:
            fprintf(stderr, "TAC_GREAT");
            break;
        case TAC_LESS:
            fprintf(stderr, "TAC_LESS");
            break;
        case TAC_EQ:
            fprintf(stderr, "TAC_EQ");
            break;
        case TAC_GE:
            fprintf(stderr, "TAC_GE");
            break;
        case TAC_LE:
            fprintf(stderr, "TAC_LE");
            break;
        case TAC_DIF:
            fprintf(stderr, "TAC_DIF");
            break;
        case TAC_AND:
            fprintf(stderr, "TAC_AND");
            break;
        case TAC_OR:
            fprintf(stderr, "TAC_OR");
            break;
        case TAC_NOT:
            fprintf(stderr, "TAC_NOT");
            break;
        case TAC_COPY:
            fprintf(stderr, "TAC_COPY");
            break;
        case TAC_LABEL:
            fprintf(stderr, "TAC_LABEL");
            break;
        case TAC_JFALSE:
            fprintf(stderr, "TAC_JFALSE");
            break;
        case TAC_CALL:
            fprintf(stderr, "TAC_CALL");
            break;
        case TAC_ARG:
            fprintf(stderr, "TAC_ARG");
            break;
        case TAC_VEC:
            fprintf(stderr, "TAC_VEC");
            break;
        case TAC_ATTRVEC:
            fprintf(stderr, "TAC_ATTRVEC");
            break;
        case TAC_BEGINFUN:
            fprintf(stderr, "TAC_BEGINFUN");
            break;
        case TAC_ENDFUN:
            fprintf(stderr, "TAC_ENDFUN");
            break;
        case TAC_READ:
            fprintf(stderr, "TAC_READ");
            break;
        case TAC_PRINT:
            fprintf(stderr, "TAC_PRINT");
            break;
        case TAC_RETURN:
            fprintf(stderr, "TAC_RETURN");
            break;
        case TAC_JUMP:
            fprintf(stderr, "TAC_JUMP");
            break;

        default:
            fprintf(stderr, "TAC_UNKNOWN");
            break;
    }

    fprintf(stderr, ",%s", (tac->res) ? tac->res->text:"0");
    fprintf(stderr, ",%s", (tac->op1) ? tac->op1->text:"0");
    fprintf(stderr, ",%s", (tac->op2) ? tac->op2->text:"0");
    fprintf(stderr, ");\n");
}

void tacPrintBackwards(TAC* tac){
    if (!tac){
        return;
    } else {
        tacPrintBackwards(tac->prev);
        tacPrint(tac);
    }
}

// CODE GENERATION
TAC* makeOperations(int TAC_DEFINE, TAC* code0, TAC* code1, int dataType);
TAC* makeIf(TAC* code[]);
TAC* makeWhile(TAC* code[], HASH_NODE *whileLabel);

TAC* generateCode(AST *node, HASH_NODE *currentWhileLabel){
    int i;
    TAC *result = 0;
    TAC *code[MAX_SONS];

    if (!node) return 0;
    
    if(node->type == AST_WHILE){
		currentWhileLabel = makeLabel();
	}

    // PROCESS CHILDREN
    for (i = 0; i<MAX_SONS; ++i){
        code[i] = generateCode(node->son[i], currentWhileLabel);
    }

    // PROCESS THIS NODE
    switch (node->type){
        case AST_SYMBOL:
            result = tacCreate(TAC_SYMBOL,node->symbol,0,0);
            break;
        // BYNARY OPERATIONS
        case AST_ADD:
            result = makeOperations(TAC_ADD, code[0], code[1], node->dataType);
            break;
        case AST_SUB:
            return makeOperations(TAC_SUB, code[0], code[1], node->dataType);
            break;
		case AST_MUL:
            return makeOperations(TAC_MUL, code[0], code[1], node->dataType);
            break;
		case AST_DIV:
            return makeOperations(TAC_DIV, code[0], code[1], node->dataType);
            break;
		case AST_GT:
            return makeOperations(TAC_GREAT, code[0], code[1], node->dataType);
            break;
		case AST_LT:
            return makeOperations(TAC_LESS, code[0], code[1], node->dataType);
            break;
		case AST_EQ:
            return makeOperations(TAC_EQ, code[0], code[1], node->dataType);
            break;
		case AST_GE:
            return makeOperations(TAC_GE, code[0], code[1], node->dataType);
            break;
		case AST_LE:
            return makeOperations(TAC_LE, code[0], code[1], node->dataType);
            break;
		case AST_DIF:
            return makeOperations(TAC_DIF, code[0], code[1], node->dataType);
            break;
		case AST_AND:
            return makeOperations(TAC_AND, code[0], code[1], node->dataType);
            break;
		case AST_OR:
            return makeOperations(TAC_OR, code[0], code[1], node->dataType);
            break;
		case AST_NOT:
            return makeOperations(TAC_NOT, code[0], code[1], node->dataType);
            break;
        
        // COMANDS
        case AST_ATTR:
            result = tacJoin(code[0], tacCreate(TAC_COPY, node->symbol, code[0]?code[0]->res:0,0));
            break;
        case AST_ATTRVEC:
            result = tacJoin(code[0], tacJoin(code[1], 
                tacCreate(TAC_ATTRVEC, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0)));
            break;
        case AST_IFELSE:
        case AST_IF:
            result = makeIf(code);
            break;
		case AST_PRINT:
            result = tacJoin(tacJoin(code[0], tacCreate(TAC_PRINT, code[0]?code[0]->res:0, 0, 0)), code[1]);
            break;
        case AST_READ:
            result = tacCreate(TAC_READ, node->symbol, 0, 0);
            break;
        case AST_RETURN:
            result = tacJoin(code[0], tacCreate(TAC_RETURN, code[0]?code[0]->res:0, 0, 0));
            break;
        case AST_WHILE:
            result = makeWhile(code, currentWhileLabel);
            break;
        case AST_VEC:
            result = tacJoin(code[0], tacCreate(TAC_VEC, makeTemp(node->dataType), node->symbol, code[0]?code[0]->res:0));
            break;
        case AST_FUNC:
            result = tacJoin(code[0], tacCreate(TAC_CALL, makeTemp(node->dataType), node->symbol, 0));
            break;
        case AST_ARGSLST: 
        case AST_ARGSTAIL:
            result = tacJoin(code[1], tacJoin(code[0], tacCreate(TAC_ARG, code[0]?code[0]->res:0, 0, 0)));
            break;
        case AST_DECFUNC:
            result = tacJoin(tacJoin(tacJoin(tacCreate(TAC_BEGINFUN, tacCreate(TAC_SYMBOL, node->symbol, 0, 0)->res, 0, 0), code[1]), code[2]), tacCreate(TAC_ENDFUN, tacCreate(TAC_SYMBOL, node->symbol, 0, 0)->res, 0, 0));
            break;
        // 
        default:
            result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
            break;
    }

    return result;
}

TAC* tacJoin(TAC* l1, TAC* l2){
    TAC *point;

    if (!l1) return l2;
    if (!l2) return l1;

    for (point = l2; point->prev != 0; point = point->prev){
        ;
    }
    point->prev = l1;
    return l2;
}

// MAKES
TAC* makeOperations(int TAC_DEFINE, TAC* code0, TAC* code1, int dataType){
    return tacJoin(tacJoin(code0, code1), tacCreate(TAC_DEFINE, makeTemp(dataType),code0?code0->res:0,code1?code1->res:0) );
}

TAC* makeIf(TAC* code[]){
    TAC * ifTAC = 0;
    TAC * ifLabelTAC = 0;
    HASH_NODE * ifLabel = 0;

    ifLabel = makeLabel();

    // Create the TAC for the skip condition if false
    ifTAC = tacJoin(code[0], tacCreate(TAC_JFALSE,ifLabel,code[0]?code[0]->res:0,0));
    ifTAC->prev = code[0];
    ifLabelTAC = tacCreate(TAC_LABEL,ifLabel,0,0);

    if(code[2]){ // Case of have an else
        HASH_NODE* elseLabel = makeLabel();
		TAC* elseJumpTAC = tacCreate(TAC_JUMP, elseLabel, 0, 0);
        TAC* elseLabelTAC = tacCreate(TAC_LABEL, elseLabel, 0, 0);
        
		TAC* ifElseTAC = tacJoin(
            tacJoin(
                tacJoin(
                    tacJoin(
                        tacJoin(ifTAC, code[1]), 
                        elseJumpTAC),
                    ifLabelTAC),
                code[2]), 
            elseLabelTAC);
            
		return ifElseTAC;
    } else {
        return tacJoin(tacJoin(ifTAC, code[1]), ifLabelTAC);
    }
}

TAC* makeWhile(TAC* code[], HASH_NODE *whileLabel){
    HASH_NODE* jumpLabel = makeLabel();

    // creates the TACs necessary for the while command
	TAC* whileTAC = tacCreate(TAC_JFALSE, jumpLabel, code[0]?code[0]->res:0, 0);
	TAC* whileLabelTAC = tacCreate(TAC_LABEL, whileLabel, 0, 0);
	TAC* jumpTAC = tacCreate(TAC_JUMP, whileLabel, 0, 0);
	TAC* jumpLabelTAC= tacCreate(TAC_LABEL, jumpLabel, 0, 0);

    // join the TACs to form the while structure
	return tacJoin(
        tacJoin(
            tacJoin(
                tacJoin(
                    tacJoin(whileLabelTAC, code[0]),
                    whileTAC), 
                code[1]),
            jumpTAC), 
        jumpLabelTAC);
}
