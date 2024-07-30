// Semantic

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "semantic.h"
#include <string.h>

int SemanticErrors = 0;
AST *ROOT;

int checkSemantics(AST* root){
    ROOT = root;
				
	checkAndSetDeclarations(root);
    checkUndeclared();
    checkOperands(root);
    setNodeTypes(root);
    checkNature(root);
    checkReturnTypes(root);

    return SemanticErrors;
}

void checkAndSetDeclarations(AST *node){
    int i = 0;
    
    if (!node) return;

    switch (node->type){
        case AST_DECVAR:
            if (node->symbol){
                if (node->symbol->type != SYMBOL_IDENTIFIER){
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                }
                node->symbol->type = SYMBOL_VARIABLE;
                node->symbol->dataType = setDataType(node->son[0]->type);
                if(! isCompatibleDataType(node->symbol->dataType, node->son[1]->symbol->dataType)){
                    fprintf(stderr, "Semantic ERROR: Variable %s declaration with mixed dataypes\n", node->symbol->text);
                    SemanticErrors++;
		        }
            }
            break;
        case AST_DECFUNC:
            if (node->symbol){
                if (node->symbol->type != SYMBOL_IDENTIFIER){
                    fprintf(stderr, "Semantic ERROR: function %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                }          
                node->symbol->type = SYMBOL_FUNCTION;
                node->symbol->dataType = setDataType(node->son[0]->type);
            }
            break;
        case AST_DECVEC:
            if (node->symbol){
                if (node->symbol->type != SYMBOL_IDENTIFIER){
                    fprintf(stderr, "Semantic ERROR: vector %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                }          
                node->symbol->type = SYMBOL_VECTOR;
                node->symbol->dataType = setDataType(node->son[0]->type);

                if(! checkVectorElements(node->son[2], node->symbol->dataType, atoi(node->son[1]->symbol->text), 1, node->symbol->text)){
                    fprintf(stderr, "Semantic ERROR: Vector %s declaration with elements of mixed dataType\n", node->symbol->text);
                    SemanticErrors++;
                }
            }
            break;
        case AST_PARAM:
            if (node->symbol){
                if (node->symbol->type != SYMBOL_IDENTIFIER){
                    fprintf(stderr, "Semantic ERROR: parameter %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                }          
                node->symbol->type = SYMBOL_PARAM;
                node->symbol->dataType = setDataType(node->son[0]->type);
            }
            break;
    }

    for (i = 0; i < MAX_SONS; ++i){
        checkAndSetDeclarations(node->son[i]);
    }
}

void checkUndeclared(){
    SemanticErrors += hashCheckUndeclared();
}

int isInteger(int dt){
    return (dt == DATATYPE_INT || dt == DATATYPE_CHAR);
}

int isNumerical(int dt){
    return isInteger(dt) || dt == DATATYPE_REAL;
}

int isNumber(AST *son) {
    if (!son) return 0;

    // Check if the node is an arithmetic operation
    if (son->type == AST_ADD || son->type == AST_SUB || son->type == AST_MUL || son->type == AST_DIV) {
        return 1;
    }

    // Check if the node is a symbol
    if (son->type == AST_SYMBOL) {
        switch (son->symbol->type) {
            case SYMBOL_LIT_INTEGER:
            case SYMBOL_LIT_CHAR:
            case SYMBOL_LIT_REAL:
                return 1;
            case SYMBOL_VARIABLE:
            case SYMBOL_PARAM:
                return isNumerical(son->symbol->dataType);
            default:
                return 0;
        }
    }

    // Check if the node is a function or vector and its data type is numerical
    if ((son->type == AST_FUNC || son->type == AST_VEC) && isNumerical(son->symbol->dataType)) {
        return 1;
    }

    return 0;
}

void checkOperands(AST *node){
    int i = 0;
    
    if (!node) return;

    for (i = 0; i < MAX_SONS; ++i){
        checkOperands(node->son[i]);
    }

    switch (node->type){
        case AST_ADD:   // if operands are not valids
            if (! isNumber(node->son[0])){
                fprintf(stderr, "Semantic ERROR: Invalid left operands for ADD\n");
                SemanticErrors++;
            }     
            if (! isNumber(node->son[1])){
                fprintf(stderr, "Semantic ERROR: Invalid right operands for ADD\n");
                SemanticErrors++;
            }
            break;
        case AST_SUB:   // if operands are not valids
            if (! isNumber(node->son[0])){
                fprintf(stderr, "Semantic ERROR: Invalid left operands for SUB\n");
                SemanticErrors++;
            }    
            if (! isNumber(node->son[1])){
                fprintf(stderr, "Semantic ERROR: Invalid right operands for SUB\n");
                SemanticErrors++;
            }
            break;
        case AST_MUL:   // if operands are not valids
            if (! isNumber(node->son[0])){
                fprintf(stderr, "Semantic ERROR: Invalid left operands for MUL\n");
                SemanticErrors++;
            }    
            if (! isNumber(node->son[1])){
                fprintf(stderr, "Semantic ERROR: Invalid right operands for MUL\n");
                SemanticErrors++;
            }
            break;
        case AST_DIV:   // if operands are not valids
            if (! isNumber(node->son[0])){
                fprintf(stderr, "Semantic ERROR: Invalid left operands for DIV\n");
                SemanticErrors++;
            }    
            if (! isNumber(node->son[1])){
                fprintf(stderr, "Semantic ERROR: Invalid right operands for DIV\n");
                SemanticErrors++;
            }
            break;
        }
}

void setNodeTypes(AST *node) {
    if (!node) return;

    // Recursively set types for all child nodes
    for (int i = 0; i < MAX_SONS; i++) {
        setNodeTypes(node->son[i]);
    }

    switch (node->type) {
        case AST_SYMBOL:
            if (node->symbol->type == SYMBOL_VECTOR || node->symbol->type == SYMBOL_FUNCTION) {
                fprintf(stderr, "Semantic ERROR: function/vector %s is used as a scalar variable\n", node->symbol->text);
                SemanticErrors++;
            }
            node->dataType = node->symbol->dataType;
            break;
        case AST_FUNC:
        case AST_VEC:
            node->dataType = node->symbol->dataType;
            break;
        case AST_PARENT:
            node->dataType = node->son[0]->dataType;
            break;
        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
            node->dataType = (node->son[0]->dataType > node->son[1]->dataType) ? node->son[0]->dataType : node->son[1]->dataType;
            break;
        default:
            if (isRelationalOp(node->type)) {
                if (!isNumerical(node->son[0]->dataType) || !isNumerical(node->son[1]->dataType)) {
                    fprintf(stderr, "Semantic ERROR: Relational operation with incompatible data types\n");
                    SemanticErrors++;
                }
                node->dataType = DATATYPE_BOOL;
            } else if (isLogicalOp(node->type)) {
                if (node->type == AST_NOT) {
                    if (node->son[0]->dataType != DATATYPE_BOOL) {
                        fprintf(stderr, "Semantic ERROR: Logical operation with incompatible data types\n");
                        SemanticErrors++;
                    }
                } else if (node->son[0]->dataType != DATATYPE_BOOL || node->son[1]->dataType != DATATYPE_BOOL) {
                    fprintf(stderr, "Semantic ERROR: Logical operation with incompatible data types\n");
                    SemanticErrors++;
                }
                node->dataType = DATATYPE_BOOL;
            } else if (node->type == AST_TYPEPRINT) {
                node->dataType = setDataType(node->son[0]->type);
            }
            break;
    }
}

void checkNature(AST *node) {
    if (!node) return;

    switch (node->type) {
        case AST_ATTR:
            if (node->symbol->type != SYMBOL_VARIABLE) {
                fprintf(stderr, "Semantic ERROR: Variable %s isn't a scalar\n", node->symbol->text);
                SemanticErrors++;
            }
            if(!isCompatibleDataType(node->symbol->dataType, node->son[0]->dataType)){
                fprintf(stderr, "Semantic ERROR: Attribution %s with incompatible data type\n", node->symbol->text);
                SemanticErrors++;
            }
            break;
        
        case AST_ATTRVEC:
            if (node->symbol->type != SYMBOL_VECTOR) {
                fprintf(stderr, "Semantic ERROR: Left side of the vector must be a vector\n");
                SemanticErrors++;
            }
            if(!isInteger(node->son[0]->dataType)){
                fprintf(stderr, "Semantic ERROR: Index %s must be an integer\n", node->son[0]->symbol->text);
                SemanticErrors++;
            }
            if(!isCompatibleDataType(node->symbol->dataType, node->son[1]->dataType)){
                fprintf(stderr, "Semantic ERROR: Attribution %s with incompatible data type\n", node->symbol->text);
                SemanticErrors++;
            }
            break;
        case AST_FUNC:
			checkFunc(node);
			break;
        case AST_IF:
        case AST_IFELSE:
        case AST_WHILE:
            if(node->son[0]->dataType != DATATYPE_BOOL){
                fprintf(stderr, "Semantic ERROR: While condition must be a boolean expression\n");
				SemanticErrors++;
            }
            break;

        case AST_READ:
            if(node->symbol->type != SYMBOL_VARIABLE){
				fprintf(stderr, "Semantic ERROR: Read variables must be scalar\n");
				SemanticErrors++;
			}
            break;

        case AST_PRINT:
            printCheck(node);
            break;

        case AST_RETURN:
        default:
            break;
    }

    for (int i = 0; i < MAX_SONS; ++i) {
        checkNature(node->son[i]);
    }
}

void checkReturnTypes(AST *node){
	if (node != NULL && node->type == AST_DECFUNC){
		isValidReturn(node, node->symbol->dataType, node->symbol->text);
	}

	for(int i = 0; i < MAX_SONS; i++){
		if (node->son[i] == NULL) break;
		
        checkReturnTypes(node->son[i]);
	}
}

void isValidReturn(AST *node, int nodeDataType, char nodeName[20]){
	if (node == NULL) return;
    
	if (node->type == AST_RETURN){
		if (! isCompatibleDataType(nodeDataType, node->son[0]->dataType)){
			fprintf(stderr, "Semantic ERROR: Return has a different dataType than the function %s\n", nodeName);
			SemanticErrors++;
		}
	}
    
	for(int i = 0; i < MAX_SONS; i++){
		isValidReturn(node->son[i], nodeDataType, nodeName);
	}
}

void checkFunc(AST *node){
	AST* decFunc = getDecFunc(node->symbol->text, ROOT);
    if (decFunc == NULL){
        fprintf(stderr, "Semantic ERROR: Only functions can be called, %s isn't a function\n", node->symbol->text);
        SemanticErrors++;
    } else if (verifyArgumentsCount(node, decFunc)){
		calledArgsCompare(node->son[0], decFunc->son[1], node->symbol->text);					
	}
}

int getSemanticErrors(){
    return SemanticErrors;
}

int setDataType(int sonType){
    if (sonType){
        if (sonType == AST_TPINT){
            return DATATYPE_INT;
        } else if (sonType == AST_TPFLOAT){
            return DATATYPE_REAL;
        }  else if (sonType == AST_TPCHAR){
            return DATATYPE_CHAR;
        } else if (sonType == AST_TPBOOL){
            return DATATYPE_BOOL;
        }
    }
    return 0;
}

int isCompatibleDataType(int dt1, int dt2){
    return (isInteger(dt1) && isInteger(dt2)) || (dt1 == dt2);
}

bool checkVectorElements(AST *node, int dt, int vectorSize, int nElements, char *nameVector){
	if(node != NULL){
		if (nElements > vectorSize){
            fprintf(stderr,"elementos : %d %d\n", nElements, vectorSize);
            fprintf(stderr, "Semantic ERROR: Vector %s declaration with different size\n", nameVector);
            SemanticErrors++;
        }
        
        if(!isCompatibleDataType(node->son[0]->symbol->dataType, dt)) return false;

		if(node->son[1] != NULL)
			return checkVectorElements(node->son[1], dt, vectorSize, ++nElements, nameVector);
	}
	return true;
}

void printCheck(AST *node){
    if (!node) return;
    
    if(node->son[0]->type == AST_SYMBOL){
        if (! (node->son[0]->dataType == DATATYPE_STRING)){
            fprintf(stderr, "Semantic ERROR: String expected after print, %s isn't a string\n", node->son[0]->symbol->text);
            SemanticErrors++;
        }
    } else if (node->son[0]->type == AST_TYPEPRINT) {
        auxPrintCheck(node->son[0]);
    }
}

void auxPrintCheck(AST *node){
    if (! isCompatibleDataType(node->dataType, node->son[1]->dataType)){
        fprintf(stderr, "Semantic ERROR: Different types in print arguments\n");
    }
}

int isRelationalOp(int nodetype){
    return (nodetype == AST_LT || nodetype == AST_GT || nodetype == AST_EQ || nodetype == AST_LE || nodetype == AST_GE || nodetype == AST_DIF);
}

int isLogicalOp(int nodetype){
    return (nodetype == AST_AND || nodetype == AST_OR || nodetype == AST_NOT);
}

AST* getDecFunc(char *name, AST *node){
	if(node->symbol != NULL && strcmp(node->symbol->text, name) == 0 && node->type == AST_DECFUNC)
		return node;

	for(int i = 0; i < MAX_SONS; i++){
		if(node->son[i] == NULL) return NULL;

		AST *runing = getDecFunc(name, node->son[i]);
		if(runing != NULL) return runing;
	}

	return NULL;
}

bool verifyArgumentsCount(AST *node, AST *decFunc){
	int calledArgsCount   = getArgumentsCount(node->son[0]);
	int declaredArgsCount = getArgumentsCount(decFunc->son[1]);	

	if (calledArgsCount != declaredArgsCount){
    	fprintf(stderr, "Semantic ERROR: Different number of arguments in function %s\n", node->symbol->text);
		SemanticErrors++;
		return false;
	}
	return true;
}

int getArgumentsCount(AST *node){
    if (node == NULL) return 0;

	if (node->son[1] != NULL) return 1 + getArgumentsCount(node->son[1]);
	else return 0;
}

void calledArgsCompare(AST *node, AST *decFunc, char funcName[20]){
	if (node->son[0] != NULL){ // checks if have some argument in the func call
		if (! isCompatibleDataType(node->son[0]->dataType, decFunc->son[0]->symbol->dataType)){
			fprintf(stderr, "Semantic ERROR: Different argument types in function %s, argument %s \n", funcName, decFunc->son[0]->symbol->text);
			SemanticErrors++;
		}
        
        // checks whether the argument is a function or a vector, which is not allowed
        if (node->son[0]->type == AST_SYMBOL){
            if (node->son[0]->symbol->type == SYMBOL_FUNCTION){
                fprintf(stderr, "Semantic ERROR: You can't pass a function (%s) as argument\n", node->son[0]->symbol->text);
			    SemanticErrors++;
            } else if (node->son[0]->symbol->type == SYMBOL_VECTOR){
                fprintf(stderr, "Semantic ERROR: You can't pass a vector (%s) as argument\n", node->son[0]->symbol->text);
			    SemanticErrors++;
            }
        }
        
		if (node->son[1] != NULL) calledArgsCompare(node->son[1], decFunc->son[1], funcName);
	}
}
