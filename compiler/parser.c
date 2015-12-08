
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         alpha_yyparse
#define yylex           alpha_yylex
#define yyerror         alpha_yyerror
#define yylval          alpha_yylval
#define yychar          alpha_yychar
#define yydebug         alpha_yydebug
#define yynerrs         alpha_yynerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

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


/* Line 189 of yacc.c  */
#line 127 "parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 68 "parser.y"

	char* stringValue;
	int	intValue;
	float floatValue;
	int opcode;
	
	struct expr *value;



/* Line 214 of yacc.c  */
#line 276 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 288 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   525

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNRULES -- Number of states.  */
#define YYNSTATES  192

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    12,    14,    16,    18,
      21,    24,    26,    28,    30,    32,    36,    40,    44,    48,
      52,    56,    60,    64,    68,    72,    76,    80,    84,    86,
      88,    92,    95,    98,   101,   104,   107,   110,   114,   116,
     118,   120,   122,   126,   128,   131,   134,   136,   140,   144,
     149,   154,   159,   162,   169,   171,   173,   177,   183,   185,
     188,   189,   192,   194,   197,   198,   200,   203,   206,   210,
     214,   216,   219,   220,   223,   229,   230,   235,   239,   240,
     241,   249,   250,   251,   260,   262,   264,   266,   268,   270,
     272,   274,   277,   278,   281,   284,   289,   294,   296,   297,
     298,   306,   307,   308,   309,   322,   325
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    54,    53,    -1,    -1,    55,    25,    -1,
      85,    -1,    88,    -1,    91,    -1,    95,    -1,    13,    25,
      -1,    14,    25,    -1,    74,    -1,    77,    -1,    25,    -1,
      57,    -1,    55,    37,    55,    -1,    55,    36,    55,    -1,
      55,    41,    55,    -1,    55,    40,    55,    -1,    55,    39,
      55,    -1,    55,    35,    55,    -1,    55,    34,    55,    -1,
      55,    33,    55,    -1,    55,    32,    55,    -1,    55,    31,
      55,    -1,    55,    30,    55,    -1,    55,    29,    55,    -1,
      55,    28,    55,    -1,    56,    -1,    58,    -1,    50,    55,
      49,    -1,    36,    55,    -1,    45,    55,    -1,    44,    59,
      -1,    59,    44,    -1,    43,    59,    -1,    59,    43,    -1,
      59,    26,    55,    -1,    59,    -1,    61,    -1,    70,    -1,
      82,    -1,    50,    77,    49,    -1,     3,    -1,    15,     3,
      -1,    22,     3,    -1,    60,    -1,    59,    23,     3,    -1,
      61,    23,     3,    -1,    59,    48,    55,    47,    -1,    61,
      48,    55,    47,    -1,    61,    50,    65,    49,    -1,    59,
      62,    -1,    50,    77,    49,    50,    65,    49,    -1,    63,
      -1,    64,    -1,    50,    65,    49,    -1,    46,     3,    50,
      65,    49,    -1,    55,    -1,    55,    66,    -1,    -1,    27,
      65,    -1,    55,    -1,    55,    69,    -1,    -1,    55,    -1,
      55,    69,    -1,    27,    67,    -1,    48,    68,    47,    -1,
      48,    71,    47,    -1,    73,    -1,    73,    72,    -1,    -1,
      27,    71,    -1,    19,    55,    21,    55,    20,    -1,    -1,
      19,    75,    53,    20,    -1,    19,    53,    20,    -1,    -1,
      -1,    11,    78,    50,    79,    83,    49,    76,    -1,    -1,
      -1,    11,     3,    80,    50,    81,    83,    49,    76,    -1,
       5,    -1,     6,    -1,     4,    -1,    18,    -1,    16,    -1,
      17,    -1,     3,    -1,     3,    84,    -1,    -1,    27,    83,
      -1,    86,    54,    -1,    86,    54,    87,    54,    -1,     7,
      50,    55,    49,    -1,     8,    -1,    -1,    -1,     9,    50,
      89,    55,    49,    90,    54,    -1,    -1,    -1,    -1,    10,
      50,    67,    25,    92,    55,    25,    93,    67,    49,    94,
      54,    -1,    12,    25,    -1,    12,    55,    25,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,   100,   104,   105,   106,   107,   108,   109,
     120,   131,   132,   133,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   158,
     159,   160,   167,   173,   190,   214,   232,   259,   282,   283,
     284,   285,   286,   290,   310,   332,   342,   347,   368,   385,
     400,   417,   432,   447,   466,   467,   471,   475,   479,   484,
     489,   493,   497,   498,   499,   503,   504,   508,   512,   536,
     560,   561,   562,   566,   570,   578,   578,   582,   586,   597,
     586,   607,   622,   606,   634,   640,   646,   652,   657,   663,
     672,   683,   693,   696,   700,   710,   731,   743,   750,   754,
     750,   785,   795,   802,   785,   820,   828
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "INTEGER", "REAL", "IF",
  "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE",
  "LOCAL", "TRUE", "FALSE", "NIL", "LEFT_BRACE", "RIGHT_BRACE", "COLON",
  "DOUBLE_COLON", "PERIOD", "LOWEST_PREC", "SEMICOLON", "ASSIGN", "COMMA",
  "OR", "AND", "DIFF", "EQUAL", "LOWER_EQ", "LOWER", "HIGHER_EQ", "HIGHER",
  "MINUS", "PLUS", "MIDDLE_PREC", "MODULE", "DIVIDE", "STAR", "UMINUS",
  "MINUSMINUS", "PLUSPLUS", "NOT", "DOUBLE_PERIOD", "RIGHT_BRACKET",
  "LEFT_BRACKET", "RIGHT_PAR", "LEFT_PAR", "HIGHEST_PREC", "$accept",
  "program", "stmt", "expr", "term", "assignexpr", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "calllist",
  "exprs2", "elist", "elistobj", "exprs", "objectdef", "indexed",
  "indexedelems", "indexedelem", "block", "$@1", "block2", "funcdef",
  "$@2", "$@3", "$@4", "$@5", "const", "idlist", "idlists", "ifstmt",
  "ifprefix", "elseprefix", "whilestmt", "$@6", "$@7", "forstmt", "$@8",
  "$@9", "$@10", "returnstmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    53,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      56,    56,    56,    56,    56,    56,    56,    57,    58,    58,
      58,    58,    58,    59,    59,    59,    59,    60,    60,    60,
      60,    61,    61,    61,    62,    62,    63,    64,    65,    65,
      65,    66,    67,    67,    67,    68,    68,    69,    70,    70,
      71,    71,    71,    72,    73,    75,    74,    76,    78,    79,
      77,    80,    81,    77,    82,    82,    82,    82,    82,    82,
      83,    83,    83,    84,    85,    85,    86,    87,    89,    90,
      88,    92,    93,    94,    91,    95,    95
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     2,     2,     2,     2,     2,     2,     3,     1,     1,
       1,     1,     3,     1,     2,     2,     1,     3,     3,     4,
       4,     4,     2,     6,     1,     1,     3,     5,     1,     2,
       0,     2,     1,     2,     0,     1,     2,     2,     3,     3,
       1,     2,     0,     2,     5,     0,     4,     3,     0,     0,
       7,     0,     0,     8,     1,     1,     1,     1,     1,     1,
       1,     2,     0,     2,     2,     4,     4,     1,     0,     0,
       7,     0,     0,     0,    12,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    43,    86,    84,    85,     0,     0,     0,    78,     0,
       0,     0,     0,    88,    89,    87,    75,     0,    13,     0,
       0,     0,     0,    72,     0,     0,     3,     0,    28,    14,
      29,    38,    46,    39,    40,    11,    12,    41,     5,     0,
       6,     7,     8,     0,    98,    64,    81,     0,   105,     0,
       9,    10,    44,     3,    45,    31,     0,    35,     0,    33,
      32,     0,    65,     0,     0,    70,     0,     0,     1,     2,
       4,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    34,     0,     0,
      60,    52,    54,    55,     0,     0,    60,    94,     0,     0,
      62,     0,     0,    79,   106,     0,     0,     0,    64,    66,
      68,    69,    72,    71,    30,    42,    27,    26,    25,    24,
      23,    22,    21,    20,    16,    15,    19,    18,    17,    47,
      37,     0,     0,    58,     0,    48,     0,     0,    97,     0,
      96,     0,    63,   101,    82,    92,    76,     0,     0,    67,
      73,    60,    60,    49,    60,    59,    56,    50,    51,    95,
      99,     0,    92,    90,     0,     0,     0,     0,    61,     0,
       0,     0,    92,    91,     0,    74,    53,    57,   100,   102,
       0,    93,     3,    80,    64,    83,     0,     0,    77,   103,
       0,   104
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      91,    92,    93,   134,   155,   101,    63,   109,    34,    64,
     113,    65,    35,    53,   183,    36,    47,   145,   102,   162,
      37,   164,   173,    38,    39,   139,    40,    99,   169,    41,
     161,   184,   190,    42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -152
