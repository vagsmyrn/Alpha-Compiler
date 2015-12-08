#ifndef VM_LIB_FUNCS_H_
#define VM_LIB_FUNCS_H_

#include <string.h>
#include "vm_global.h"
#include "vm.h"

void avm_calllibfunc(char *name);

void lib_print(void);

char *avm_tostring(avm_memcell *arg);

#endif /* VM_LIB_FUNCS_H_ */
