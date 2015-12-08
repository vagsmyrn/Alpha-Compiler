
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     STRING = 259,
     INTEGER = 260,
     REAL = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     FOR = 265,
     FUNCTION = 266,
     RETURN = 267,
     BREAK = 268,
     CONTINUE = 269,
     LOCAL = 270,
     TRUE = 271,
     FALSE = 272,
     NIL = 273,
     LEFT_BRACE = 274,
     RIGHT_BRACE = 275,
     COLON = 276,
     DOUBLE_COLON = 277,
     PERIOD = 278,
     LOWEST_PREC = 279,
     SEMICOLON = 280,
     ASSIGN = 281,
     COMMA = 282,
     OR = 283,
     AND = 284,
     DIFF = 285,
     EQUAL = 286,
     LOWER_EQ = 287,
     LOWER = 288,
     HIGHER_EQ = 289,
     HIGHER = 290,
     MINUS = 291,
     PLUS = 292,
     MIDDLE_PREC = 293,
     MODULE = 294,
     DIVIDE = 295,
     STAR = 296,
     UMINUS = 297,
     MINUSMINUS = 298,
     PLUSPLUS = 299,
     NOT = 300,
     DOUBLE_PERIOD = 301,
     RIGHT_BRACKET = 302,
     LEFT_BRACKET = 303,
     RIGHT_PAR = 304,
     LEFT_PAR = 305,
     HIGHEST_PREC = 306
   };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define INTEGER 260
#define REAL 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define FUNCTION 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define LOCAL 270
#define TRUE 271
#define FALSE 272
#define NIL 273
#define LEFT_BRACE 274
#define RIGHT_BRACE 275
#define COLON 276
#define DOUBLE_COLON 277
#define PERIOD 278
#define LOWEST_PREC 279
#define SEMICOLON 280
#define ASSIGN 281
#define COMMA 282
#define OR 283
#define AND 284
#define DIFF 285
#define EQUAL 286
#define LOWER_EQ 287
#define LOWER 288
#define HIGHER_EQ 289
#define HIGHER 290
#define MINUS 291
#define PLUS 292
#define MIDDLE_PREC 293
#define MODULE 294
#define DIVIDE 295
#define STAR 296
#define UMINUS 297
#define MINUSMINUS 298
#define PLUSPLUS 299
#define NOT 300
#define DOUBLE_PERIOD 301
#define RIGHT_BRACKET 302
#define LEFT_BRACKET 303
#define RIGHT_PAR 304
#define LEFT_PAR 305
#define HIGHEST_PREC 306




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 68 "parser.y"

	char* stringValue;
	int	intValue;
	float floatValue;
	int opcode;
	
	struct expr *value;



/* Line 1676 of yacc.c  */
#line 165 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE alpha_yylval;


