#include <stdio.h>
#include <stdlib.h>

#include "fcode.h"

char **const_str = NULL;
int size_str = 0, index_str = -1;

char **const_lib = NULL;
int size_lib = 0, index_lib = -1;

double *const_num = NULL;
int size_num = 0, index_num = -1;

SymbolTableEntry **const_func  = NULL;
int size_func = 0, index_func = -1;

instruction *head_instr = NULL;
int cur_instruction = 0;

func_node *ret_stack  = NULL;


generator_func_t generators[] = {
	generate_ASSIGN_Q,
	generate_ADD,
	generate_SUB,
	generate_MUL,
	generate_DIV,
	generate_MOD,
	generate_UMINUS_Q,
	generate_AND_Q,
	generate_OR_Q,
	generate_NOT_Q,
	
	generate_IF_EQ,
	generate_IF_NOTEQ,
	generate_IF_LESS_EQ,
	generate_IF_GREATER_EQ,
	generate_IF_LESS,
	generate_IF_GREATER,
	generate_JUMP,
	generate_LABEL,
	
	generate_FUNCSTART,
	generate_FUNCEND,
	generate_RET,
	generate_CALL,
	generate_PARAM,
	generate_GETRETVAL,
	
	generate_TABLECREATE,
	generate_TABLEGETELEM,
	generate_TABLESETELEM,
/*
*/
};

void generate_TABLECREATE(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(newtable);
	instruction->result = make_operand(quad->result);
	
}

void generate_TABLEGETELEM(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(tablegetelem);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_operand(quad->result->index);
	instruction->result = make_operand(quad->result);
	
}

void generate_TABLESETELEM(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(tablesetelem);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->result = make_operand(quad->result);
	
}

void generate_FUNCSTART(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(jump);
	instruction->result = create_vmarg();
	instruction->result->type = label_a;
	instruction->result->sym = quad->result->sym;


	instruction = create_instruction(enterfunc);

	push_func(quad->result->sym);
	quad->result->sym->var->funcStart = cur_instruction;

	instruction->result = make_operand(quad->result);
	
}

void generate_FUNCEND(quad *quad){
	instruction *temp;
	instruction *instruction;
	int first = 1;
	
	instruction = create_instruction(exitfunc);
	instruction->result = make_operand(quad->result);
	
	
	for(temp=head_instr; temp!=NULL; temp=temp->next){
		if(temp->opcode == jump && temp->result->sym != NULL && temp->result->sym == quad->result->sym){
			temp->result->val = cur_instruction;
			if(first){
				temp->result->val++;
				first = 0;
			}
		}
	}
	
	pop_func();
}

void generate_RET(quad *quad){
	instruction *instruction;
	
	if(quad->result != NULL){
		instruction = create_instruction(assign);
		instruction->arg1 = make_operand(quad->result);
		instruction->result = make_retvaloperand();
	}
	
	instruction = create_instruction(jump);
	instruction->result = create_vmarg();
	instruction->result->type = label_a;
	instruction->result->sym = ret_stack->sym;	
	
}

void generate_CALL(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(callfunc);
	instruction->result = make_operand(quad->result);
}

void generate_PARAM(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(pusharg);
	instruction->result = make_operand(quad->result);
}

void generate_GETRETVAL(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(assign);
	instruction->arg1 = make_operand(quad->result);
	instruction->result = make_retvaloperand();
	
}

void generate_ASSIGN_Q(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(assign);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->result = make_operand(quad->result);
	
}

void generate_ADD(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(add);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_operand(quad->arg2);
	instruction->result = make_operand(quad->result);
}

void generate_SUB(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(sub);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_operand(quad->arg2);
	instruction->result = make_operand(quad->result);
}

void generate_MUL(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(mul);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_operand(quad->arg2);
	instruction->result = make_operand(quad->result);
}

void generate_DIV(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(dvd);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_operand(quad->arg2);
	instruction->result = make_operand(quad->result);
}

void generate_MOD(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(mod);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_operand(quad->arg2);
	instruction->result = make_operand(quad->result);
}

void generate_UMINUS_Q(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(mul);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_numberoperand(-1.0);
	instruction->result = make_operand(quad->result);
}

void generate_AND_Q(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(and);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_operand(quad->arg2);
	instruction->result = make_operand(quad->result);
}

void generate_OR_Q(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(or);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_operand(quad->arg2);
	instruction->result = make_operand(quad->result);
}

void generate_NOT_Q(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(not);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->result = make_operand(quad->result);
}

void generate_JUMP(quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(jump);
	instruction->result = create_vmarg();
	instruction->result->type = label_a;
	instruction->label_no = quad->result->labelNo;
}

