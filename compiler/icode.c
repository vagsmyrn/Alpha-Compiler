#include <stdio.h>
#include <stdlib.h>

#include "icode.h"

quad* head_q = NULL;
quad* head_suffix = NULL;
loop *head_l = NULL;

FILE *icode_stream;

quad *push_suffix(quad *new_node){
	quad *temp;
	
	if(head_suffix==NULL){
		new_node->next = NULL;
		head_suffix = new_node;
		return head_suffix;
	}
	
	for(temp=head_suffix; temp!=NULL; temp=temp->next){
		if(temp->next==NULL){
			new_node->next = NULL;			
			temp->next = new_node;
			
			return head_suffix;
		}
	}
	return head_suffix;
}

void flush_suffix(void){
	quad *temp;
	
	if(head_q==NULL){
		head_q = head_suffix;
		head_suffix = NULL;
	}
	
	for(temp=head_q; temp!=NULL; temp=temp->next){
		if(temp->next==NULL){
			temp->next = head_suffix;
			head_suffix = NULL;
		}
	}
}


void push_loop(quad *previous_quad, expr *start_label, expr *end_label){
	loop *new_node;
	
	new_node = calloc(1, sizeof(loop));
	new_node->previous_quad = previous_quad;
	new_node->start_label = start_label;
	new_node->end_label = end_label;
	
	new_node->next = head_l;
	head_l = new_node;
}

loop *pop_loop(void){
	loop *temp;

	if(head_l == NULL){
		return NULL;
	}
	
	temp = head_l;
	head_l = head_l->next;
	
	return temp;
}

loop *peek_loop(void){
	return head_l;
}

quad *insert_quad(quad *new_node){
	quad *temp;
	
	if(head_q==NULL){
		new_node->next = NULL;
		head_q = new_node;
		return head_q;
	}
	
	for(temp=head_q; temp!=NULL; temp=temp->next){
		if(temp->next==NULL){
			new_node->next = NULL;			
			temp->next = new_node;
			
			return head_q;
		}
	}
	return head_q;
}

quad *insert_after_quad(quad *target, quad *new_node){
	quad *temp;


	if(target == NULL){
		new_node->next = head_q;
		head_q = new_node;
		
		return head_q;
//		return insert_quad(new_node);
	}
	
	for(temp=head_q; temp!=NULL; temp=temp->next){
		if(temp == target){
			new_node->next = temp->next;			
			temp->next = new_node;
			
			return head_q;
		}
	}
	return head_q;
}

quad *insert_before_quad(quad *target, quad *new_node){
	quad *temp;
	
	if(head_q == target || target == NULL){
		new_node->next = head_q;
		head_q = new_node;
		
		return head_q;
	}
	
	for(temp=head_q; temp!=NULL; temp=temp->next){
		if(temp->next == target){
			new_node->next = temp->next;			
			temp->next = new_node;
			
			return head_q;
		}
	}
	return head_q;
}

quad *get_last_quad(void){
	quad *temp;
	
	for(temp=head_q; temp!=NULL; temp=temp->next){
		if(temp->next == NULL){
			return temp;
		}
	}
	return NULL;

}

quad *create_quad(enum iopcode op, expr* arg1, expr* arg2, expr* result, int label, int line){
	quad *new_node;
;
	new_node = calloc(1, sizeof(quad));
	
	new_node->op = op;
	new_node->arg1 = arg1;
	new_node->arg2 = arg2;
	new_node->result = result;
	new_node->label = label;
	new_node->line = line;
	
	return new_node;
}

expr *create_expr(enum expr_t type, SymbolTableEntry *sym){
	expr *new_node;
	
	new_node = calloc(1, sizeof(expr));
	
	new_node->type = type;
	new_node->sym = sym;
	
	return new_node;
}

void print_icode(void){
	quad *temp;
	
	fprintf(stderr, "\n======== icode ===========\n");
	for(temp = head_q; temp != NULL; temp = temp->next){
		print_quad(temp);
	}
}

void print_quad(quad *quad){
	fprintf(icode_stream, "%2d: %-12s ", quad->line, literal_of_op(quad->op));
	if(quad->op == LABEL){
		fprintf(icode_stream, "LABEL_%d\n", quad->label);	
		return;
	}
	if(quad->op == FUNCSTART || quad->op == FUNCEND){
		fprintf(icode_stream, "%10s\n", quad->result->sym->var->name);	
		return;
	}
	
	if(quad->op == TABLEGETELEM){
		print_expr(quad->arg1);
		print_expr(quad->result->index);
		print_expr(quad->result);
		fprintf(icode_stream, "\n");
		return;
	}
	
	print_expr(quad->arg1);
	print_expr(quad->arg2);
	print_expr(quad->result);
	
	fprintf(icode_stream, "\n");
}

void print_expr(expr *quad){
	if(quad != NULL){
// 		fprintf(icode_stream, "[");
// 		fprintf(icode_stream, "%s ", literal_of_expr(quad->type));
		if(quad->type == VAR_E || quad->type == ARITHEXPR_E || quad->type == PROGRAMFUNC_E 
			|| quad->type == LIBRARYFUNC_E || quad->type == TABLEITEM_E 
			|| quad->type == NEWTABLE_E){
			fprintf(icode_stream, "%10s ", quad->sym->var->name);
		}else if(quad->type == CONSTNUM_E){
			fprintf(icode_stream, "%10.1f ", quad->numConst);
		}else if(quad->type == CONSTBOOL_E){
			fprintf(icode_stream, "%10s ", (quad->boolConst==0)?("FALSE"):("TRUE"));
		}else if(quad->type == CONSTSTRING_E){
			fprintf(icode_stream, "%10s ", quad->strConst);
		}else if(quad->type == LABEL_E){
			fprintf(icode_stream, "%10s ", quad->strConst);
		}else{
			fprintf(icode_stream, "XXX ");
		}
// 		fprintf(icode_stream, "] ");
	}else{
			fprintf(icode_stream, "%10s ", "-");
	}
	
}
char *literal_of_expr(enum expr_t type){
	char *ar[] = {
		"VAR_E",
		"TABLEITEM_E",

		"PROGRAMFUNC_E",
		"LIBRARYFUNC_E",

		"ARITHEXPR_E",
		"BOOLEXPR_E",
		"ASSIGNEXPR_E",
		"NEWTABLE_E",

		"CONSTNUM_E",
		"CONSTBOOL_E",
		"CONSTSTRING_E",

		"NIL_E",
		"LABEL_E"
	};
	
	return ar[type];
}
char *literal_of_op(enum iopcode op){
	char *ar[] = {
		"ASSIGN_Q",
		"ADD",
		"SUB",
		"MUL",
		"DIV",
		"MOD",
		"UMINUS_Q",
		"AND_Q",
		"OR_Q",
		"NOT_Q",
		"IF_EQ",
		"IF_NOTEQ",
		"IF_LESS_EQ",
		"IF_GREATER_EQ",
		"IF_LESS",
		"IF_GREATER",
		"JUMP",
		"LABEL",
		"FUNCSTART",
		"FUNCEND",
		"RET",
		"CALL",
		"PARAM",
		"GETRETVAL",
		"TABLECREATE",
		"TABLEGETELEM",
		"TABLESETELEM",
	};
	
	return ar[op];
}

