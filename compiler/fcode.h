#ifndef _FCODE_H_
#define _FCODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "symtable.h"
#include "icode.h"


#define VECTOR_SIZE	16

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

typedef void (*generator_func_t)(quad *);

typedef struct func_node{
	SymbolTableEntry *sym;
	struct func_node *next;
} func_node;

typedef struct vmarg {
	enum vmarg_t type;
	unsigned val;
	SymbolTableEntry *sym; // XXX
} vmarg;

typedef struct instruction {
	enum vmopcode opcode;
	vmarg *result, *arg1, *arg2;
	unsigned srcLine;
	unsigned cur_instruction;
	unsigned label_no;
	
	struct instruction *next;
} instruction;

instruction *insert_instr(instruction *new_node);

void generate_fcode(quad* head_quad);

int const_new_str(char *s);
int const_new_num(double n);
int const_new_func(SymbolTableEntry *sym);

vmarg *make_operand(struct expr* e);

vmarg *make_numberoperand(double val);
vmarg *make_booloperand(unsigned val);
vmarg* make_retvaloperand(void);

instruction *create_instruction(enum vmopcode opcode);
vmarg *create_vmarg();

void print_fcode(FILE *output);
void print_instruction(FILE *output, instruction *instruction);
void print_vmarg(FILE *output, vmarg *vmarg);
void print_const_num(FILE *output);
void print_const_func(FILE *output);

void print_binary(FILE *output);
void print_binary_arg(FILE *output, vmarg *arg);

void push_func(SymbolTableEntry *func);
SymbolTableEntry *pop_func(void);

void generate_rel(enum vmopcode opcode, quad *quad);

void generate_ASSIGN_Q(quad *quad);
void generate_ADD(quad *quad);
void generate_SUB(quad *quad);
void generate_MUL(quad *quad);
void generate_DIV(quad *quad);
void generate_MOD(quad *quad);
void generate_UMINUS_Q(quad *quad);
void generate_AND_Q(quad *quad);
void generate_OR_Q(quad *quad);
void generate_NOT_Q(quad *quad);

void generate_IF_EQ(quad *quad);
void generate_IF_NOTEQ(quad *quad);
void generate_IF_LESS_EQ(quad *quad);
void generate_IF_GREATER_EQ(quad *quad);
void generate_IF_LESS(quad *quad);
void generate_IF_GREATER(quad *quad);

void generate_JUMP(quad *quad);
void generate_LABEL(quad *quad);

void generate_FUNCSTART(quad *quad);
void generate_FUNCEND(quad *quad);
void generate_RET(quad *quad);
void generate_CALL(quad *quad);
void generate_PARAM(quad *quad);
void generate_GETRETVAL(quad *quad);

void generate_TABLECREATE(quad *quad);
void generate_TABLEGETELEM(quad *quad);
void generate_TABLESETELEM(quad *quad);

char *literal_of_vmopcode(enum vmopcode opcode);
char *literal_of_vmarg(enum vmarg_t type);
#endif // _FCODE_H_

