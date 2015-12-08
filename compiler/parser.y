%{
	#define log(...)		{fprintf(stdout, "\t %2d: ", alpha_yylineno); fprintf(stdout, __VA_ARGS__); putchar('\n');}
	#define print_info(...)	{fprintf(stdout, "INFO %d: ", alpha_yylineno); fprintf(stdout, __VA_ARGS__); putchar('\n');}
	#define print_err(...)	{fprintf(stderr, "ERROR %d: ", alpha_yylineno); fprintf(stderr, __VA_ARGS__); fprintf(stderr,"\n");}

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <string.h>
	#include "symtable.h"
	#include "icode.h"
	#include "fcode.h"
	
	int alpha_yyerror (char* yaccProvideMessage);
	int alpha_yylex (void);
	Variable *createVar(char *name, unsigned int scope, unsigned int line);
	char *getUniqueId(void);
	char *getTempId(void);
	char *getLabelId(void);
	expr *genetate_expr_code(enum iopcode op, expr* arg1, expr* arg2);
	expr *genetate_rel_expr_code(enum iopcode op, expr* arg1, expr* arg2);
	expr *generate_label_code(void);
	expr *genetate_unary_expr_code(enum iopcode op, expr* arg1);

	expr *TRUE_EXPR, *FALSE_EXPR, *label1, *label2, *label3, *label4;
	quad *temp_quad, *temp_quad2;
	quad *last_quad1, *last_quad2;
	loop *temp_loop;

	int scope = 0;
	int loop_flag = 0;
	int uniqueCounter = 0; // functions
	int uniqueCounter1 = 1; //  temp vars
	int uniqueCounter2 = 1; //  labels
	char *str;
		
	SymbolTableEntry *st_res, *st_res2;
	expr *ex1, *ex2;

	extern quad* head_q;
	extern int alpha_yylineno;
	extern char* alpha_yytext;
	extern FILE* alpha_yyin;
%}

%name-prefix="alpha_yy"
%output="parser.c"
%expect 1

%start program

%type <value> indexed indexedelems indexedelem lvalue  member call funcdef const term expr assignexpr primary stmt block program returnstmt elist elistobj exprs objectdef ifstmt ifprefix elseprefix whilestmt
%token <stringValue> ID STRING
%token <intValue> INTEGER
%token <floatValue> REAL
%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE LOCAL TRUE FALSE NIL LEFT_BRACE RIGHT_BRACE COLON DOUBLE_COLON PERIOD

%initial-action
{
TRUE_EXPR = create_expr(CONSTBOOL_E, NULL);
TRUE_EXPR->boolConst = 1;

FALSE_EXPR = create_expr(CONSTBOOL_E, NULL);
FALSE_EXPR->boolConst = 0;

}

%union {
	char* stringValue;
	int	intValue;
	float floatValue;
	int opcode;
	
	struct expr *value;
}

%left		LOWEST_PREC
%left		SEMICOLON
%left 		ASSIGN
%left		COMMA
%left		OR
%left		AND
%nonassoc	EQUAL DIFF
%nonassoc	HIGHER HIGHER_EQ LOWER LOWER_EQ
%left 		PLUS MINUS
%left		MIDDLE_PREC
%left		STAR DIVIDE MODULE
%right		NOT PLUSPLUS MINUSMINUS UMINUS
%left		DOUBLE_PERIOD PERIOD
%left		LEFT_BRACKET  RIGHT_BRACKET
%left		LEFT_PAR RIGHT_PAR
%left		HIGHEST_PREC

%destructor { free($$); } ID

%%

program: 	
		stmt program 				{ log("stmt program -> program");}
	|								{ log("empty -> program"); $$ = NULL; }
	;

stmt:		
		expr SEMICOLON			{ $$ = $1; }
	|	ifstmt					{ log("ifstmt -> stmt");}
	|	whilestmt				{ log("whilestmt -> stmt");}
	|	forstmt					{ log("forstmt; -> stmt");}
	|	returnstmt				{ log("returnstmt; -> stmt");}
	|	BREAK SEMICOLON			{
						log("break; -> stmt");
						if(loop_flag==0){
							print_err("BREAK without a loop.");
							exit(-1);
						}
						temp_quad = create_quad(JUMP, NULL, NULL, peek_loop()->end_label, -1, alpha_yylineno);
						insert_quad(temp_quad);
						$$ = create_expr(NIL_E, NULL);
						$$->quad = temp_quad;
					}
	|	CONTINUE SEMICOLON 			{
						log("continue; -> stmt");
						if(loop_flag==0){
							print_err("CONTINUE without a loop.");
							exit(-1);
						}
						temp_quad = create_quad(JUMP, NULL, NULL, peek_loop()->start_label, -1, alpha_yylineno);
						insert_quad(temp_quad);
						$$ = create_expr(NIL_E, NULL);
						$$->quad = temp_quad;
					}
	|	block					{ log("block -> stmt"); $$ = $1; }
	|	funcdef					{ log("funcdef -> stmt"); $$ = $1; }
	|	SEMICOLON				{ log(";->stmt"); $$ = create_expr(NIL_E, NULL); }
	;



