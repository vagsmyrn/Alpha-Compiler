#include "symtable.h"

SymbolTableEntry *head = NULL;
FunctionNode *functionStack = NULL;
int globalScopeVarsCount = 0;

int functionBetween = 0;

Variable *var_copy(Variable *source, char *target_name){
	Variable *target;
	
	target = malloc(sizeof(Variable));
	target->name = target_name;
	target->scope = source->scope;
	
	target->line = source->line;
	target->members = source->members;
	
	return target;
}

SymbolTableEntry *st_copy(SymbolTableEntry *source, Variable *target_var){
	SymbolTableEntry *target;
	
	target = malloc(sizeof(SymbolTableEntry));
	target->active = source->active;
	target->var = target_var;
	target->type = source->type;
	target->next = NULL;
	
	return target;
}


SymbolTableEntry *insert(Variable *var, enum SymbolTableType type){
	SymbolTableEntry *new_node;
	new_node = malloc(sizeof(SymbolTableEntry));
	
	new_node->type = type;
	new_node->var = var;
	new_node->active = 1;

	if(type == GLOBAL_VAR){ // || LIBFUNC){
		new_node->var->offset = globalScopeVarsCount++;
	}else if(type == LOCAL_VAR){
		if(peek() != NULL)
			new_node->var->offset = peek()->scopeVarsCount++;
		else
			new_node->var->offset = globalScopeVarsCount++;
	}else if(type == FORMAL_VAR){
		new_node->var->offset = peek()->formalVarsCount++;
	}
	
	if(type == FORMAL_VAR){
		new_node->space = FORMAL_SP;
	}else if(peek() == NULL){
		new_node->space = GLOBAL_SP;
	}else{
		new_node->space = LOCAL_SP;
	}

	new_node->next = head;
	head = new_node;

	return new_node;
}

SymbolTableEntry *insert_member(SymbolTableEntry *parent, Variable *var) {
	SymbolTableEntry *new_node;
	new_node = malloc(sizeof(SymbolTableEntry));
	
	if(parent->var->scope == 0)
		new_node->type = GLOBAL_VAR;
	else
		new_node->type = LOCAL_VAR;
	new_node->var = var;
	new_node->active = 1;

	new_node->next = parent->var->members;
	parent->var->members = new_node;

	return new_node;
}

SymbolTableEntry *lookup(int scope, char *name, enum LookupScope type){
	SymbolTableEntry *temp, *firstFunction = NULL;
	int scopeChanged = 0;
	functionBetween = 0;
	
	for(temp=head; temp!=NULL; temp=temp->next){
		if(type == GLOBAL_SCOPE && temp->var->scope != 0){
				continue;
		}			
		if(temp->type == USERFUNC){
			functionBetween = 1;
			if(firstFunction == NULL){
				firstFunction = temp;
				if(strcmp(name, temp->var->name) == 0){ // && type == FORMAL_SCOPE){
					return temp;
				}
			}
		}
		
		if(temp->var->scope < scope){
			scopeChanged = 1;
		}

		if(strcmp(name, temp->var->name) == 0 
			&& ((!scopeChanged && scope >= temp->var->scope) || (scopeChanged && scope > temp->var->scope))  ){
			if(type == ANY){
				return temp;
			} else if(type == GLOBAL_SCOPE 
					&& (temp->type==GLOBAL_VAR || temp->type==LIBFUNC || (temp->type=USERFUNC && temp->var->scope == 0))){
				return temp;
			} else if(type == LOCAL_LIB_SCOPE 
					&& (((temp->type==LOCAL_VAR || temp->type==USERFUNC || temp->type==FORMAL_VAR || (temp->type==GLOBAL_VAR && scope==0) ) 
					&& temp->var->scope==scope)|| temp->type==LIBFUNC)){ // TODO Check ()
				return temp;
			} else if(type == FORMAL_SCOPE
					&& ((temp->type==FORMAL_VAR && temp->var->scope==scope) || temp->type==LIBFUNC)){
				return temp;
			}
		}
	}
	return NULL;
}
SymbolTableEntry *lookup_variable(Variable *var){
	SymbolTableEntry *temp;
	
	for(temp=head; temp!=NULL; temp=temp->next){
		if(temp->var == var){
			return temp;
		}
	}
	return NULL;

}

SymbolTableEntry *lookup_member(SymbolTableEntry *parent, char *name) {
	SymbolTableEntry *temp;
	
	for(temp=parent->var->members; temp!=NULL; temp=temp->next){
		if(strcmp(temp->var->name, name) == 0){
			return temp;
		}
	}
	return NULL;
}


void print_list(void){
	fprintf(stderr, "\n\n========= Symbol table =================\n");
	fprintf(stderr, "SCOPE|        NAME         |   TYPE     |  MEMBERS\n");
	print_node(head);

}


void print_node(SymbolTableEntry *node){
	if(node == NULL)
	    return;
	print_node(node->next);

	fprintf(stderr, "%-5d| %-20s| %-11s| ", node->var->scope, node->var->name, literal_of(node->type));
	
	print_member(node->var->members);
	fprintf(stderr, "\n");
}

void print_member(SymbolTableEntry *node){
	if(node == NULL)
	    return;
	fprintf(stderr, "%s ", node->var->name);

	print_member(node->next);
}

char *literal_of(enum SymbolTableType type){
    switch(type){
        case(GLOBAL_VAR):
            return "GLOBAL_VAR";
    	case(LOCAL_VAR):
    	    return "LOCAL_VAR";
	    case(FORMAL_VAR):
        	return "FORMAL_VAR";
	    case(USERFUNC):
	        return "USERFUNC";
	    case(LIBFUNC):
	        return "LIBFUNC";
	   	default:
    	    return "UNKNOWN";
    }
}

void push(Variable *func){
	FunctionNode *newNode;

	newNode = malloc(sizeof(FunctionNode));
	newNode->val = func;

	newNode->next = functionStack;
	functionStack = newNode;
	
	// XXX fprintf(stderr, "push ====>%s\n", func->name);
}

Variable *pop(void){
	FunctionNode *oldHead;
	Variable *res;

	if(functionStack == NULL){
		fprintf(stderr, "===> Pop in empty function stack!\n");
		return NULL;
	}

	oldHead = functionStack;
	functionStack = oldHead->next;

	res = oldHead->val;
	free(oldHead);

	// XXX fprintf(stderr, "pop  ====>%s\n", res->name);
	return res;
}

Variable *peek(void){
	if(functionStack == NULL){
		return NULL;
	}
	return functionStack->val;
}
