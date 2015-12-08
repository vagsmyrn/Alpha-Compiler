#include "vm_lib_funcs.h"


void avm_calllibfunc(char *name){
	topsp = top;
	totalActuals = 0;

	if(strcmp(name, "print") == 0){
		lib_print();
	}

	if(!executionFinished)
		execute_exitfunc(NULL);
}

void lib_print(void){
	unsigned n = avm_totalactuals();
	unsigned i;

	for(i=0; i<n; i++){
		avm_tostring(avm_getactual(i));
		putchar(' ');
	}
	putchar('\n');
}

char *avm_tostring(avm_memcell *arg){

	switch(arg->type){
	case number_m:
		fprintf(stdout, "%f", arg->data.numVal);
		break;

	case string_m:
		fprintf(stdout, "%s", arg->data.strVal);
		break;

	case bool_m:
		fprintf(stdout, "%s", arg->data.boolVal==0?"FALSE":"TRUE");
		break;

	case nil_m:
		fprintf(stdout, "NIL");
		break;

	default:
		fprintf(stdout, "UNSUPPORTED");
		break;
	}

	return NULL;
}