static const yytype_int16 yypact[] =
{
     111,  -152,  -152,  -152,  -152,   -41,   -30,   -28,    22,     1,
      10,    23,    44,  -152,  -152,  -152,  -152,    47,  -152,   209,
       9,     9,   209,   161,   185,    58,   111,   369,  -152,  -152,
    -152,   193,  -152,     6,  -152,  -152,  -152,  -152,  -152,   111,
    -152,  -152,  -152,   209,  -152,   209,  -152,    11,  -152,   386,
    -152,  -152,  -152,   111,  -152,  -152,    49,     7,     6,     7,
    -152,   209,   418,    28,    30,    51,   232,    35,  -152,  -152,
    -152,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,    85,   209,  -152,  -152,    86,   209,
     209,  -152,  -152,  -152,    88,   209,   209,    84,   254,   209,
     418,    68,    45,  -152,  -152,    74,    48,   315,   209,  -152,
    -152,  -152,    77,  -152,  -152,    50,   460,   472,   484,   484,
      71,    71,    71,    71,     2,     2,  -152,  -152,  -152,  -152,
     447,    59,   329,   433,    52,  -152,   349,    64,  -152,   111,
    -152,   276,  -152,  -152,  -152,    95,  -152,    50,   209,  -152,
    -152,   209,   209,  -152,   209,  -152,  -152,  -152,  -152,  -152,
    -152,   209,    95,    92,    82,   298,    89,    91,  -152,   111,
     403,    97,    95,  -152,   115,  -152,  -152,  -152,  -152,  -152,
     115,  -152,   111,  -152,   209,  -152,   117,    99,  -152,  -152,
     111,  -152
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,   -25,   -37,    -9,  -152,  -152,  -152,    12,  -152,    18,
    -152,  -152,  -152,   -69,  -152,  -105,  -152,    41,  -152,    32,
    -152,  -152,  -152,  -152,   -45,   -16,  -152,  -152,  -152,  -152,
    -152,  -151,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      49,    69,    97,   149,     1,     2,     3,     4,    67,    43,
      55,   171,     1,    60,    62,    66,    12,    13,    14,    15,
      44,   181,    45,    17,    12,    46,    48,   137,   105,    94,
      84,    17,    57,    59,    98,    50,   100,    19,    58,    58,
     106,    81,    82,    83,    20,    21,    22,    52,    51,    23,
      54,    24,   107,    88,    95,    89,    96,    90,    68,    56,
       8,   103,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   110,   130,   111,   112,   187,
     132,   133,   166,   167,   115,   168,   136,   133,   129,   131,
     141,   135,   138,   143,   146,   144,    61,   147,   163,   100,
     151,   156,   159,    -1,    -1,    -1,    -1,    79,    80,   152,
      81,    82,    83,   158,     1,     2,     3,     4,     5,   172,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,   174,   178,    17,   182,   185,    18,   188,   176,   165,
     177,   142,   133,   133,   150,   133,   180,    19,   189,     0,
       0,     0,   170,   191,    20,    21,    22,   186,     0,    23,
       0,    24,     0,     0,     1,     2,     3,     4,     0,     0,
       0,     0,     0,     0,     0,   100,    12,    13,    14,    15,
      61,     0,     0,    17,     0,     0,     0,     0,     1,     2,
       3,     4,     0,     0,     0,     0,     8,    19,     0,     0,
      12,    13,    14,    15,    20,    21,    22,    17,     0,    23,
       0,    24,     1,     2,     3,     4,    84,     0,     0,    85,
       0,    19,     0,     0,    12,    13,    14,    15,    20,    21,
      22,    17,     0,    23,     0,    24,    86,    87,     0,    88,
       0,    89,     0,    90,     0,    19,     0,     0,     0,     0,
       0,     0,    20,    21,    22,     0,     0,    23,     0,    24,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
       0,    81,    82,    83,     0,     0,     0,     0,     0,     0,
       0,   114,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     0,    81,    82,    83,     0,     0,     0,     0,
       0,     0,     0,   140,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,    81,    82,    83,   175,     0,
       0,     0,     0,     0,     0,   160,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   148,    81,    82,    83,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     0,    81,    82,    83,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     0,    81,    82,
      83,     0,     0,     0,     0,     0,   153,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     0,    81,    82,
      83,     0,     0,     0,    70,     0,   157,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     0,    81,    82,
      83,   104,     0,     0,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,    81,    82,    83,   179,     0,
       0,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,     0,    81,    82,    83,   108,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,     0,    81,    82,    83,
     154,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,     0,    81,    82,    83,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,     0,    81,    82,    83,    72,
      73,    74,    75,    76,    77,    78,    79,    80,     0,    81,
      82,    83,    73,    74,    75,    76,    77,    78,    79,    80,
       0,    81,    82,    83,    -1,    -1,    75,    76,    77,    78,
      79,    80,     0,    81,    82,    83
};

