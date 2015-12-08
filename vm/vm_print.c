#include "vm_print.h"


void print_const(FILE *output){
	int i;
	
	fprintf(output, "===== constr_str =====\n" );
	for(i=0; i<size_str; i++){
		fprintf(output, "%d:%s\n", i, const_str[i]);
	}

	fprintf(output, "===== constr_num =====\n" );
	for(i=0; i<size_num; i++){
		fprintf(output, "%d:%f\n", i, const_num[i]);
	}

	fprintf(output, "===== constr_func =====\n" );
	for(i=0; i<size_func; i++){
		fprintf(output, "%s->%d, %d\n", const_func[i].id, const_func[i].address, const_func[i].localsize);
	}

	fprintf(output, "===== constr_lib =====\n" );
	for(i=0; i<size_lib; i++){
		fprintf(output, "%d:%s\n", i, const_lib[i]);
	}

}

void print_fcode(FILE *output){
	int i;
	fprintf(output, "===== fcode(%d) =====\n", codeSize-1);
	for(i=1; i<codeSize; i++){
		fprintf(output, "%2d: ", i);
		print_instruction(output, &code[i]);
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
			fprintf(output, "%d(%s) ", (int)(vmarg->type), literal_of_vmarg(vmarg->type));
			break;

		case libfunc_a:
			fprintf(output, "%d(%s) %d:%s ", (int)(vmarg->type), literal_of_vmarg(vmarg->type), vmarg->val, const_lib[vmarg->val]);
			break;

		case userfunc_a:
			fprintf(output, "%d(%s) %d:%s ", (int)(vmarg->type), literal_of_vmarg(vmarg->type), vmarg->val);//, const_func[vmarg->val].id);
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