expr:	
		assignexpr				{ $$ = $1; }
	|	expr PLUS expr			{ $$ = genetate_expr_code(ADD, $1, $3); }
	|	expr MINUS expr			{ $$ = genetate_expr_code(SUB, $1, $3); }
	|	expr STAR expr			{ $$ = genetate_expr_code(MUL, $1, $3); }
	|	expr DIVIDE expr		{ $$ = genetate_expr_code(DIV, $1, $3); }
	|	expr MODULE expr		{ $$ = genetate_expr_code(MOD, $1, $3); }
	|	expr HIGHER expr		{ $$ = genetate_rel_expr_code(IF_GREATER, $1, $3); }
	|	expr HIGHER_EQ expr		{ $$ = genetate_rel_expr_code(IF_GREATER_EQ, $1, $3); }
	|	expr LOWER expr		 	{ $$ = genetate_rel_expr_code(IF_LESS, $1, $3); }
	|	expr LOWER_EQ expr		{ $$ = genetate_rel_expr_code(IF_LESS_EQ, $1, $3); }
	|	expr EQUAL expr			{ $$ = genetate_rel_expr_code(IF_EQ, $1, $3); }
	|	expr DIFF expr			{ $$ = genetate_rel_expr_code(IF_NOTEQ, $1, $3); }
	|	expr AND expr			{ $$ = genetate_expr_code(AND_Q, $1, $3); }
	|	expr OR expr			{ $$ = genetate_expr_code(OR_Q, $1, $3); }
	|	term 					{ $$ = $1; } 
	;