void generate_LABEL(quad *quad){
	instruction *temp;
	
	for(temp=head_instr; temp!=NULL; temp=temp->next){
		if((temp->opcode == jump 
				|| temp->opcode == jeq
				|| temp->opcode == jne
				|| temp->opcode == jgt
				|| temp->opcode == jlt
				|| temp->opcode == jge
				|| temp->opcode == jle
			)
			&& temp->label_no == quad->label){
			temp->result->val = cur_instruction+1;
		}
	}

}

void generate_fcode(quad* head_quad){
	quad *temp;
	
	for(temp = head_quad; temp != NULL; temp = temp->next){
		generators[temp->op](temp);
	}
}

void generate_IF_EQ(quad *quad){
	generate_rel(jeq, quad);
}
void generate_IF_NOTEQ(quad *quad){
	generate_rel(jne, quad);
}
void generate_IF_LESS_EQ(quad *quad){
	generate_rel(jle, quad);
}
void generate_IF_GREATER_EQ(quad *quad){
	generate_rel(jge, quad);
}
void generate_IF_LESS(quad *quad){
	generate_rel(jlt, quad);
}
void generate_IF_GREATER(quad *quad){
	generate_rel(jgt, quad);
}
void generate_rel(enum vmopcode opcode, quad *quad){
	instruction *instruction;
	
	instruction = create_instruction(opcode);
	instruction->arg1 = make_operand(quad->arg1);
	instruction->arg2 = make_operand(quad->arg2);
	
	instruction->result = create_vmarg();
	instruction->result->type = label_a;
	instruction->label_no = quad->result->labelNo;

}

instruction *insert_instr(instruction *new_node){
	instruction *temp;
	
	cur_instruction++;
	new_node->cur_instruction = cur_instruction;
	
	if(head_instr == NULL){
		head_instr = new_node;
		
		return head_instr;
	}
	
	for(temp=head_instr; temp!=NULL; temp=temp->next){
		if(temp->next == NULL){
			temp->next = new_node;
			return head_instr;
		}
	}
	return head_instr;
}

int const_new_str(char *s){
	index_str++;
	if(size_str == 0){
		size_str = VECTOR_SIZE;
		const_str = malloc(VECTOR_SIZE*sizeof(char *));
	}else if(size_str<=index_str){
		size_str *= 2;
		const_str = realloc(const_str, size_str*sizeof(char *));
	}
	const_str[index_str] = s;
	return index_str;
}

int const_new_lib(char *s){
	int i;

	for(i=0; i<=index_lib; i++){
		if(strcmp(const_lib[i], s) == 0)
			return i;
	}

	index_lib++;
	if(size_lib == 0){
		size_lib = VECTOR_SIZE;
		const_lib = malloc(VECTOR_SIZE*sizeof(char *));
	}else if(size_lib<=index_lib){
		size_lib *= 2;
		const_lib = realloc(const_lib, size_lib*sizeof(char *));
	}
	const_lib[index_lib] = s;
	return index_lib;
}

int const_new_num(double n){
	index_num++;
	if(size_num == 0){
		size_num = VECTOR_SIZE;
		const_num = calloc(VECTOR_SIZE, sizeof(double));
	}else if(size_num<=index_num){
		size_num *= 2;
		const_num = realloc(const_num, size_num*sizeof(double));
	}
	const_num[index_num] = n;
	return index_num;
}

int const_new_func(SymbolTableEntry *sym){
	int i;
	
	for(i=0; i<=index_func; i++){
		if(const_func[i] == sym)
			return i;
	}

	index_func++;
	if(size_func == 0){
		size_func = VECTOR_SIZE;
		const_func = calloc(VECTOR_SIZE, sizeof(SymbolTableEntry *));
	}else if(size_func<=index_func){
		size_func *= 2;
		const_func = realloc(const_func, size_func*sizeof(SymbolTableEntry *));
	}
	const_func[index_func] = sym;
	return index_func;
}

