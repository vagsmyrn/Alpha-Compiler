#include "vm.h"

avm_memcell stack[AVM_STACKSIZE];
avm_memcell *globmem = &stack[AVM_STACKSIZE-1];
avm_memcell ax, bx, cx;
avm_memcell retval;

unsigned topsp = AVM_STACKSIZE-1, top = AVM_STACKSIZE-1;

unsigned char executionFinished = 0;
unsigned pc = 1;
unsigned currLine = 0;
unsigned totalActuals = 0;

char **const_str = NULL;
int size_str = 0;

double *const_num = NULL;
int size_num = 0;

function *const_func = NULL;
int size_func = 0;

char **const_lib = NULL;
int size_lib = 0;

instruction *code;
int codeSize = 0;


double const_get_num(unsigned index){
	return const_num[index];
}

char *const_get_str(unsigned index){
	return const_str[index];
}

char *const_get_lib(unsigned index){
	return const_lib[index];
}

function *const_get_func(unsigned index){
	return &const_func[index];
}

unsigned avm_totalactuals(void){
	return avm_get_envvalue(topsp + AVM_ACTUALS_OFFSET);
}

avm_memcell *avm_getactual(unsigned i){
	return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void avm_memcellclear(avm_memcell *cell){
	if(cell->type == undef_m){
		return;
	}else if(cell->type == string_m){
		free(cell->data.strVal);
	}else if(cell->type == table_m){
		// TODO
	}
}

unsigned avm_get_envvalue(unsigned i){
	assert(stack[i].type == number_m);
	unsigned val = (unsigned) stack[i].data.numVal;
	assert(stack[i].data.numVal == ((double)val));
	return val;
}

void avm_dec_top(void){
	if(!top) {
		print_err("Stack overflow.");
		executionFinished = 1;
	}else{
		top--;
	}
}

void avm_push_envvalue(unsigned val){
	stack[top].type = number_m;
	stack[top].data.numVal = val;
	avm_dec_top();
}

void avm_callsaveenvironment(void){
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top + totalActuals + 2);
	avm_push_envvalue(topsp);
}

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg){

	switch(arg->type){
		case global_a:
			return &stack[AVM_STACKSIZE-1-arg->val];
		case local_a:
			return &stack[topsp-1-arg->val];
		case formal_a:
			return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];

		case retval_a:
			return &retval;

		case number_a:
			reg->type = number_m;
			reg->data.numVal = const_get_num(arg->val);
			return reg;

		case string_a:
			reg->type = string_m;
			reg->data.strVal = const_get_str(arg->val);
			return reg;

		case bool_a:
			reg->type = bool_m;
			reg->data.boolVal = arg->val;
			return reg;

		case nil_a:
			reg->type = nil_m;
			return reg;

		case userfunc_a:
			reg->type = userfunc_m;
			reg->data.funcVal = arg->val;
			return reg;

		case libfunc_a:
			reg->type = libfunc_m;
			reg->data.libfuncVal = const_get_lib(arg->val);
			return reg;

		default:
			assert(0);
			return NULL;
	}
}

void read(FILE *input){
	int i, j;
	char buffer[1024];
	enum vmarg_t type;
	unsigned val;
	unsigned magic = 340200501;

	/****** magic ******/
	fread(&val, sizeof(unsigned), 1, input);
	if(val != magic){
		fprintf(stderr, "Invalid file.\n");
		exit(1);
	}

	/****** constr_str ******/
	fread(&size_str, sizeof(int), 1, input);
	const_str = calloc(size_str, sizeof(char *));
	
	for(i=0; i<size_str; i++){
		for(j=0; j<1024; j++){
			fread(&buffer[j], sizeof(char), 1, input);
			if(buffer[j] == '\0'){
				break;
			}
		}
		const_str[i] = strdup(buffer);
	}

	/****** constr_num ******/
	fread(&size_num, sizeof(int), 1, input);
	const_num = calloc(size_num, sizeof(double));
	
	for(i=0; i<size_num; i++){
		fread(&const_num[i], sizeof(double), 1, input);
	}

	/****** constr_func ******/
	fread(&size_func, sizeof(int), 1, input);
	const_func = calloc(size_func, sizeof(function));

	for(i=0; i<size_func; i++){
		fread(&(const_func[i].address), sizeof(int), 1, input);
		fread(&(const_func[i].localsize), sizeof(int), 1, input);
		for(j=0; j<1024; j++){
			fread(&buffer[j], sizeof(char), 1, input);
			if(buffer[j] == '\0'){
				break;
			}
		}
		const_func[i].id = strdup(buffer);
	}

	/****** constr_lib ******/
	fread(&size_lib, sizeof(int), 1, input);
	const_lib = calloc(size_lib, sizeof(char *));

	for(i=0; i<size_lib; i++){
		for(j=0; j<1024; j++){
			fread(&buffer[j], sizeof(char), 1, input);
			if(buffer[j] == '\0'){
				break;
			}
		}
		const_lib[i] = strdup(buffer);
	}

	/****** prog ******/
	fread(&codeSize, sizeof(int), 1, input);
	code = calloc(codeSize+1, sizeof(instruction));
	
	for(i=0; i<codeSize; i++){
		fread(&(code[i+1].opcode), sizeof(enum vmopcode), 1, input);
		
		fread(&type, sizeof(enum vmarg_t), 1, input);
		fread(&val, sizeof(unsigned), 1, input);
		code[i+1].arg1 = create_vmarg(type, val);
		
		fread(&type, sizeof(enum vmarg_t), 1, input);
		fread(&val, sizeof(unsigned), 1, input);
		code[i+1].arg2 = create_vmarg(type, val);
		
		fread(&type, sizeof(enum vmarg_t), 1, input);
		fread(&val, sizeof(unsigned), 1, input);
		code[i+1].result = create_vmarg(type, val);
		
	}
	codeSize++;

}

vmarg *create_vmarg(enum vmarg_t type, unsigned val){
	vmarg *res;
	
	if(type == nil_a){
		return NULL;
	}
	
	res = calloc(1, sizeof(vmarg));
	res->type = type;
	res->val = val;
	
	return res;
}

void avm_initstack(void){
	unsigned i;

	for(i=0; i<AVM_STACKSIZE; i++){
		AVM_WIPEOUT(stack[i]);
		stack[i].type = undef_m;
	}
}

int main(int argn, char *argv[]){
	FILE *input;
	
	input = fopen(argv[1], "rb");
	read(input);
	
	fclose(input);
	
	print_const(stdout);
	print_fcode(stdout);

	avm_initstack();
	
	fprintf(stdout, "===== output =====\n");
	while(!executionFinished)
		execute_cycle();
	
	return 0;
}
