%{
#include <string.h>
#include "parser.h"
#include "symtable.h"
#define YY_DECL int alpha_yylex()

int tokenNo=0,comment_count=0,error_count=0;
char ch, temp[2], *strtemp;

/*
const char* tostr(int val) {
   switch(val) {
	case ASSIGN:    		return "=";
	case PLUS:			return "+";
	case MINUS:			return "-";
	case STAR:			return "*";
	case DIVIDE:			return "/";
	case MODULE:		return "%";
	case EQUAL:		return "==";
	case DIFF:			return "!=";
	case PLUSPLUS:		return "++";
	case MINUSMINUS:		return "--";
	case HIGHER:		return ">";
	case LOWER:		return "<";
	case HIGHER_EQ:		return ">=";
	case LOWER_EQ:		return "<=";
	
	case IF:			return "IF";
	case ELSE:			return "ELSE";
	case WHILE:			return "WHILE";
	case FOR:			return "FOR";
	case FUNCTION:		return "FUNCTION";
	case RETURN:		return "RETURN";
	case BREAK:			return "BREAK";
	case CONTINUE:		return "CONTINUE";
	case AND:			return "AND";
	case NOT:			return "NOT";
	case OR:			return "OR";
	case LOCAL:			return "LOCAL";
	case TRUE:			return "TRUE";
	case FALSE:			return "FALSE";
	case NIL:			return "NIL";

	case LEFT_BRACE:		return "{";
	case RIGHT_BRACE:	return "}";
	case LEFT_BRACKET:	return "[";
	case RIGHT_BRACKET: 	return "]";
	case LEFT_PAR:		return "(";
	case RIGHT_PAR:		return ")";
	case SEMICOLON:		return ";";
	case COMMA:		return ",";
	case COLON:		return ":";
	case DOUBLE_COLON: 	return "::";
	case PERIOD:		return ".";
	case DOUBLE_PERIOD: 	return "..";

	default:		break;	
   }
}
*/

%}

%option noyywrap
%option outfile ="lex.c"
%option yylineno
%option prefix="alpha_yy"

character		[a-zA-Z]
integer			[0-9]([0-9]*)
real			[0-9]*\.[0-9](e|E)?[0-9]*
IF			"if"
ELSE			"else"
WHILE			"while"
FOR			"for"
FUNCTION		"function"
RETURN			"return"
BREAK			"break"
CONTINUE		"continue"
AND			"and"
NOT			"not"
OR			"or"
LOCAL			"local"
TRUE			"true"
FALSE			"false"
NIL			"nil"

LEFT_BRACE	\{
RIGHT_BRACE	\}
LEFT_BRACKET	\[
RIGHT_BRACKET	\]
LEFT_PAR		\(
RIGHT_PAR	\)
SEMICOLON		\;
COMMA		\,
COLON		\:
DOUBLE_COLON	\::
PERIOD		\.
DOUBLE_PERIOD	\.\.

ASSIGN		\=
PLUS		\+
MINUS		\-
STAR			\*
DIVIDE		\/
MODULE		\%
EQUAL		\==
DIFF			\!=
PLUSPLUS		\++
MINUSMINUS	\--
HIGHER		\>
LOWER		\<
HIGHER_EQ	\>=
LOWER_EQ	\<=


id			[a-zA-Z][a-zA-Z_0-9_]*
space			[\r \t\v]
backslash_n		[\n]
string			\"[]*\"
comment2		"//".*

%x COMMENT1
%x COMMENT2
%x STRING_VAL  
%x ESCAPE


%%

"\""			    {strtemp = malloc(sizeof(char)); strcpy(strtemp, alpha_yytext);}	BEGIN(STRING_VAL);
<STRING_VAL>"\\" 		{BEGIN(ESCAPE);}
<ESCAPE>"\\"		{temp[0]='\\';strtemp = realloc(strtemp, strlen(strtemp)+1); strcat(strtemp, temp);BEGIN(STRING_VAL);}
<ESCAPE>"n" 		{temp[0]='\n';strtemp = realloc(strtemp, strlen(strtemp)+1); strcat(strtemp, temp);BEGIN(STRING_VAL);}
<ESCAPE>"t" 		{temp[0]='\t';strtemp = realloc(strtemp, strlen(strtemp)+1); strcat(strtemp, temp);BEGIN(STRING_VAL);}
<ESCAPE>"\"" 		{temp[0]='\"';strtemp = realloc(strtemp, strlen(strtemp)+1); strcat(strtemp, temp);BEGIN(STRING_VAL);}
<ESCAPE>"r" 		{temp[0]='\r';strtemp = realloc(strtemp, strlen(strtemp)+1); strcat(strtemp, temp);BEGIN(STRING_VAL);}
<ESCAPE>{character}	{printf("error line: %d :unknown escape character %s\n",alpha_yylineno,alpha_yytext);BEGIN(STRING_VAL);}
<STRING_VAL>"\n"		{temp[0]='\n';strtemp = realloc(strtemp, strlen(strtemp)+1); strcat(strtemp, temp);}
<STRING_VAL>"\""		{strtemp = realloc(strtemp, strlen(strtemp)+1); strcat(strtemp, alpha_yytext);
				alpha_yylval.stringValue = strdup(strtemp); BEGIN(INITIAL); return STRING;}