vmarg *make_operand(struct expr* e){
	if(e == NULL){
		return NULL;
	}
	vmarg* arg;
	arg = create_vmarg();
	
	switch(e->type){		
		//All those below use a variable for storage
		case VAR_E:
		case TABLEITEM_E:
		case ARITHEXPR_E:
		case ASSIGNEXPR_E:
		case BOOLEXPR_E:
		case NEWTABLE_E: {
			assert(e->sym);
			arg->val = e->sym->var->offset;
			arg->sym = e->sym; // XXX
			
			switch(e->sym->space){
				case GLOBAL_SP: {
					arg->type = global_a;
					break;
				}
				case LOCAL_SP: {
					arg->type = local_a;
					break;
				}
				case FORMAL_SP: {
					arg->type = formal_a;
					break;
				}
				default: assert(0); //should not reach here
			}	
			
			break; //from case newtable_e
		}
		
		//CONSTANTS
		case CONSTBOOL_E: {
			arg->val = e->boolConst;
			arg->type = bool_a;
			break;
		}
		
		case CONSTSTRING_E: {
			arg->val = const_new_str(e->strConst);
			arg->type = string_a;
			break;
		}
		
		case CONSTNUM_E: {
			arg->val = const_new_num(e->numConst);
			arg->type = number_a;
			break;
		}
		
		case NIL_E: {
			arg->type = nil_a;
			break;
		}
		
		//FUNCTIONS
		case PROGRAMFUNC_E: {
			arg->type = userfunc_a;
			const_new_func(e->sym);
			arg->val = e->sym->var->funcStart;
			break;
		}
		
		case LIBRARYFUNC_E: {
			arg->type = libfunc_a;
			arg->val = const_new_lib(e->sym->var->name);
			break;
		}
		
		default: assert(0); break;//should not reach here!
		
	}
	return arg;
}

vmarg *make_numberoperand(double val){
	vmarg* arg;
	
	arg = create_vmarg();
	arg->val = const_new_num(val);
	arg->type = number_a;
	
	return arg;
}

vmarg *make_booloperand(unsigned val){
	vmarg* arg;
	
	arg = create_vmarg();
	arg->val = val;
	arg->type = bool_a;
	
	return arg;
}

vmarg *make_retvaloperand(void){
	vmarg* arg;
	
	arg = create_vmarg();
	arg->type = retval_a;
	return arg;
}

instruction *create_instruction(enum vmopcode opcode){
	instruction *temp;
	
	temp = calloc(1, sizeof(instruction));
	temp->opcode = opcode;
	insert_instr(temp);
	
	return temp;
}

vmarg *create_vmarg(){
	vmarg *temp;
	
	temp = calloc(1, sizeof(vmarg));
	
	return temp;
}


void push_func(SymbolTableEntry *func){
	func_node *new_node;
	
	new_node = calloc(1, sizeof(func_node));
	new_node->sym = func;
	new_node->next = ret_stack;
	ret_stack = new_node;
}

SymbolTableEntry *pop_func(void){
	SymbolTableEntry *res;
	func_node *old_head;
	
	assert(ret_stack != NULL);
	
	res = ret_stack->sym;
	old_head = ret_stack;
	ret_stack = ret_stack->next;
	
	free(old_head);
	
	return res;
}

void print_fcode(FILE *output){
	instruction *temp;
	int i=1;
	
	for(temp=head_instr; temp!=NULL; temp=temp->next){
		fprintf(output, "%2d: ", i++);
		print_instruction(output, temp);
	}
}

void print_instruction(FILE *output, instruction *instruction){
	fprintf(output, "%s ", literal_of_vmopcode(instruction->opcode));
	print_vmarg(output, instruction->arg1);
	print_vmarg(output, instruction->arg2);
	print_vmarg(output, instruction->result);
	fprintf(output, "\n");
}

void print_vmarg(FILE *output, vmarg *vmarg){
	if(vmarg == NULL){
		fprintf(output, "- | ");
		return;
	}
	switch(vmarg->type){
		case global_a:
		case local_a:
		case formal_a:
			fprintf(output, "%d(%s) %d:%s ", (int)(vmarg->type), literal_of_vmarg(vmarg->type), vmarg->val, vmarg->sym->var->name);
			break;

		case libfunc_a:
			fprintf(output, "%d(%s) %d:%s ", (int)(vmarg->type), literal_of_vmarg(vmarg->type), vmarg->val, const_lib[vmarg->val]);
			break;

		case userfunc_a:
			fprintf(output, "%d(%s)@%d ", (int)(vmarg->type), literal_of_vmarg(vmarg->type), vmarg->val);//, const_func[vmarg->val]->var->name);
			break;
			
		case number_a:
			fprintf(output, "%d(%s) %d:%.1f ", (int)(vmarg->type), literal_of_vmarg(vmarg->type), vmarg->val, const_num[vmarg->val]);
			break;
			
		case string_a:
			fprintf(output, "%d(%s) %d:%s ", (int)(vmarg->type), literal_of_vmarg(vmarg->type), vmarg->val, const_str[vmarg->val]);
			break;
			
		case bool_a:
			fprintf(output, "%d(%s) %s ", (int)(vmarg->type), literal_of_vmarg(vmarg->type), (vmarg->val)?("TRUE"):("FALSE"));
			break;
			
		case label_a:
			fprintf(output, "%d(%s) %d ", (int)(vmarg->type), literal_of_vmarg(vmarg->type), vmarg->val);
			break;
			
		case retval_a:
			fprintf(output, "%d(%s) ", (int)(vmarg->type), literal_of_vmarg(vmarg->type));
			break;

		default:
			fprintf(output, "XXX ");
			break;
	}
	fprintf(output, " | ");
}