static const yytype_int16 yycheck[] =
{
       9,    26,    39,   108,     3,     4,     5,     6,    24,    50,
      19,   162,     3,    22,    23,    24,    15,    16,    17,    18,
      50,   172,    50,    22,    15,     3,    25,    96,    53,    23,
      23,    22,    20,    21,    43,    25,    45,    36,    20,    21,
      56,    39,    40,    41,    43,    44,    45,     3,    25,    48,
       3,    50,    61,    46,    48,    48,    50,    50,     0,    50,
      11,    50,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    47,    85,    47,    27,   184,
      89,    90,   151,   152,    49,   154,    95,    96,     3,     3,
      99,     3,     8,    25,    20,    50,    19,    49,     3,   108,
      50,    49,   139,    32,    33,    34,    35,    36,    37,    50,
      39,    40,    41,    49,     3,     4,     5,     6,     7,    27,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    49,   169,    22,    19,   180,    25,    20,    49,   148,
      49,   100,   151,   152,   112,   154,    49,    36,    49,    -1,
      -1,    -1,   161,   190,    43,    44,    45,   182,    -1,    48,
      -1,    50,    -1,    -1,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,    15,    16,    17,    18,
      19,    -1,    -1,    22,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    11,    36,    -1,    -1,
      15,    16,    17,    18,    43,    44,    45,    22,    -1,    48,
      -1,    50,     3,     4,     5,     6,    23,    -1,    -1,    26,
      -1,    36,    -1,    -1,    15,    16,    17,    18,    43,    44,
      45,    22,    -1,    48,    -1,    50,    43,    44,    -1,    46,
      -1,    48,    -1,    50,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    48,    -1,    50,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    39,    40,    41,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    21,    39,    40,    41,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    39,    40,    41,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    47,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    25,    -1,    47,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    39,    40,    41,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    39,    40,    41,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    39,    40,    41,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    39,    40,    41,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    39,    40,    41,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    39,    40,    41,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    40,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    22,    25,    36,
      43,    44,    45,    48,    50,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    70,    74,    77,    82,    85,    86,
      88,    91,    95,    50,    50,    50,     3,    78,    25,    55,
      25,    25,     3,    75,     3,    55,    50,    59,    61,    59,
      55,    19,    55,    68,    71,    73,    55,    77,     0,    53,
      25,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    39,    40,    41,    23,    26,    43,    44,    46,    48,
      50,    62,    63,    64,    23,    48,    50,    54,    55,    89,
      55,    67,    80,    50,    25,    53,    77,    55,    27,    69,
      47,    47,    27,    72,    49,    49,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,     3,
      55,     3,    55,    55,    65,     3,    55,    65,     8,    87,
      49,    55,    69,    25,    50,    79,    20,    49,    21,    67,
      71,    50,    50,    47,    27,    66,    49,    47,    49,    54,
      49,    92,    81,     3,    83,    55,    65,    65,    65,    90,
      55,    83,    27,    84,    49,    20,    49,    49,    54,    25,
      49,    83,    19,    76,    93,    76,    53,    67,    20,    49,
      94,    54
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "ID" */

/* Line 1000 of yacc.c  */
#line 94 "parser.y"
	{ free((yyvaluep->stringValue)); };

/* Line 1000 of yacc.c  */
#line 1433 "parser.c"
	break;

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

/* User initialization code.  */

/* Line 1242 of yacc.c  */
#line 59 "parser.y"
{
TRUE_EXPR = create_expr(CONSTBOOL_E, NULL);
TRUE_EXPR->boolConst = 1;

FALSE_EXPR = create_expr(CONSTBOOL_E, NULL);
FALSE_EXPR->boolConst = 0;

}

/* Line 1242 of yacc.c  */
#line 1573 "parser.c"

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 99 "parser.y"
    { log("stmt program -> program");}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 100 "parser.y"
    { log("empty -> program"); (yyval.value) = NULL; }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 104 "parser.y"
    { (yyval.value) = (yyvsp[(1) - (2)].value); }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 105 "parser.y"
    { log("ifstmt -> stmt");}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    { log("whilestmt -> stmt");}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 107 "parser.y"
    { log("forstmt; -> stmt");}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    { log("returnstmt; -> stmt");}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    {
						log("break; -> stmt");
						if(loop_flag==0){
							print_err("BREAK without a loop.");
							exit(-1);
						}
						temp_quad = create_quad(JUMP, NULL, NULL, peek_loop()->end_label, -1, alpha_yylineno);
						insert_quad(temp_quad);
						(yyval.value) = create_expr(NIL_E, NULL);
						(yyval.value)->quad = temp_quad;
					}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 120 "parser.y"
    {
						log("continue; -> stmt");
						if(loop_flag==0){
							print_err("CONTINUE without a loop.");
							exit(-1);
						}
						temp_quad = create_quad(JUMP, NULL, NULL, peek_loop()->start_label, -1, alpha_yylineno);
						insert_quad(temp_quad);
						(yyval.value) = create_expr(NIL_E, NULL);
						(yyval.value)->quad = temp_quad;
					}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    { log("block -> stmt"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    { log("funcdef -> stmt"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    { log(";->stmt"); (yyval.value) = create_expr(NIL_E, NULL); }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    { (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    { (yyval.value) = genetate_expr_code(ADD, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 141 "parser.y"
    { (yyval.value) = genetate_expr_code(SUB, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    { (yyval.value) = genetate_expr_code(MUL, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 143 "parser.y"
    { (yyval.value) = genetate_expr_code(DIV, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    { (yyval.value) = genetate_expr_code(MOD, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    { (yyval.value) = genetate_rel_expr_code(IF_GREATER, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 146 "parser.y"
    { (yyval.value) = genetate_rel_expr_code(IF_GREATER_EQ, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    { (yyval.value) = genetate_rel_expr_code(IF_LESS, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    { (yyval.value) = genetate_rel_expr_code(IF_LESS_EQ, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    { (yyval.value) = genetate_rel_expr_code(IF_EQ, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 150 "parser.y"
    { (yyval.value) = genetate_rel_expr_code(IF_NOTEQ, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    { (yyval.value) = genetate_expr_code(AND_Q, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    { (yyval.value) = genetate_expr_code(OR_Q, (yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value)); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    { (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    { log("primary -> term"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    { log("(expr) -> term"); (yyval.value) = (yyvsp[(2) - (3)].value); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    { 
			log("-expr -> term"); (yyval.value) = (yyvsp[(2) - (2)].value);
		
			expr *ex = genetate_unary_expr_code(UMINUS_Q, (yyvsp[(2) - (2)].value));
			(yyval.value) = ex; 
			//$$ = genetate_expr_code(UMINUS_Q, $2, NULL);
		}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    { 
			log("not expr -> term"); 
			
			expr *ex = genetate_unary_expr_code(NOT_Q, (yyvsp[(2) - (2)].value));
			(yyval.value) = ex; 
		}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 173 "parser.y"
    {
			log("++lvalue -> term");
			
			if((yyvsp[(2) - (2)].value)->sym->type == USERFUNC){
				print_err("lvalue cannot be a function");
				exit(-1);
			}
			expr *ex = create_expr(CONSTNUM_E, NULL);
			ex->numConst = 1;
			ex = genetate_expr_code(ADD, (yyvsp[(2) - (2)].value), ex);
			
			quad *temp_quad = create_quad(ASSIGN_Q, ex, NULL, (yyvsp[(2) - (2)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			(yyval.value) = (yyvsp[(2) - (2)].value);
			(yyval.value)->quad = temp_quad;
			}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    {
			log("lvalue++ -> term");
			
			if((yyvsp[(1) - (2)].value)->sym->type == USERFUNC){
				print_err("lvalue cannot be a function");
				exit(-1);
			}
			Variable *temp_lvalue_var = var_copy((yyvsp[(1) - (2)].value)->sym->var, getTempId());
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
			
			ex1 = create_expr(VAR_E, temp_lvalue);

			temp_quad = create_quad(ASSIGN_Q, (yyvsp[(1) - (2)].value), NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			(yyval.value) = ex1;
			(yyval.value)->quad = temp_quad;
			
			expr *ex = create_expr(CONSTNUM_E, NULL);
			ex->numConst = 1;
			
			temp_quad = create_quad(ADD, (yyvsp[(1) - (2)].value), ex, (yyvsp[(1) - (2)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 214 "parser.y"
    {
			log("--lvalue -> term");
			
			if((yyvsp[(2) - (2)].value)->sym->type == USERFUNC){
				print_err("lvalue cannot be a function");
				exit(-1);
			}
			expr *ex = create_expr(CONSTNUM_E, NULL);
			ex->numConst = 1;
			ex = genetate_expr_code(SUB, (yyvsp[(2) - (2)].value), ex);
			
			quad *temp_quad = create_quad(ASSIGN_Q, ex, NULL, (yyvsp[(2) - (2)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			(yyval.value) = (yyvsp[(2) - (2)].value);
			(yyval.value)->quad = temp_quad;
		}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 232 "parser.y"
    {
			log("lvalue-- -> term");
			
			if((yyvsp[(1) - (2)].value)->sym->type == USERFUNC){
				print_err("lvalue cannot be a function");
				exit(-1);
			}
			Variable *temp_lvalue_var = var_copy((yyvsp[(1) - (2)].value)->sym->var, getTempId());
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
			
			ex1 = create_expr(VAR_E, temp_lvalue);

			temp_quad = create_quad(ASSIGN_Q, (yyvsp[(1) - (2)].value), NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			(yyval.value) = ex1;
			(yyval.value)->quad = temp_quad;
			
			expr *ex = create_expr(CONSTNUM_E, NULL);
			ex->numConst = 1;
			
			temp_quad = create_quad(SUB, (yyvsp[(1) - (2)].value), ex, (yyvsp[(1) - (2)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);			
		}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 259 "parser.y"
    {
				log("lvalue ASSIGN expr -> assignexpr");
				if((yyvsp[(1) - (3)].value) == NULL) {
					print_err("Ignoring NULL lvalue");
				} else if((yyvsp[(1) - (3)].value)->sym->type == USERFUNC){
					print_err("Cannot assign to function %s %s. scope: %d, line: %d", literal_of((yyvsp[(1) - (3)].value)->sym->type), (yyvsp[(1) - (3)].value)->sym->var->name, (yyvsp[(1) - (3)].value)->sym->var->scope, (yyvsp[(1) - (3)].value)->sym->var->line);
				}else if((yyvsp[(1) - (3)].value)->type == TABLEITEM_E) {
					temp_quad = create_quad(TABLESETELEM, (yyvsp[(3) - (3)].value), (yyvsp[(3) - (3)].value)->index, (yyvsp[(1) - (3)].value), -1, alpha_yylineno);
					insert_quad(temp_quad);
					(yyval.value) = (yyvsp[(1) - (3)].value);
					(yyval.value)->quad = temp_quad;
				}else{
					temp_quad = create_quad(ASSIGN_Q, (yyvsp[(3) - (3)].value), NULL, (yyvsp[(1) - (3)].value), -1, alpha_yylineno);
					insert_quad(temp_quad);
					(yyval.value) = (yyvsp[(1) - (3)].value);
					//$$ = create_expr(ASSIGNEXPR_E, $1->sym);
					(yyval.value)->quad = temp_quad;
				}
			}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 282 "parser.y"
    { log("lvalue -> primary"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
    { log("call -> primary"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 284 "parser.y"
    { log("objectdef -> primary"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 285 "parser.y"
    { log("const -> primary"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    { log("( funcdef ) -> primary"); (yyval.value) = (yyvsp[(2) - (3)].value); }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 290 "parser.y"
    {
			log("ID:%s -> lvalue",(yyvsp[(1) - (1)].stringValue));
			
			st_res = lookup(scope, (yyvsp[(1) - (1)].stringValue), ANY);
			if(st_res == NULL){
				print_info("INSERT in ST variable (ID:%s) scope: %d", (yyvsp[(1) - (1)].stringValue), scope);
				Variable *var = createVar((yyvsp[(1) - (1)].stringValue), scope, alpha_yylineno);
				(yyval.value) = create_expr(VAR_E, insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR));
			}else{
				if(st_res->type == USERFUNC){
					(yyval.value) = create_expr(PROGRAMFUNC_E, st_res);
				}else if(st_res->type == LIBFUNC ){
					(yyval.value) = create_expr(LIBRARYFUNC_E, st_res);
				}else if(st_res->var->scope != 0 && st_res->var->scope != scope && functionBetween){
					print_err("Cannot access %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, scope, st_res->var->line);
				}else{
					(yyval.value) = create_expr(VAR_E, st_res);
				}
			}
		}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 310 "parser.y"
    {
			log("LOCAL ID:%s -> lvalue",(yyvsp[(2) - (2)].stringValue));
			st_res = lookup(scope, (yyvsp[(2) - (2)].stringValue), LOCAL_LIB_SCOPE);
			if(st_res==NULL){
				print_info("INSERT in ST local variable (LOCAL ID) scope: %d, line: %d", scope, alpha_yylineno);
				Variable *var = createVar((yyvsp[(2) - (2)].stringValue), scope, alpha_yylineno);
				if(scope == 0){
					(yyval.value) = create_expr(VAR_E, insert(var, GLOBAL_VAR));
				} else {
					(yyval.value) = create_expr(VAR_E, insert(var, LOCAL_VAR));
				}
			}else{
				if(st_res->type == USERFUNC ||	(st_res->type == LIBFUNC && scope == 0)){
					(yyval.value) = create_expr(VAR_E, st_res);
				}else if(st_res->type == LIBFUNC ){
					print_err("Collision with %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, scope, st_res->var->line);
					exit(0);
				}else{
					(yyval.value) = create_expr(VAR_E, st_res);
				}
			}
		}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    {
			log("::ID:%s -> lvalue",(yyvsp[(2) - (2)].stringValue));
			st_res = lookup(scope, (yyvsp[(2) - (2)].stringValue), GLOBAL_SCOPE);
			if(st_res==NULL){
				print_err("Cannot find global symbol %s", (yyvsp[(2) - (2)].stringValue));
				exit(0);
			}else{
				(yyval.value) = create_expr(VAR_E, st_res);
			}
		}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 342 "parser.y"
    {log("member -> lvalue"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 347 "parser.y"
    {
			log("lvalue.ID: %s-> member", (yyvsp[(3) - (3)].stringValue));
			st_res = lookup_member((yyvsp[(1) - (3)].value)->sym, (yyvsp[(3) - (3)].stringValue));
			if(st_res == NULL){
				Variable *var = createVar((yyvsp[(3) - (3)].stringValue), (yyvsp[(1) - (3)].value)->sym->var->scope, alpha_yylineno);
				insert_member((yyvsp[(1) - (3)].value)->sym, var);
				print_info("INSERT in ST member variable (parent: %s, %s, %d) scope: %d, line: %d", (yyvsp[(1) - (3)].value)->sym->var->name, literal_of((yyvsp[(1) - (3)].value)->sym->type), (yyvsp[(1) - (3)].value)->sym->var->line, scope, alpha_yylineno);
			}
			Variable *temp_lvalue_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
		
			ex1 = create_expr(TABLEITEM_E, temp_lvalue);
			ex1->index = create_expr(CONSTSTRING_E, NULL);
			ex1->index->strConst = strdup((yyvsp[(3) - (3)].stringValue));
			(yyval.value) = ex1;
			
		
			temp_quad = create_quad(TABLEGETELEM, (yyvsp[(1) - (3)].value), NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			(yyval.value)->quad = temp_quad;
		}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 368 "parser.y"
    {
			log("call.ID:%s -> member",(yyvsp[(3) - (3)].stringValue));
			st_res = lookup_member((yyvsp[(1) - (3)].value)->sym, (yyvsp[(3) - (3)].stringValue));

			Variable *temp_lvalue_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
		
			ex1 = create_expr(TABLEITEM_E, temp_lvalue);
			ex1->index = create_expr(CONSTSTRING_E, NULL);
			ex1->index->strConst = strdup((yyvsp[(3) - (3)].stringValue));
			(yyval.value) = ex1;
			
		
			temp_quad = create_quad(TABLEGETELEM, (yyvsp[(1) - (3)].value), NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			(yyval.value)->quad = temp_quad;			
		}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 385 "parser.y"
    {
			log("lvalue [ expr ] -> member");
			
			Variable *temp_lvalue_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
		
			ex1 = create_expr(TABLEITEM_E, temp_lvalue);
			ex1->index = (yyvsp[(3) - (4)].value);
			(yyval.value) = ex1;
		
			temp_quad = create_quad(TABLEGETELEM, (yyvsp[(1) - (4)].value), NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			(yyval.value)->quad = temp_quad;
			
		}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 400 "parser.y"
    {
			log("call [ expr] -> member");
			
			Variable *temp_lvalue_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_lvalue = insert(temp_lvalue_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
		
			ex1 = create_expr(TABLEITEM_E, temp_lvalue);
			ex1->index = (yyvsp[(3) - (4)].value);
			(yyval.value) = ex1;
		
			temp_quad = create_quad(TABLEGETELEM, (yyvsp[(1) - (4)].value), NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
			(yyval.value)->quad = temp_quad;
		}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
    {
			log("call ( elist ) -> call");
			temp_quad = create_quad(CALL, NULL, NULL, (yyvsp[(1) - (4)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			Variable *var = createVar(getTempId(), scope, alpha_yylineno);
			st_res = insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);

			ex1 = create_expr(VAR_E, st_res);
	
			ex1->quad = create_quad(GETRETVAL, NULL, NULL, ex1, -1, alpha_yylineno);
			insert_quad(ex1->quad);
			
			(yyval.value) = ex1;
		}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 432 "parser.y"
    {
			log("lvalue callsufix -> call");
			temp_quad = create_quad(CALL, NULL, NULL, (yyvsp[(1) - (2)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			Variable *var = createVar(getTempId(), scope, alpha_yylineno);
			st_res = insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);

			ex1 = create_expr(VAR_E, st_res);
	
			ex1->quad = create_quad(GETRETVAL, NULL, NULL, ex1, -1, alpha_yylineno);
			insert_quad(ex1->quad);
			
			(yyval.value) = ex1;			
		}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 447 "parser.y"
    { 
			log("( funcdef ) ( elist ) -> call");
			temp_quad = create_quad(CALL, NULL, NULL, (yyvsp[(2) - (6)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			Variable *var = createVar(getTempId(), scope, alpha_yylineno);
			st_res = insert(var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);

			ex1 = create_expr(VAR_E, st_res);
	
			ex1->quad = create_quad(GETRETVAL, NULL, NULL, ex1, -1, alpha_yylineno);
			insert_quad(ex1->quad);
			
			(yyval.value) = ex1;			
		}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 466 "parser.y"
    { log("normcall -> callsuffix"); }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 467 "parser.y"
    { log("methodcall -> callsuffix"); }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 471 "parser.y"
    { log("( elist ) -> normcall");}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 475 "parser.y"
    { log(".. ID: %s ( elist )  -> op",(yyvsp[(2) - (5)].stringValue));}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 479 "parser.y"
    { 
			log("expr -> calllist");
			temp_quad = create_quad(PARAM, NULL, NULL, (yyvsp[(1) - (1)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 484 "parser.y"
    {
			log("expr exprs2 -> calllist");
			temp_quad = create_quad(PARAM, NULL, NULL, (yyvsp[(1) - (2)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 493 "parser.y"
    { log(", calllist -> exprs2");}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 497 "parser.y"
    { log("expr -> elist");}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 498 "parser.y"
    { log("expr exprs -> elist"); (yyvsp[(1) - (2)].value)->next = (yyvsp[(2) - (2)].value); (yyval.value) = (yyvsp[(1) - (2)].value); }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 499 "parser.y"
    { (yyval.value) = NULL; }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 503 "parser.y"
    { log("expr -> elistobj"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 504 "parser.y"
    { log("expr exprs -> elistobj"); (yyvsp[(1) - (2)].value)->next = (yyvsp[(2) - (2)].value); (yyval.value) = (yyvsp[(1) - (2)].value); }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 508 "parser.y"
    { log(", elist -> exprs"); (yyval.value) = (yyvsp[(2) - (2)].value); }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 512 "parser.y"
    { 
			log("[ elistobj ] -> objectdef");
			
			Variable *temp_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_table = insert(temp_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
			
			expr *table_expr = create_expr(NEWTABLE_E, temp_table);
			
			temp_quad = create_quad(TABLECREATE, NULL, NULL, table_expr, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			(yyval.value) = table_expr;
			(yyval.value)->quad = temp_quad;
			
			expr *temp;
			int i=0;
			for(temp = (yyvsp[(2) - (3)].value); temp!=NULL; temp = temp->next){
				expr *ex = create_expr(CONSTNUM_E, NULL);
				ex->numConst = i++;
				
				temp_quad = create_quad(TABLESETELEM, temp, ex, table_expr, -1, alpha_yylineno);
				insert_quad(temp_quad);	
			}
		}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 536 "parser.y"
    {
			log("[ indexed ] -> objectdef");
			
			Variable *temp_var = createVar(getTempId(), scope, alpha_yylineno);
			SymbolTableEntry *temp_table = insert(temp_var, (scope==0)?GLOBAL_VAR:LOCAL_VAR);
			
			expr *table_expr = create_expr(NEWTABLE_E, temp_table);
			
			temp_quad = create_quad(TABLECREATE, NULL, NULL, table_expr, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			(yyval.value) = table_expr;
			(yyval.value)->quad = temp_quad;
			
			expr *temp;

			for(temp = (yyvsp[(2) - (3)].value); temp!=NULL; temp = temp->next){
				temp_quad = create_quad(TABLESETELEM, temp, temp->index, table_expr, -1, alpha_yylineno);
				insert_quad(temp_quad);	
			}
		}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 560 "parser.y"
    { log("indexedelem -> indexed"); (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 561 "parser.y"
    { log("indexedelem indexedelems -> indexed"); (yyvsp[(1) - (2)].value)->next = (yyvsp[(2) - (2)].value); (yyval.value) = (yyvsp[(1) - (2)].value); }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 562 "parser.y"
    { (yyval.value) = NULL; }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 566 "parser.y"
    { log(", indexed -> indexedelems"); (yyval.value) = (yyvsp[(2) - (2)].value); }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 570 "parser.y"
    { 
			log("{ expr : expr } -> indexedelem");
			(yyvsp[(4) - (5)].value)->index = (yyvsp[(2) - (5)].value);
			(yyval.value) = (yyvsp[(4) - (5)].value);
		}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 578 "parser.y"
    { scope++; }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 578 "parser.y"
    { log("{ program } -> block"); (yyval.value) = (yyvsp[(3) - (4)].value); scope--;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 582 "parser.y"
    { log("{ program } -> block2"); }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 586 "parser.y"
    {
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
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 597 "parser.y"
    {scope++;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 598 "parser.y"
    { 
			st_res = lookup_variable(pop());
			ex1 = create_expr(PROGRAMFUNC_E, st_res);
			scope--; 
			(yyval.value) = ex1;
			temp_quad = create_quad(FUNCEND, NULL, NULL, ex1, -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 607 "parser.y"
    {
			log("funtion id (idlist) -> lvalue");
			st_res = lookup(scope, (yyvsp[(2) - (2)].stringValue), LOCAL_LIB_SCOPE);
			if(st_res==NULL || (st_res->var->scope != scope && st_res->type == USERFUNC)){
				print_info("INSERT in ST user function %s. scope: %d, line: %d", (yyvsp[(2) - (2)].stringValue), scope, alpha_yylineno);
				Variable *var = createVar((yyvsp[(2) - (2)].stringValue), scope, alpha_yylineno);
				st_res = insert(var, USERFUNC);
				push(var);
				ex1 = create_expr(PROGRAMFUNC_E, st_res);
				temp_quad = create_quad(FUNCSTART, NULL, NULL, ex1, -1, alpha_yylineno);
				insert_quad(temp_quad);
			}else if( st_res != NULL) {
    			print_err("Collision with %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, st_res->var->scope, st_res->var->line);
			}
		}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 622 "parser.y"
    { scope++; }
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 623 "parser.y"
    { 
				st_res = lookup_variable(pop());
				ex1 = create_expr(PROGRAMFUNC_E, st_res);
				scope--; 
				(yyval.value) = ex1;
				temp_quad = create_quad(FUNCEND, NULL, NULL, ex1, -1, alpha_yylineno);
				insert_quad(temp_quad);
			}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 634 "parser.y"
    {
			log("integer:%d -> const",(yyvsp[(1) - (1)].intValue));
			ex1 = create_expr(CONSTNUM_E, NULL);
			ex1->numConst = (yyvsp[(1) - (1)].intValue);
			(yyval.value) = ex1;
		}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 640 "parser.y"
    {
			log("real:%f -> const",(yyvsp[(1) - (1)].floatValue));
			ex1 = create_expr(CONSTNUM_E, NULL);
			ex1->numConst = (yyvsp[(1) - (1)].floatValue);
			(yyval.value) = ex1;
		}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 646 "parser.y"
    {
			log("string:%s -> const",(yyvsp[(1) - (1)].stringValue));
			ex1 = create_expr(CONSTSTRING_E, NULL);
			ex1->strConst = (yyvsp[(1) - (1)].stringValue);
			(yyval.value) = ex1;
		}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 652 "parser.y"
    {
			log("nil -> const");
			ex1 = create_expr(NIL_E, NULL);
			(yyval.value) = ex1;
		}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 657 "parser.y"
    {
			log("true -> const");
			ex1 = create_expr(CONSTBOOL_E, NULL);
			ex1->boolConst = 1;
			(yyval.value) = ex1;
		}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 663 "parser.y"
    {
			log("false -> const");
			ex1 = create_expr(CONSTBOOL_E, NULL);
			ex1->boolConst = 0;
			(yyval.value) = ex1;
		}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 672 "parser.y"
    {
			log("ID  -> idlist");
			st_res = lookup(scope, (yyvsp[(1) - (1)].stringValue), FORMAL_SCOPE);
			if(st_res==NULL){
				Variable *arg = createVar((yyvsp[(1) - (1)].stringValue), scope, alpha_yylineno);
				insert(arg, FORMAL_VAR);
				print_info("INSERT %s %s. scope: %d, line: %d", literal_of(FORMAL_VAR), arg->name, scope, arg->line);
			}else {
				print_err("Collision with %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, scope, st_res->var->line);
			}            
		}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 683 "parser.y"
    {
			st_res = lookup(scope, (yyvsp[(1) - (2)].stringValue), FORMAL_SCOPE);
			if(st_res==NULL){
            	Variable *arg = createVar((yyvsp[(1) - (2)].stringValue), scope, alpha_yylineno);
				insert(arg, FORMAL_VAR);
            	print_info("INSERT %s %s. scope: %d, line: %d", literal_of(FORMAL_VAR), arg->name, scope, arg->line);
			}else{
            	print_err("Collision with %s %s. scope: %d, line: %d", literal_of(st_res->type), st_res->var->name, scope, st_res->var->line);
			}										
		}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 696 "parser.y"
    { log(", idlist -> idlists");}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 700 "parser.y"
    {
			label1 = generate_label_code();
			temp_quad = create_quad(IF_NOTEQ, (yyvsp[(1) - (2)].value), TRUE_EXPR, label1, -1, alpha_yylineno);
			
			insert_after_quad((yyvsp[(1) - (2)].value)->quad, temp_quad);
			insert_quad(label1->quad);
			
			(yyval.value) = create_expr(NIL_E, NULL);
			(yyval.value)->quad = label1->quad;
		}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 710 "parser.y"
    {
			label1 = generate_label_code();
			
			temp_quad = create_quad(IF_NOTEQ, (yyvsp[(1) - (4)].value), TRUE_EXPR, label1, -1, alpha_yylineno);
			insert_after_quad((yyvsp[(1) - (4)].value)->quad, temp_quad);
			
			insert_after_quad((yyvsp[(3) - (4)].value)->quad, label1->quad);

			label2 = generate_label_code();
			insert_quad(label2->quad);
			
			temp_quad = create_quad(JUMP, NULL, NULL, label2, -1, alpha_yylineno);
			
			insert_before_quad(label1->quad, temp_quad);
				
			(yyval.value) = create_expr(NIL_E, NULL);
			(yyval.value)->quad = label2->quad;	
		}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 731 "parser.y"
    { 
			(yyval.value) = (yyvsp[(3) - (4)].value);
			if((yyvsp[(3) - (4)].value)->quad == NULL){
				(yyval.value)->quad = get_last_quad();
				//print_info("=============> %p", $$->quad);
				//print_quad($$->quad);
			}
			
		}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 743 "parser.y"
    {
			(yyval.value) = create_expr(NIL_E, NULL);
			(yyval.value)->quad = get_last_quad();
		}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 750 "parser.y"
    {
				label1 = generate_label_code(); // while start
				label2 = generate_label_code(); // stmt end
				push_loop(get_last_quad(), label1, label2);
		}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 754 "parser.y"
    { loop_flag++; }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 755 "parser.y"
    {
				loop_flag--;
				log("while ( expr ) stmt -> whilestmt");
				temp_loop = pop_loop();
				
				label1 = temp_loop->start_label; // while start
				label2 = temp_loop->end_label; // stmt end

				temp_quad = create_quad(IF_NOTEQ, (yyvsp[(4) - (7)].value), TRUE_EXPR, label2, -1, alpha_yylineno);
				
				if((yyvsp[(4) - (7)].value)->quad != NULL){
					insert_after_quad((yyvsp[(4) - (7)].value)->quad, temp_quad);
				}else{
					insert_after_quad(temp_loop->previous_quad, temp_quad);
				}

				insert_after_quad(temp_loop->previous_quad, label1->quad);
				
				temp_quad = create_quad(JUMP, NULL, NULL, label1, -1, alpha_yylineno);
				insert_after_quad(get_last_quad(), temp_quad);
				insert_after_quad(get_last_quad(), label2->quad);
				
				free(temp_loop);
				
				(yyval.value) = label2;
				
  		}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 785 "parser.y"
    {
		
				label1 = generate_label_code(); // while start
				label2 = generate_label_code(); // stmt end
				push_loop(get_last_quad(), label1, label2);
				
				label4 = generate_label_code();
				
				label3 = generate_label_code();
				insert_quad(label3->quad);
		}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 795 "parser.y"
    {
				temp_quad = create_quad(IF_NOTEQ, (yyvsp[(6) - (7)].value), TRUE_EXPR, peek_loop()->end_label, -1, alpha_yylineno);
				insert_quad(temp_quad);
				temp_quad = create_quad(IF_EQ, (yyvsp[(6) - (7)].value), TRUE_EXPR, label4, -1, alpha_yylineno);
				insert_quad(temp_quad);
				
				insert_quad(peek_loop()->start_label->quad);
		}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 802 "parser.y"
    {
				temp_quad = create_quad(JUMP, NULL, NULL, label3, -1, alpha_yylineno);
				insert_quad(temp_quad);
		
				insert_quad(label4->quad);				
		loop_flag++;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 808 "parser.y"
    { 
			loop_flag--; log("for ( elist ; expr ; elist ) stmt -> forstmt");

			temp_quad = create_quad(JUMP, NULL, NULL, peek_loop()->start_label, -1, alpha_yylineno);
			insert_quad(temp_quad);
			
			insert_quad(peek_loop()->end_label->quad);
			pop_loop();
		}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 820 "parser.y"
    {
  			log("return ; -> returnstmt");
			if(peek() == NULL){
				print_err("RETURN without a function.");
  			}
			temp_quad = create_quad(RET, NULL, NULL, NULL, -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 828 "parser.y"
    {
  			log("return expr ; -> return stmt");
			if(peek() == NULL){
				print_err("RETURN without a function.");
  			}
			temp_quad = create_quad(RET, NULL, NULL, (yyvsp[(2) - (3)].value), -1, alpha_yylineno);
			insert_quad(temp_quad);
		}
    break;



/* Line 1455 of yacc.c  */
#line 3008 "parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 838 "parser.y"


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


	