term:
		primary						{ log("primary -> term"); $$ = $1; }
	|	LEFT_PAR expr RIGHT_PAR		{ log("(expr) -> term"); $$ = $2; }
	|	MINUS expr 					{ 
			log("-expr -> term"); $$ = $2;
		
			expr *ex = genetate_unary_expr_code(UMINUS_Q, $2);
			$$ = ex; 
			//$$ = genetate_expr_code(UMINUS_Q, $2, NULL);
		} %prec UMINUS
	|	NOT expr					{ 
			log("not expr -> term"); 
			
			expr *ex = genetate_unary_expr_code(NOT_Q, $2);
			$$ = ex; 
		}
	|	PLUSPLUS lvalue				{
			log("++lvalue -> term");
			
			if($2->sym->type == USERFUNC){
				print_err("lvalue cannot be a function");
				exit(-1);
			}
			expr *ex = create_expr(CONSTNUM_E, NULL);
			ex->numConst = 1;
			ex = genetate_expr_code(ADD, $2, ex);
			
			quad *temp_quad = create_quad(ASSIGN_Q, ex, NULL, $2, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			$$ = $2;
			$$->quad = temp_quad;
			}
	|	lvalue PLUSPLUS				{
			log("lvalue++ -> term");
			
			if($1->sym->type == USERFUNC){
				print_err("lvalue cannot be a function");
				exit(-1);
			}
			Variable *temp_lvalue_var = var_copy($1->sym->var, getTempId());
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
			
			ex1 = create_expr(VAR_E, temp_lvalue);

			temp_quad = create_quad(ASSIGN_Q, $1, NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			$$ = ex1;
			$$->quad = temp_quad;
			
			expr *ex = create_expr(CONSTNUM_E, NULL);
			ex->numConst = 1;
			
			temp_quad = create_quad(ADD, $1, ex, $1, -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
	|	MINUSMINUS lvalue 			{
			log("--lvalue -> term");
			
			if($2->sym->type == USERFUNC){
				print_err("lvalue cannot be a function");
				exit(-1);
			}
			expr *ex = create_expr(CONSTNUM_E, NULL);
			ex->numConst = 1;
			ex = genetate_expr_code(SUB, $2, ex);
			
			quad *temp_quad = create_quad(ASSIGN_Q, ex, NULL, $2, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			$$ = $2;
			$$->quad = temp_quad;
		}
		
	|	lvalue MINUSMINUS 			{
			log("lvalue-- -> term");
			
			if($1->sym->type == USERFUNC){
				print_err("lvalue cannot be a function");
				exit(-1);
			}
			Variable *temp_lvalue_var = var_copy($1->sym->var, getTempId());
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
			
			ex1 = create_expr(VAR_E, temp_lvalue);

			temp_quad = create_quad(ASSIGN_Q, $1, NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			$$ = ex1;
			$$->quad = temp_quad;
			
			expr *ex = create_expr(CONSTNUM_E, NULL);
			ex->numConst = 1;
			
			temp_quad = create_quad(SUB, $1, ex, $1, -1, alpha_yylineno);
			insert_quad(temp_quad);			
		}
	;

assignexpr:		
		lvalue ASSIGN expr			{
				log("lvalue ASSIGN expr -> assignexpr");
				if($1 == NULL) {
					print_err("Ignoring NULL lvalue");
				} else if($1->sym->type == USERFUNC){
					print_err("Cannot assign to function %s %s. scope: %d, line: %d", literal_of($1->sym->type), $1->sym->var->name, $1->sym->var->scope, $1->sym->var->line);
				}else if($1->type == TABLEITEM_E) {
					temp_quad = create_quad(TABLESETELEM, $3, $3->index, $1, -1, alpha_yylineno);
					insert_quad(temp_quad);
					$$ = $1;
					$$->quad = temp_quad;
				}else{
					temp_quad = create_quad(ASSIGN_Q, $3, NULL, $1, -1, alpha_yylineno);
					insert_quad(temp_quad);
					$$ = $1;
					//$$ = create_expr(ASSIGNEXPR_E, $1->sym);
					$$->quad = temp_quad;
				}
			}

	;

primary:
		lvalue					{ log("lvalue -> primary"); $$ = $1; }
	|	call					{ log("call -> primary"); $$ = $1; }
	|	objectdef				{ log("objectdef -> primary"); $$ = $1; }
	|	const					{ log("const -> primary"); $$ = $1; }
	|	LEFT_PAR funcdef RIGHT_PAR		{ log("( funcdef ) -> primary"); $$ = $2; }
	;
		
lvalue:
		ID {
			log("ID:%s -> lvalue",$1);
			
			st_res = lookup(scope, $1, ANY);
			if(st_res == NULL){
				print_info("INSERT in ST variable (ID:%s) scope: %d", $1, scope);
				Variable *var = createVar($1, scope, alpha_yylineno);
				$$ = create_expr(VAR_E, insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR));
			}else{
				if(st_res->type == USERFUNC){
					$$ = create_expr(PROGRAMFUNC_E, st_res);
				}else if(st_res->type == LIBFUNC ){
					$$ = create_expr(LIBRARYFUNC_E, st_res);
				}else if(st_res->var->scope != 0 && st_res->var->scope != scope && functionBetween){
					print_err("Cannot access %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, scope, st_res->var->line);
				}else{
					$$ = create_expr(VAR_E, st_res);
				}
			}
		}
	|	LOCAL ID {
			log("LOCAL ID:%s -> lvalue",$2);
			st_res = lookup(scope, $2, LOCAL_LIB_SCOPE);
			if(st_res==NULL){
				print_info("INSERT in ST local variable (LOCAL ID) scope: %d, line: %d", scope, alpha_yylineno);
				Variable *var = createVar($2, scope, alpha_yylineno);
				if(scope == 0){
					$$ = create_expr(VAR_E, insert(var, GLOBAL_VAR));
				} else {
					$$ = create_expr(VAR_E, insert(var, LOCAL_VAR));
				}
			}else{
				if(st_res->type == USERFUNC ||	(st_res->type == LIBFUNC && scope == 0)){
					$$ = create_expr(VAR_E, st_res);
				}else if(st_res->type == LIBFUNC ){
					print_err("Collision with %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, scope, st_res->var->line);
					exit(0);
				}else{
					$$ = create_expr(VAR_E, st_res);
				}
			}
		}
	|	DOUBLE_COLON ID {
			log("::ID:%s -> lvalue",$2);
			st_res = lookup(scope, $2, GLOBAL_SCOPE);
			if(st_res==NULL){
				print_err("Cannot find global symbol %s", $2);
				exit(0);
			}else{
				$$ = create_expr(VAR_E, st_res);
			}
		}
	|	member {log("member -> lvalue"); $$ = $1; }

	;

member:		
		lvalue PERIOD ID {
			log("lvalue.ID: %s-> member", $3);
			st_res = lookup_member($1->sym, $3);
			if(st_res == NULL){
				Variable *var = createVar($3, $1->sym->var->scope, alpha_yylineno);
				insert_member($1->sym, var);
				print_info("INSERT in ST member variable (parent: %s, %s, %d) scope: %d, line: %d", $1->sym->var->name, literal_of($1->sym->type), $1->sym->var->line, scope, alpha_yylineno);
			}
			Variable *temp_lvalue_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
		
			ex1 = create_expr(TABLEITEM_E, temp_lvalue);
			ex1->index = create_expr(CONSTSTRING_E, NULL);
			ex1->index->strConst = strdup($3);
			$$ = ex1;
			
		
			temp_quad = create_quad(TABLEGETELEM, $1, NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			$$->quad = temp_quad;
		}
	|	call PERIOD ID {
			log("call.ID:%s -> member",$3);
			st_res = lookup_member($1->sym, $3);

			Variable *temp_lvalue_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
		
			ex1 = create_expr(TABLEITEM_E, temp_lvalue);
			ex1->index = create_expr(CONSTSTRING_E, NULL);
			ex1->index->strConst = strdup($3);
			$$ = ex1;
			
		
			temp_quad = create_quad(TABLEGETELEM, $1, NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			$$->quad = temp_quad;			
		}
	|	lvalue LEFT_BRACKET expr RIGHT_BRACKET {
			log("lvalue [ expr ] -> member");
			
			Variable *temp_lvalue_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
		
			ex1 = create_expr(TABLEITEM_E, temp_lvalue);
			ex1->index = $3;
			$$ = ex1;
		
			temp_quad = create_quad(TABLEGETELEM, $1, NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			$$->quad = temp_quad;
			
		}
	|	call LEFT_BRACKET expr RIGHT_BRACKET {
			log("call [ expr] -> member");
			
			Variable *temp_lvalue_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
		
			ex1 = create_expr(TABLEITEM_E, temp_lvalue);
			ex1->index = $3;
			$$ = ex1;
		
			temp_quad = create_quad(TABLEGETELEM, $1, NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			$$->quad = temp_quad;
		}
	;

call:
		call LEFT_PAR calllist RIGHT_PAR	{
			log("call ( elist ) -> call");
			temp_quad = create_quad(CALL, NULL, NULL, $1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			Variable *var = createVar(getTempId(), scope, alpha_yylineno);
			st_res = insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);

			ex1 = create_expr(VAR_E, st_res);
	
			ex1->quad = create_quad(GETRETVAL, NULL, NULL, ex1, -1, alpha_yylineno);
			insert_quad(ex1->quad);
			
			$$ = ex1;
		}
	|	lvalue callsuffix		{
			log("lvalue callsufix -> call");
			temp_quad = create_quad(CALL, NULL, NULL, $1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			Variable *var = createVar(getTempId(), scope, alpha_yylineno);
			st_res = insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);

			ex1 = create_expr(VAR_E, st_res);
	
			ex1->quad = create_quad(GETRETVAL, NULL, NULL, ex1, -1, alpha_yylineno);
			insert_quad(ex1->quad);
			
			$$ = ex1;			
		}
	|	LEFT_PAR funcdef RIGHT_PAR LEFT_PAR calllist RIGHT_PAR	{ 
			log("( funcdef ) ( elist ) -> call");
			temp_quad = create_quad(CALL, NULL, NULL, $2, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			Variable *var = createVar(getTempId(), scope, alpha_yylineno);
			st_res = insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);

			ex1 = create_expr(VAR_E, st_res);
	
			ex1->quad = create_quad(GETRETVAL, NULL, NULL, ex1, -1, alpha_yylineno);
			insert_quad(ex1->quad);
			
			$$ = ex1;			
		}
	;


callsuffix:
		normcall	{ log("normcall -> callsuffix"); }
	|	methodcall	{ log("methodcall -> callsuffix"); }
	;

normcall:
		LEFT_PAR calllist RIGHT_PAR	{ log("( elist ) -> normcall");}
	;	

methodcall:	
		DOUBLE_PERIOD ID LEFT_PAR calllist RIGHT_PAR { log(".. ID: %s ( elist )  -> op",$2);}
	; 	// equivalent to lvalue.id(lvalue,elist)

calllist:
		expr		{ 
			log("expr -> calllist");
			temp_quad = create_quad(PARAM, NULL, NULL, $1, -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
	|	expr exprs2	{
			log("expr exprs2 -> calllist");
			temp_quad = create_quad(PARAM, NULL, NULL, $1, -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
	|	/*empty*/
	;
	
exprs2:
		COMMA calllist	{ log(", calllist -> exprs2");}
	;
	
elist:
		expr		{ log("expr -> elist");}
	|	expr exprs	{ log("expr exprs -> elist"); $1->next = $2; $$ = $1; }
	|	/*empty*/	{ $$ = NULL; }
	;

elistobj:
  		expr		{ log("expr -> elistobj"); $$ = $1; }
	|	expr exprs	{ log("expr exprs -> elistobj"); $1->next = $2; $$ = $1; }
	;

exprs:
		COMMA elist	{ log(", elist -> exprs"); $$ = $2; }
	;

objectdef:
		LEFT_BRACKET  elistobj RIGHT_BRACKET	{ 
			log("[ elistobj ] -> objectdef");
			
			Variable *temp_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_table = insert(temp_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
			
			expr *table_expr = create_expr(NEWTABLE_E, temp_table);
			
			temp_quad = create_quad(TABLECREATE, NULL, NULL, table_expr, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			$$ = table_expr;
			$$->quad = temp_quad;
			
			expr *temp;
			int i=0;
			for(temp = $2; temp!=NULL; temp = temp->next){
				expr *ex = create_expr(CONSTNUM_E, NULL);
				ex->numConst = i++;
				
				temp_quad = create_quad(TABLESETELEM, temp, ex, table_expr, -1, alpha_yylineno);
				insert_quad(temp_quad);	
			}
		}
	|	LEFT_BRACKET indexed RIGHT_BRACKET		{
			log("[ indexed ] -> objectdef");
			
			Variable *temp_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_table = insert(temp_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
			
			expr *table_expr = create_expr(NEWTABLE_E, temp_table);
			
			temp_quad = create_quad(TABLECREATE, NULL, NULL, table_expr, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			$$ = table_expr;
			$$->quad = temp_quad;
			
			expr *temp;

			for(temp = $2; temp!=NULL; temp = temp->next){
				temp_quad = create_quad(TABLESETELEM, temp, temp->index, table_expr, -1, alpha_yylineno);
				insert_quad(temp_quad);	
			}
		}
	;

indexed:
		indexedelem	{ log("indexedelem -> indexed"); $$ = $1; }
	|	indexedelem indexedelems	{ log("indexedelem indexedelems -> indexed"); $1->next = $2; $$ = $1; }
	|	/*empty*/					{ $$ = NULL; }
	;

indexedelems:
		COMMA indexed	{ log(", indexed -> indexedelems"); $$ = $2; }
	;

indexedelem:
		LEFT_BRACE expr COLON expr RIGHT_BRACE	{ 
			log("{ expr : expr } -> indexedelem");
			$4->index = $2;
			$$ = $4;
		}
	;

block:
		LEFT_BRACE { scope++; } program RIGHT_BRACE	{ log("{ program } -> block"); $$ = $3; scope--;}
	;

block2:		
		LEFT_BRACE program RIGHT_BRACE	{ log("{ program } -> block2"); }
	;

funcdef:
		FUNCTION {
			log("function (idlist) -> lvalue");
			str = getUniqueId();
			print_info("INSERT in ST anonymous function %s. scope: %d, line: %d", str, scope, alpha_yylineno);
			Variable *var = createVar(str, scope, alpha_yylineno);
			st_res = insert(var, USERFUNC);
			push(var);
			ex1 = create_expr(PROGRAMFUNC_E, st_res);
			temp_quad = create_quad(FUNCSTART, NULL, NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
		} 
		LEFT_PAR {scope++;}
		idlist RIGHT_PAR block2 { 
			st_res = lookup_variable(pop());
			ex1 = create_expr(PROGRAMFUNC_E, st_res);
			scope--; 
			$$ = ex1;
			temp_quad = create_quad(FUNCEND, NULL, NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
	|	FUNCTION
		ID {
			log("funtion id (idlist) -> lvalue");
			st_res = lookup(scope, $2, LOCAL_LIB_SCOPE);
			if(st_res==NULL || (st_res->var->scope != scope && st_res->type == USERFUNC)){
				print_info("INSERT in ST user function %s. scope: %d, line: %d", $2, scope, alpha_yylineno);
				Variable *var = createVar($2, scope, alpha_yylineno);
				st_res = insert(var, USERFUNC);
				push(var);
				ex1 = create_expr(PROGRAMFUNC_E, st_res);
				temp_quad = create_quad(FUNCSTART, NULL, NULL, ex1, -1, alpha_yylineno);
				insert_quad(temp_quad);
			}else if( st_res != NULL) {
    			print_err("Collision with %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, st_res->var->scope, st_res->var->line);
			}
		}
		LEFT_PAR { scope++; } 
		idlist RIGHT_PAR block2 { 
				st_res = lookup_variable(pop());
				ex1 = create_expr(PROGRAMFUNC_E, st_res);
				scope--; 
				$$ = ex1;
				temp_quad = create_quad(FUNCEND, NULL, NULL, ex1, -1, alpha_yylineno);
				insert_quad(temp_quad);
			}
	;

const:
		INTEGER	{
			log("integer:%d -> const",$1);
			ex1 = create_expr(CONSTNUM_E, NULL);
			ex1->numConst = $1;
			$$ = ex1;
		}
	|	REAL	{
			log("real:%f -> const",$1);
			ex1 = create_expr(CONSTNUM_E, NULL);
			ex1->numConst = $1;
			$$ = ex1;
		}
	|	STRING	{
			log("string:%s -> const",$1);
			ex1 = create_expr(CONSTSTRING_E, NULL);
			ex1->strConst = $1;
			$$ = ex1;
		}
	|	NIL		{
			log("nil -> const");
			ex1 = create_expr(NIL_E, NULL);
			$$ = ex1;
		}
	|	TRUE	{
			log("true -> const");
			ex1 = create_expr(CONSTBOOL_E, NULL);
			ex1->boolConst = 1;
			$$ = ex1;
		}
	|	FALSE	{
			log("false -> const");
			ex1 = create_expr(CONSTBOOL_E, NULL);
			ex1->boolConst = 0;
			$$ = ex1;
		}
	;

idlist:
		ID	{
			log("ID  -> idlist");
			st_res = lookup(scope, $1, FORMAL_SCOPE);
			if(st_res==NULL){
				Variable *arg = createVar($1, scope, alpha_yylineno);
				insert(arg, FORMAL_VAR);
				print_info("INSERT %s %s. scope: %d, line: %d", literal_of(FORMAL_VAR), arg->name, scope, arg->line);
			}else {
				print_err("Collision with %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, scope, st_res->var->line);
			}            
		}
	|	ID idlists	{
			st_res = lookup(scope, $1, FORMAL_SCOPE);
			if(st_res==NULL){
            	Variable *arg = createVar($1, scope, alpha_yylineno);
				insert(arg, FORMAL_VAR);
            	print_info("INSERT %s %s. scope: %d, line: %d", literal_of(FORMAL_VAR), arg->name, scope, arg->line);
			}else{
            	print_err("Collision with %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, scope, st_res->var->line);
			}										
		}
	|	/*empty*/
	;

idlists:	COMMA idlist	{ log(", idlist -> idlists");}
	;

ifstmt:
		ifprefix stmt {
			label1 = generate_label_code();
			temp_quad = create_quad(IF_NOTEQ, $1, TRUE_EXPR, label1, -1, alpha_yylineno);
			
			insert_after_quad($1->quad, temp_quad);
			insert_quad(label1->quad);
			
			$$ = create_expr(NIL_E, NULL);
			$$->quad = label1->quad;
		}
	|	ifprefix stmt elseprefix stmt {
			label1 = generate_label_code();
			
			temp_quad = create_quad(IF_NOTEQ, $1, TRUE_EXPR, label1, -1, alpha_yylineno);
			insert_after_quad($1->quad, temp_quad);
			
			insert_after_quad($3->quad, label1->quad);

			label2 = generate_label_code();
			insert_quad(label2->quad);
			
			temp_quad = create_quad(JUMP, NULL, NULL, label2, -1, alpha_yylineno);
			
			insert_before_quad(label1->quad, temp_quad);
				
			$$ = create_expr(NIL_E, NULL);
			$$->quad = label2->quad;	
		}
	;
	
ifprefix:
		IF LEFT_PAR expr RIGHT_PAR { 
			$$ = $3;
			if($3->quad == NULL){
				$$->quad = get_last_quad();
				//print_info("=============> %p", $$->quad);
				//print_quad($$->quad);
			}
			
		}
	;
	
elseprefix:
		ELSE {
			$$ = create_expr(NIL_E, NULL);
			$$->quad = get_last_quad();
		}
	;

whilestmt:
		WHILE LEFT_PAR {
				label1 = generate_label_code(); // while start
				label2 = generate_label_code(); // stmt end
				push_loop(get_last_quad(), label1, label2);
		} expr RIGHT_PAR { loop_flag++; }
		stmt{
				loop_flag--;
				log("while ( expr ) stmt -> whilestmt");
				temp_loop = pop_loop();
				
				label1 = temp_loop->start_label; // while start
				label2 = temp_loop->end_label; // stmt end

				temp_quad = create_quad(IF_NOTEQ, $4, TRUE_EXPR, label2, -1, alpha_yylineno);
				
				if($4->quad != NULL){
					insert_after_quad($4->quad, temp_quad);
				}else{
					insert_after_quad(temp_loop->previous_quad, temp_quad);
				}

				insert_after_quad(temp_loop->previous_quad, label1->quad);
				
				temp_quad = create_quad(JUMP, NULL, NULL, label1, -1, alpha_yylineno);
				insert_after_quad(get_last_quad(), temp_quad);
				insert_after_quad(get_last_quad(), label2->quad);
				
				free(temp_loop);
				
				$$ = label2;
				
  		}
	;

forstmt:
		FOR LEFT_PAR elist SEMICOLON {
		
				label1 = generate_label_code(); // while start
				label2 = generate_label_code(); // stmt end
				push_loop(get_last_quad(), label1, label2);
				
				label4 = generate_label_code();
				
				label3 = generate_label_code();
				insert_quad(label3->quad);
		} expr SEMICOLON {
				temp_quad = create_quad(IF_NOTEQ, $6, TRUE_EXPR, peek_loop()->end_label, -1, alpha_yylineno);
				insert_quad(temp_quad);
				temp_quad = create_quad(IF_EQ, $6, TRUE_EXPR, label4, -1, alpha_yylineno);
				insert_quad(temp_quad);
				
				insert_quad(peek_loop()->start_label->quad);
		} elist RIGHT_PAR {
				temp_quad = create_quad(JUMP, NULL, NULL, label3, -1, alpha_yylineno);
				insert_quad(temp_quad);
		
				insert_quad(label4->quad);				
		loop_flag++;}
		stmt{ 
			loop_flag--; log("for ( elist ; expr ; elist ) stmt -> forstmt");

			temp_quad = create_quad(JUMP, NULL, NULL, peek_loop()->start_label, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			insert_quad(peek_loop()->end_label->quad);
			pop_loop();
		}
	;

returnstmt:
		RETURN SEMICOLON	{
  			log("return ; -> returnstmt");
			if(peek() == NULL){
				print_err("RETURN without a function.");
  			}
			temp_quad = create_quad(RET, NULL, NULL, NULL, -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
	|	RETURN expr SEMICOLON	{
  			log("return expr ; -> return stmt");
			if(peek() == NULL){
				print_err("RETURN without a function.");
  			}
			temp_quad = create_quad(RET, NULL, NULL, $2, -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
	;

%%

int alpha_yyerror (char* yaccProvidedMessage){

	fprintf(stderr,"%s: at line %d, before token: %s|\nINPUT NOT VALID\n\nPANAGIA\n\n",yaccProvidedMessage,alpha_yylineno,alpha_yytext);
	
	return 0;
}

//***************************************************************

Variable *createVar(char *name, unsigned int scope, unsigned int line){
	Variable *res;
	
	res = malloc(sizeof(Variable));
	res->name = strdup(name);
	res->scope = scope;
	res->line = line;
	res->offset = 0;
	res->scopeVarsCount = 0;
	res->formalVarsCount = 0;
	res->members = NULL;
	

	return res;
}

char *getUniqueId(void){
	char *res;
	char prefix[10];
	
	sprintf(prefix, "$f%d", uniqueCounter++);
	res = strdup(prefix);
	
	return res;
}

char *getTempId(void){
	char *res;
	char prefix[10];
	
	sprintf(prefix, "_t%d", uniqueCounter1++);
	res = strdup(prefix);
	
	return res;
}

char *getLabelId(void){
	char *res;
	char prefix[10];
	
	sprintf(prefix, "_LABEL_%d", uniqueCounter2++);
	res = strdup(prefix);
	
	return res;
}


expr *genetate_expr_code(enum iopcode op, expr* arg1, expr* arg2){
	char *temp_name = getTempId();
	SymbolTableEntry *st;
	expr *exp1;
	Variable *var;
	
	var = createVar(temp_name, scope, alpha_yylineno);
	st = insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);

	exp1 = create_expr(op, st);
	exp1->type = VAR_E; // arg1->type;
	
	exp1->quad = create_quad(op, arg1, arg2, exp1, -1, alpha_yylineno);
	insert_quad(exp1->quad);

	return exp1;
}

expr *genetate_rel_expr_code(enum iopcode op, expr* arg1, expr* arg2){
	char *temp_name = getTempId();
	SymbolTableEntry *st;
	expr *exp1, *l1, *l2;
	Variable *var;
	quad *jump_quad;
	
	var = createVar(temp_name, scope, alpha_yylineno);
	st = insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);

	exp1 = create_expr(op, st);
	exp1->type = VAR_E; // arg1->type;
	
	l1 = generate_label_code();
	l2 = generate_label_code();
	
	exp1->quad = create_quad(op, arg1, arg2, l1, l1->labelNo, alpha_yylineno);
	insert_quad(exp1->quad);
	
	temp_quad = create_quad(ASSIGN_Q, FALSE_EXPR, NULL, exp1, -1, alpha_yylineno);
	insert_quad(temp_quad);
	
	jump_quad = create_quad(JUMP, NULL, NULL, l2, l2->labelNo, alpha_yylineno);
	insert_quad(jump_quad);
	
	insert_quad(l1->quad);
	
	temp_quad = create_quad(ASSIGN_Q, TRUE_EXPR, NULL, exp1, -1, alpha_yylineno);
	insert_quad(temp_quad);

	insert_quad(l2->quad);
	
	exp1->quad = l2->quad;
	return exp1;
}

expr *genetate_unary_expr_code(enum iopcode op, expr* arg1){
	char *temp_name = getTempId();
	SymbolTableEntry *st;
	expr *exp1;
	Variable *var;
	
	var = createVar(temp_name, scope, alpha_yylineno);
	st = insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);

	exp1 = create_expr(op, st);
	exp1->type = VAR_E; // arg1->type;
	
	exp1->quad = create_quad(op, arg1, NULL, exp1, -1, alpha_yylineno);
	insert_quad(exp1->quad);

	return exp1;
}


expr *generate_label_code(void){
	expr *label;
	
	label = create_expr(LABEL_E, NULL);
	label->labelNo = uniqueCounter2;
	label->quad = create_quad(LABEL, NULL, NULL, NULL, uniqueCounter2, alpha_yylineno);
	label->strConst = getLabelId();
	
	return label;
}


int main(int argc,char** argv){
	icode_stream = stderr;
	FILE *bin_output;

	scope = 0;
	
	if(argc ==3){
		icode_stream = fopen(argv[2],"w");
	}else{
		icode_stream = stderr;
	}
	
	if (argv){
		if (!(alpha_yyin = fopen(argv[1],"r"))){
			fprintf(stderr,"cannot read file\n");
			return 1;
		}
	}
	else{
		alpha_yyin=stdin;
	}
	
	insert(createVar("print", 0, 0), LIBFUNC);
	insert(createVar("input", 0, 0), LIBFUNC);
	insert(createVar("objectmemberkeys", 0, 0), LIBFUNC);
	insert(createVar("objecttotalmembers", 0, 0), LIBFUNC);
	insert(createVar("objectcopy", 0, 0), LIBFUNC);
	insert(createVar("totalarguments", 0, 0), LIBFUNC);
	insert(createVar("argument", 0, 0), LIBFUNC);
	insert(createVar("typeof", 0, 0), LIBFUNC);
	insert(createVar("strtonum", 0, 0), LIBFUNC);
	insert(createVar("sqrt", 0, 0), LIBFUNC);
	insert(createVar("cos", 0, 0), LIBFUNC);
	insert(createVar("sin", 0, 0), LIBFUNC);

	alpha_yyparse();
	print_list();
	print_icode();

	generate_fcode(head_q);
	fprintf(stderr, "======= const_num =======\n");
	print_const_num(stderr);
	fprintf(stderr, "======= const_func =======\n");
	print_const_func(stderr);
	fprintf(stderr, "======= fcode =======\n");
	print_fcode(stderr);
	fprintf(stderr, "\n");
	
	bin_output = fopen("test.abc", "wb");
	print_binary(bin_output);
	fclose(bin_output);

	return 0;
}


	