char *literal_of_vmarg(enum vmarg_t type){
	char *literals[] = {
		"label_a",
		"global_a",
		"local_a",
		"formal_a",
		"bool_a",
		"string_a",
		"number_a",
		"nil_a",
		"userfunc_a",
		"libfunc_a",
		"retval_a",
	};
	return literals[type];
}

char *literal_of_vmopcode(enum vmopcode opcode){
	char *literals[] = {
		"assign",
		"pusharg",
		"callfunc",
		"add",
		"sub",
		"mul",
		"dvd",
		"mod",
		"enterfunc",
		"exitfunc",
		"jump",
		"and",
		"or",
		"not",
		"jeq",
		"jne",
		"jgt",
		"jlt",
		"jge",
		"jle",
		"newtable",
		"tablegetelem",
		"tablesetelem",
		"nop",	
	};
	return literals[opcode];
}

void print_const_str(FILE *output){
	int i;
	
	fprintf(output, "===== constr_str =====\n" );
	for(i=0; i<=index_str; i++){
		fprintf(output, "%d:%s\n", i, const_str[i]);
	}

}

void print_const_num(FILE *output){
	int i;
	
	for(i=0; i<=index_num; i++){
		fprintf(output, "%d:%.2f\n", i, const_num[i]);
	}

}

void print_const_func(FILE *output){
	int i;
	
	for(i=0; i<=index_func; i++){
		fprintf(output, "%d:%s\n", i, const_func[i]->var->name);
	}

}

void print_binary(FILE *output){
	int int1, i;
	char c1;
	instruction *temp;

	unsigned magic = 340200501;
	fwrite(&magic, sizeof(unsigned),1,output);


	/****** constr_str ******/
	int1 = index_str + 1;
	fwrite(&int1, sizeof(int), 1, output);
	
	for(i=0; i<index_str+1 ; i++){
		fprintf(output, "%s", const_str[i]);
		c1 = '\0';
		fwrite(&c1, sizeof(char), 1, output);
	}

	/****** constr_num ******/
	int1 = index_num + 1;
	fwrite(&int1, sizeof(int), 1, output);
	
	for(i=0; i<index_num+1 ; i++){
		fwrite(&const_num[i], sizeof(double), 1, output);
	}
	
	/****** constr_func ******/
	int1 = index_func + 1;
	fwrite(&int1, sizeof(int), 1, output);

	for(i=0; i<index_func+1 ; i++){
		fwrite(&(const_func[i]->var->funcStart), sizeof(int), 1, output);

		int int1 = const_func[i]->var->formalVarsCount + const_func[i]->var->scopeVarsCount;
		fwrite(&int1, sizeof(int), 1, output);

		fprintf(output, "%s", const_func[i]->var->name);
		c1 = '\0';
		fwrite(&c1, sizeof(char), 1, output);
	}

	/****** constr_lib ******/
	int1 = index_lib + 1;
	fwrite(&int1, sizeof(int), 1, output);

	for(i=0; i<index_lib+1 ; i++){
		fprintf(output, "%s", const_lib[i]);
		c1 = '\0';
		fwrite(&c1, sizeof(char), 1, output);
	}

	/***** instruction ******/
	int1 = cur_instruction;
	fwrite(&int1, sizeof(int), 1, output);
	
	for(temp=head_instr; temp!=NULL; temp=temp->next){
		fwrite(&temp->opcode, sizeof(enum vmopcode), 1, output);
		
		print_binary_arg(output, temp->arg1);
		print_binary_arg(output, temp->arg2);
		print_binary_arg(output, temp->result);
	}

}

void print_binary_arg(FILE *output, vmarg *arg){
	enum vmarg_t nil = nil_a;
	unsigned nil_val = 0;
	
	if(arg != NULL){
		fwrite(&(arg->type), sizeof(enum vmarg_t), 1, output);
		fwrite(&(arg->val), sizeof(unsigned), 1, output);
	}else{
		fwrite(&nil, sizeof(enum vmarg_t), 1, output);
		fwrite(&nil_val, sizeof(unsigned), 1, output);
	}
}


