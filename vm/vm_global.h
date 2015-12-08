#ifndef _VM_GLOBAL_H_
#define _VM_GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>

#define AVM_STACKSIZE			4096
#define AVM_WIPEOUT(m)			(memset(&(m), 0, sizeof(m)))
#define AVM_MAX_INSTRUCTIONS	nop
#define AVM_STACKENV_SIZE		4
#define AVM_ENDING_PC			codeSize

#define AVM_ACTUALS_OFFSET		4
#define AVM_SAVED_PCOFFSET		3
#define AVM_SAVED_TOPOFFSET		2
#define AVM_SAVED_TOPSPOFFSET	1

#define log(...)		{fprintf(stdout, "\t: "); fprintf(stdout, __VA_ARGS__); putchar('\n');}
#define print_warn(...)	{fprintf(stdout, "WARNING%2u: ", pc); fprintf(stdout, __VA_ARGS__); putchar('\n');}
#define print_err(...)	{fprintf(stderr, "ERROR %2u: ", pc); fprintf(stderr, __VA_ARGS__); fprintf(stderr,"\n");}


enum vmopcode {
	assign,
	pusharg,
	callfunc,
	add,
	sub,
	mul,
	dvd,
	mod,
	enterfunc,
	exitfunc,
	jump,
	and,
	or,
	not,
	jeq,
	jne,
	jgt,
	jlt,
	jge,
	jle,
	newtable,
	tablegetelem,
	tablesetelem,
	nop,	
};



enum vmarg_t {
	label_a,
	global_a,
	local_a,
	formal_a,
	bool_a,
	string_a,
	number_a,
	nil_a,
	userfunc_a,
	libfunc_a,
	retval_a,
};

typedef enum avm_memcell_t {
	number_m = 0,
	string_m,
	bool_m,
	table_m,
	userfunc_m,
	libfunc_m,
	nil_m,
	undef_m,
} avm_memcell_t;

typedef struct avm_table {
	int d;
} avm_table;

typedef struct avm_memcell {
	avm_memcell_t type;
	union {
		double numVal;
		char *strVal;
		unsigned char boolVal;
		avm_table *tableVal;
		unsigned funcVal;
		char *libfuncVal;
	} data;
} avm_memcell;

typedef struct vmarg {
	enum vmarg_t type;
	unsigned val;
} vmarg;

typedef struct function {
	int address;
	int localsize;
	char *id;
} function;

typedef struct instruction {
	enum vmopcode opcode;
	vmarg *result, *arg1, *arg2;
} instruction;

extern avm_memcell stack[AVM_STACKSIZE];
extern avm_memcell *globmem;
extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned topsp, top;
extern unsigned pc;
extern unsigned totalActuals;
#endif // _VM_GLOBAL_
