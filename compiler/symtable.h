#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

enum SymbolTableSpace {
	GLOBAL_SP,
	LOCAL_SP,
	FORMAL_SP,
};

enum SymbolTableType {
	GLOBAL_VAR = 0,
	LOCAL_VAR,
	FORMAL_VAR,
	USERFUNC,
	LIBFUNC,
};

enum LookupScope {
	GLOBAL_SCOPE = 0,
	LOCAL_LIB_SCOPE,
	FORMAL_SCOPE,
	ANY
};


typedef struct SymbolTableEntry SymbolTableEntry;

typedef struct Variable {
	char *name;
	unsigned int scope;
	unsigned int line;
	int offset;
	int scopeVarsCount;
	int formalVarsCount;
	int funcStart;
	struct SymbolTableEntry *members;
} Variable;

typedef struct SymbolTableEntry{
	int active;
	Variable *var;
	enum SymbolTableType type;
	enum SymbolTableSpace space;
	
	struct SymbolTableEntry *next;
} SymbolTableEntry;

typedef struct FunctionNode{
	Variable *val;
	struct FunctionNode *next;
} FunctionNode;

extern FunctionNode *functionStack;
extern int functionBetween;

SymbolTableEntry *insert(Variable *var, enum SymbolTableType type);
SymbolTableEntry *insert_member(SymbolTableEntry *parent, Variable *var);

SymbolTableEntry *lookup(int scope, char *name, enum LookupScope type);
SymbolTableEntry *lookup_member(SymbolTableEntry *parent, char *name);
SymbolTableEntry *lookup_variable(Variable *var);

Variable *var_copy(Variable *source, char *target_name);
SymbolTableEntry *st_copy(SymbolTableEntry *source, Variable *target_var);


void print_list();
void print_node(SymbolTableEntry *node);
void print_member(SymbolTableEntry *node);
char *literal_of(enum SymbolTableType type);

void push(Variable *func);
Variable *pop(void);
Variable *peek(void);

#endif // _SYMTABLE_H_