<STRING_VAL>.		    {strtemp = realloc(strtemp, strlen(strtemp)+1); strcat(strtemp, alpha_yytext);}
<STRING_VAL><<EOF>>		{printf("error line: %d :string didn't end while EOF\n", alpha_yylineno);exit(-1);}



"/*"				{comment_count++;printf("%d:	#%d	new COMMENT start	",alpha_yylineno,++tokenNo);	BEGIN (COMMENT1);}
<COMMENT1>[^(*|/)]*		{printf("%s",alpha_yytext);}
<COMMENT1>"/"+"*"		{comment_count++;printf("\n%d:	#%d	new COMMENT start       ",alpha_yylineno,++tokenNo);}
<COMMENT1>"*"+[^*/]*		{printf("%s",alpha_yytext);}
<COMMENT1>"*"+"/"		{printf("\n%d:	COMMENT finish\n",alpha_yylineno);  comment_count--;  if(comment_count==0) BEGIN(INITIAL);}
<COMMENT1><<EOF>>		{printf("Error :comment didn't end while EOF\n");exit(-1);}

"//"				{}	BEGIN (COMMENT2);
<COMMENT2>[.]*			{}
<COMMENT2>[^\n]*		{}	BEGIN(INITIAL);



{IF}			{return IF;}
{ELSE}			{return ELSE;}
{WHILE}			{return WHILE;}
{FOR}			{return FOR;}
{FUNCTION}		{return FUNCTION;}
{RETURN}		{return RETURN;}
{BREAK}			{return BREAK;}
{CONTINUE}		{return CONTINUE;}
{AND}			{return AND;}
{NOT}			{return NOT;}
{OR}			{return OR;}
{LOCAL}			{return LOCAL;}
{TRUE}			{alpha_yylval.intValue= 1; return TRUE;}
{FALSE}			{alpha_yylval.intValue= 0; return FALSE;}
{NIL}			{return NIL;}

{ASSIGN}		{return ASSIGN;}
{PLUS}			{return PLUS;}
{MINUS}			{return MINUS;}
{STAR}			{return STAR;}
{DIVIDE}		{return DIVIDE;}
{MODULE}		{return MODULE;}
{EQUAL}			{return EQUAL;}
{DIFF}			{return DIFF;}
{PLUSPLUS}		{return PLUSPLUS;}
{MINUSMINUS}		{return MINUSMINUS;}
{HIGHER}		{return HIGHER;}
{LOWER}			{return LOWER;}
{HIGHER_EQ}		{return HIGHER_EQ;}
{LOWER_EQ}		{return LOWER_EQ;}

{id}			{alpha_yylval.stringValue = strdup(yytext); return ID;}

{LEFT_BRACE}		{return LEFT_BRACE;}
{RIGHT_BRACE}		{return RIGHT_BRACE;}
{LEFT_BRACKET}		{return LEFT_BRACKET;}
{RIGHT_BRACKET}		{return RIGHT_BRACKET;}
{LEFT_PAR}		{return LEFT_PAR;}
{RIGHT_PAR}		{return RIGHT_PAR;}
{SEMICOLON}		{return SEMICOLON;}
{COMMA}			{return COMMA;}
{COLON}			{return COLON;}
{DOUBLE_COLON}		{return DOUBLE_COLON;}
{PERIOD}		{return PERIOD;}
{DOUBLE_PERIOD}		{return DOUBLE_PERIOD;}
{integer}		{alpha_yylval.intValue= atoi(yytext);return INTEGER;}

{real}		        {alpha_yylval.floatValue = atof(yytext); return REAL;}


{space}			    {}
{backslash_n}		{}

.			{
				ch=input();
				//err++;
				if(ch!=' ' && ch!='\n' && ch!='\t'){
					temp[0]=ch;
					strcat(alpha_yytext,temp);
					while(ch!=' ' && ch!='\n' && ch!='\t') {
						ch=input();
						temp[0]=ch;
						strcat(alpha_yytext,temp);
					}
					
					fprintf(stderr,"error line: %d :unknown token %s\n",alpha_yylineno,alpha_yytext);
				}
				else
				{
					if(ch=='\n') fprintf(stderr,"error line: %d :unknown token %s\n",alpha_yylineno-1,alpha_yytext);
					else fprintf(stderr,"error line: %d :unknown token %s\n",alpha_yylineno,alpha_yytext);
					unput(ch);
				}
					
			}


%%


