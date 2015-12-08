#ifndef _ICODE_H_
#define _ICODE_H_

#include <stdio.h>
#include <stdlib.h>

#include "symtable.h"

enum iopcode {
	ASSIGN_Q,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	UMINUS_Q,
	AND_Q,
	OR_Q,
	NOT_Q,
	IF_EQ,
	IF_NOTEQ,
	IF_LESS_EQ,
	IF_GREATER_EQ,
	IF_LESS,
	IF_GREATER,
	JUMP,
	LABEL,
	FUNCSTART,
	FUNCEND,
	RET,
	CALL,
	PARAM,
	GETRETVAL,
	TABLECREATE,
	TABLEGETELEM,
	TABLESETELEM,
};

enum expr_t {
	VAR_E,
	TABLEITEM_E,
	
	PROGRAMFUNC_E,
	LIBRARYFUNC_E,
	
	ARITHEXPR_E,
	BOOLEXPR_E,
	ASSIGNEXPR_E,
	NEWTABLE_E,
	
	CONSTNUM_E,
	CONSTBOOL_E,
	CONSTSTRING_E,
	
	NIL_E,
	LABEL_E

};

typedef struct expr {
	enum expr_t 		type;
	SymbolTableEntry*	sym;
	struct expr*		index;
	double				numConst;
	char*				strConst;
	char				boolConst;
	unsigned			labelNo;
	struct expr*		next;
	struct quad*		quad;
} expr;

typedef struct quad {
	enum iopcode	op;
	expr*			arg1;
	expr*			arg2;
	expr*			result;
	int				label;
	int				line;
	
	struct quad*	next;
} quad;

typedef struct loop {
	struct quad*	previous_quad;
	struct expr*	start_label;
	struct expr*	end_label;
	
	struct loop *next;
} loop;

extern FILE *icode_stream;

void push_loop(quad *previous_quad, expr *start_label, expr *end_quad);
loop *pop_loop(void);
loop *peek_loop(void);

quad *push_suffix(quad *new_quad);
void flush_suffix(void);

quad *insert_quad(quad *new_node);
quad *insert_after_quad(quad *target, quad *new_node);
quad *insert_before_quad(quad *target, quad *new_node);
quad *get_last_quad(void);
quad *create_quad(enum iopcode op, expr* arg1, expr* arg2, expr* result, int label, int line);
expr *create_expr(enum expr_t type, SymbolTableEntry *sym);

void print_icode(void);
void print_quad(quad *quad);
void print_expr(expr *quad);
char *literal_of_op(enum iopcode op);
char *literal_of_expr(enum expr_t type);
#endif // _ICODE_H_
