#ifndef _VM_H_
#define _VM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "vm_global.h"
#include "vm_print.h"
#include "execute.h"

void avm_initstack(void);
void avm_memcellclear(avm_memcell *cell);

unsigned avm_totalactuals(void);
unsigned avm_get_envvalue(unsigned i);
void avm_dec_top(void);
void avm_push_envvalue(unsigned val);
void avm_callsaveenvironment(void);
avm_memcell *avm_getactual(unsigned i);

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg);

double const_get_num(unsigned index);
char *const_get_str(unsigned index);
char *const_get_lib(unsigned index);
function *const_get_func(unsigned index);

vmarg *create_vmarg(enum vmarg_t type, unsigned val);
void read(FILE *input);

#endif // _VM_H_
