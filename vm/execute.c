#include "execute.h"

execute_func_t executeFuncs[] = {
		execute_assign,
		execute_pusharg,
		execute_callfunc,

		execute_add,
		execute_sub,
		execute_mul,
		execute_dvd,
		execute_mod,
		execute_enterfunc,
		execute_exitfunc,
		execute_jump,
//		execute_and,
//		execute_or,
//		execute_not,
//		execute_jeq,
//		execute_jne,
//		execute_jgt,
//		execute_jlt,
//		execute_jge,
//		execute_jle,
//		execute_newtable,
//		execute_tablegetelem,
//		execute_tablesetelem,
//		execute_nop,
};

void execute_jump(instruction *instr){
	pc = instr->result->val;
}

void execute_enterfunc(instruction *instr){
	avm_memcell *func = avm_translate_operand(instr->result, &ax);
	function *funcInfo;

	assert(func);
	assert(pc == func->data.funcVal);

	totalActuals = 0;
	topsp = top;
	funcInfo = const_get_func(func->data.funcVal);
	top = top - funcInfo->localsize;
}

void execute_exitfunc(instruction *unused){
	unsigned oldTop = top;

	top = avm_get_envvalue(topsp + AVM_SAVED_TOPOFFSET);
	pc = avm_get_envvalue(topsp + AVM_SAVED_PCOFFSET);
	topsp = avm_get_envvalue(topsp + AVM_SAVED_TOPSPOFFSET);

	while(oldTop++ <= top){
		avm_memcellclear(&stack[oldTop]);
	}
}

void execute_arithmetic(instruction *instr){
	avm_memcell *result, *arg1, *arg2;

	arg1 = avm_translate_operand(instr->arg1, &ax);
	arg2 = avm_translate_operand(instr->arg2, &bx);
	result = avm_translate_operand(instr->result, NULL);

	if(arg1->type != number_m || arg2->type != number_m){
		print_err("Not a number.");
	}else{
		avm_memcellclear(result);
		result->type = number_m;
		switch(instr->opcode){
			case add:
				result->data.numVal = arg1->data.numVal + arg2->data.numVal;
				break;

			case sub:
				result->data.numVal = arg1->data.numVal - arg2->data.numVal;
				break;

			case mul:
				result->data.numVal = arg1->data.numVal * arg2->data.numVal;
				break;
			case dvd:
				result->data.numVal = arg1->data.numVal / arg2->data.numVal;
				break;
			case mod:
				result->data.numVal = ((unsigned)(arg1->data.numVal)) % ((unsigned)arg2->data.numVal);
				break;
			default:
				print_err("Illegal arithmetic operation");
				break;
		}

	}
}

void execute_callfunc(instruction *instr){
	avm_memcell *func = avm_translate_operand(instr->result, &ax);
	assert(func);
	avm_callsaveenvironment();

	switch(func->type){
		case userfunc_m:
			pc = func->data.funcVal;
			assert(pc < AVM_ENDING_PC);
			assert(code[pc].opcode == enterfunc);
			break;

		case string_m:
			avm_calllibfunc(func->data.strVal);
			break;

		case libfunc_m:
			avm_calllibfunc(func->data.libfuncVal);
			break;

		default:
			print_err("Undefined function.");
			executionFinished = 1;
			break;
	}

}

void execute_pusharg(instruction *instr){
	avm_memcell *arg = avm_translate_operand(instr->result, &ax);
	assert(arg);

	avm_assign(&stack[top], arg);
	totalActuals++;

	avm_dec_top();
}

void execute_cycle(void){
	if(executionFinished){
		return;
	}else if(pc == AVM_ENDING_PC) {
		executionFinished = 1;
		return;
	}else {
		assert(pc < AVM_ENDING_PC);
		instruction * instr = &code[pc];

		assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);

		unsigned oldPc = pc;
		fprintf(stdout, "pc: %u, %s\n", pc, literal_of_vmopcode(instr->opcode)); // XXX
		(*executeFuncs[instr->opcode])(instr);
		if(pc == oldPc){
			pc++;
		}
	}
}

void avm_assign(avm_memcell *lv, avm_memcell *rv){
	if(lv == rv)
		return;

	if(lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)
		return;

	if(rv->type == undef_m){
		print_err("assignment from undefined variable. Exiting...");
		executionFinished = 1;
	}

	avm_memcellclear(lv);

	memcpy(lv, rv, sizeof(avm_memcell));

	if(lv->type == string_m)
		lv->data.strVal = strdup(rv->data.strVal);
	else if(lv->type == table_m){
		;
	}
}

void execute_assign(instruction *instr){
	avm_memcell *lv = avm_translate_operand(instr->result, NULL);
	avm_memcell *rv = avm_translate_operand(instr->arg1, &ax);

//	assert(lv );
//	assert(&stack[AVM_STACKSIZE-1] >= lv);
//	assert(lv > &stack[top]);
//	assert(rv != NULL);

	avm_assign(lv, rv);
	top--; // XXX
}
