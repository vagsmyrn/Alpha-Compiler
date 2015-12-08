#ifndef _VM_PRINT_H_
#define _VM_PRINT_H_

#include <stdio.h>
#include <stdlib.h>

#include "vm_global.h"
#include "vm.h"

extern char **const_str;
extern int size_str;

extern double *const_num;
extern int size_num;

extern function *const_func;
extern int size_func;

extern char **const_lib;
extern int size_lib;

extern instruction *code;
extern int codeSize;

void print_const(FILE *output);
void print_fcode(FILE *output);
void print_instruction(FILE *output, instruction *instruction);

char *literal_of_vmopcode(enum vmopcode opcode);
char *literal_of_vmarg(enum vmarg_t type);
void print_vmarg(FILE *output, vmarg *vmarg);

#endif // _VM_PRINT_
