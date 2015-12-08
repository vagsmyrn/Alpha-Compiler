#ifndef EXECUTE_H_
#define EXECUTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "vm_global.h"
#include "vm.h"
#include "vm_lib_funcs.h"


extern unsigned char executionFinished;
extern unsigned pc;
extern instruction *code;
extern int codeSize;

typedef void (*execute_func_t)(instruction *);

void execute_cycle(void);

void avm_assign(avm_memcell *lv, avm_memcell *rv);

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_dvd execute_arithmetic
#define execute_mod execute_arithmetic

void execute_assign(instruction *instr);
void execute_pusharg(instruction *instr);
void execute_callfunc(instruction *instr);
void execute_arithmetic(instruction *instr);
void execute_enterfunc(instruction *instr);
void execute_exitfunc(instruction *unused);
void execute_jump(instruction *instr);
/*
void execute_and(instruction *instr);
void execute_or(instruction *instr);
void execute_not(instruction *instr);
void execute_jeq(instruction *instr);
void execute_jne(instruction *instr);
void execute_jgt(instruction *instr);
void execute_jlt(instruction *instr);
void execute_jge(instruction *instr);
void execute_jle(instruction *instr);
void execute_newtable(instruction *instr);
void execute_tablegetelem(instruction *instr);
void execute_tablesetelem(instruction *instr);
void execute_nop(instruction *instr);
*/

#endif /* EXECUTE_H_ */
