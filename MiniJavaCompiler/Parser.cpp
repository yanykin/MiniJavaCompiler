/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
/* Line 349 of yacc.c  */
#line 13 "Parser.y"

	


/* Line 349 of yacc.c  */
#line 70 "Parser.cpp"



/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 3 "Parser.y"

    #include <iostream>
    #include <cmath>
	#include "GrammaticRules.h"
	#include "CoordinatesHolder.h"
	extern int yyerror( IProgram* mainProgram, char* msg );
    extern int yylex();

/* Line 371 of yacc.c  */
#line 86 "Parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 387 of yacc.c  */
#line 17 "Parser.y"

	#include "GrammaticSymbols.h"
	#include "TerminalSymbols.h"

	class CCoordinatesHolder;


/* Line 387 of yacc.c  */
#line 126 "Parser.cpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER_NUMBER = 258,
     TRUE_KEYWORD = 259,
     FALSE_KEYWORD = 260,
     IDENTIFIER = 261,
     CLASS_KEYWORD = 262,
     PUBLIC_KEYWORD = 263,
     STATIC_KEYWORD = 264,
     VOID_KEYWORD = 265,
     EXTENDS_KEYWORD = 266,
     RETURN_KEYWORD = 267,
     INT_KEYWORD = 268,
     BOOLEAN_KEYWORD = 269,
     STRING_KEYWORD = 270,
     IF_KEYWORD = 271,
     ELSE_KEYWORD = 272,
     WHILE_KEYWORD = 273,
     THIS_KEYWORD = 274,
     NEW_KEYWORD = 275,
     PRINTLN_KEYWORD = 276,
     LENGTH_KEYWORD = 277,
     MAIN_KEYWORD = 278,
     SYSTEM_KEYWORD = 279,
     OUT_KEYWORD = 280,
     BINARY_AND = 281
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 26 "Parser.y"

	int int_val;
	char* string_val;

	IProgram* Program;
	IMainClassDeclaration* MainClassDeclaration;
	IStatement* Statement;
	CIdentifier* Identifier;

	IVariableDeclaration* VariableDeclaration;
	CVariableDeclarationList* VariableDeclarationList;

	IClassDeclaration* ClassDeclaration;
	IMethodDeclaration* MethodDeclaration;

	IFormalList* FormalList;

	IExpression* Expression;

	IType* Type;


/* Line 387 of yacc.c  */
#line 190 "Parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (IProgram* &mainProgram);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 231 "Parser.cpp"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   215

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNRULES -- Number of states.  */
#define YYNSTATES  145

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,     2,     2,     2,     2,     2,
      38,    39,    34,    32,    27,    33,    35,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
      30,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      25,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    24,    25,    28,    35,    44,    45,
      48,    52,    53,    56,    70,    71,    75,    76,    79,    83,
      87,    89,    91,    93,    94,    97,   101,   109,   115,   125,
     130,   138,   142,   146,   150,   154,   158,   162,   169,   171,
     173,   175,   177,   179,   185,   190,   193,   197,   198,   201,
     202,   205
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    44,    45,    -1,     7,     6,    36,     8,
       9,    10,    23,    38,    15,    40,    41,     6,    39,    36,
      56,    37,    37,    -1,    -1,    46,    45,    -1,     7,     6,
      36,    47,    49,    37,    -1,     7,     6,    11,     6,    36,
      47,    49,    37,    -1,    -1,    47,    48,    -1,    54,     6,
      26,    -1,    -1,    50,    49,    -1,     8,    54,     6,    38,
      51,    39,    36,    47,    55,    12,    57,    26,    37,    -1,
      -1,    54,     6,    52,    -1,    -1,    53,    52,    -1,    27,
      54,     6,    -1,    13,    40,    41,    -1,    14,    -1,    13,
      -1,     6,    -1,    -1,    56,    55,    -1,    36,    55,    37,
      -1,    16,    38,    57,    39,    56,    17,    56,    -1,    18,
      38,    57,    39,    56,    -1,    24,    35,    25,    35,    21,
      38,    57,    39,    26,    -1,     6,    28,    57,    26,    -1,
       6,    40,    57,    41,    28,    57,    26,    -1,    57,    29,
      57,    -1,    57,    30,    57,    -1,    57,    32,    57,    -1,
      57,    33,    57,    -1,    57,    34,    57,    -1,    57,    35,
      22,    -1,    57,    35,     6,    38,    58,    39,    -1,     3,
      -1,     4,    -1,     5,    -1,     6,    -1,    19,    -1,    20,
      13,    40,    57,    41,    -1,    20,     6,    38,    39,    -1,
      31,    57,    -1,    38,    57,    39,    -1,    -1,    57,    59,
      -1,    -1,    60,    59,    -1,    27,    57,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,   101,   106,   109,   114,   117,   122,   125,
     130,   135,   138,   143,   148,   151,   157,   160,   165,   170,
     173,   176,   179,   184,   187,   192,   195,   198,   201,   204,
     207,   212,   215,   218,   221,   224,   227,   230,   233,   236,
     239,   242,   245,   248,   251,   254,   257,   262,   265,   270,
     273,   278
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER_NUMBER", "TRUE_KEYWORD",
  "FALSE_KEYWORD", "IDENTIFIER", "CLASS_KEYWORD", "PUBLIC_KEYWORD",
  "STATIC_KEYWORD", "VOID_KEYWORD", "EXTENDS_KEYWORD", "RETURN_KEYWORD",
  "INT_KEYWORD", "BOOLEAN_KEYWORD", "STRING_KEYWORD", "IF_KEYWORD",
  "ELSE_KEYWORD", "WHILE_KEYWORD", "THIS_KEYWORD", "NEW_KEYWORD",
  "PRINTLN_KEYWORD", "LENGTH_KEYWORD", "MAIN_KEYWORD", "SYSTEM_KEYWORD",
  "OUT_KEYWORD", "';'", "','", "'='", "BINARY_AND", "'<'", "'!'", "'+'",
  "'-'", "'*'", "'.'", "'{'", "'}'", "'('", "')'", "'['", "']'", "$accept",
  "Program", "MainClassDeclaration", "ClassDeclarationList",
  "ClassDeclaration", "VariableDeclarationList", "VariableDeclaration",
  "MethodDeclarationList", "MethodDeclaration", "FormalList",
  "FormalRestList", "FormalRest", "Type", "StatementList", "Statement",
  "Expression", "ExpressionList", "ExpressionRestList", "ExpressionRest", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    59,    44,    61,   281,
      60,    33,    43,    45,    42,    46,   123,   125,    40,    41,
      91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    45,    45,    46,    46,    47,    47,
      48,    49,    49,    50,    51,    51,    52,    52,    53,    54,
      54,    54,    54,    55,    55,    56,    56,    56,    56,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    58,    58,    59,
      59,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,    17,     0,     2,     6,     8,     0,     2,
       3,     0,     2,    13,     0,     3,     0,     2,     3,     3,
       1,     1,     1,     0,     2,     3,     7,     5,     9,     4,
       7,     3,     3,     3,     3,     3,     3,     6,     1,     1,
       1,     1,     1,     5,     4,     2,     3,     0,     2,     0,
       2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     0,     1,     0,     2,     4,     0,
       0,     5,     0,     0,     8,     0,     0,    11,     0,     8,
      22,     0,    21,    20,     9,     0,    11,     0,     0,    11,
       0,     0,     6,    12,     0,     0,     0,     0,    19,    10,
       0,     7,    14,     0,     0,     0,     0,     0,    16,     0,
       8,     0,    15,    16,     0,    23,     0,    17,     0,    22,
       0,     0,     0,    23,     0,    23,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    24,     0,    38,    39,
      40,    41,    42,     0,     0,     0,     0,     0,     0,     0,
       0,    25,     0,     3,     0,     0,    45,     0,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,    31,    32,    33,    34,    35,     0,    36,
       0,     0,    27,     0,    13,    44,     0,    47,     0,     0,
       0,    43,    49,     0,    30,    26,     0,     0,    48,    49,
      37,     0,    51,    50,    28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     8,    17,    24,    25,    26,    44,
      52,    53,    27,    64,    65,    86,   133,   138,   139
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -70
static const yytype_int16 yypact[] =
{
      15,    21,    40,    43,    10,   -70,    48,   -70,    43,    52,
       2,   -70,    58,    74,   -70,    71,    46,     6,    67,   -70,
     -70,    56,    51,   -70,   -70,    55,    92,   102,    78,     6,
     118,    85,   -70,   -70,   104,   121,   100,   108,   -70,   -70,
     107,   -70,    56,   115,   101,   144,   153,   130,   154,   133,
     -70,    56,   -70,   154,   146,    39,   177,   -70,    23,    16,
     147,   148,   149,    23,   175,    23,   -70,    16,   151,     5,
       5,     5,     5,   164,   155,     5,   -70,   156,   -70,   -70,
     -70,   -70,   -70,    59,     5,     5,    99,    44,    64,    72,
     159,   -70,   109,   -70,   152,   157,   145,    80,   -70,     5,
       5,     5,     5,     5,    -1,   163,    23,    23,   174,   161,
     160,     5,   -70,   141,   145,   -17,   -17,   165,   158,   -70,
       5,   184,   -70,   166,   -70,   -70,    54,     5,   119,    23,
       5,   -70,   128,   167,   -70,   -70,    88,     5,   -70,   176,
     -70,   179,   135,   -70,   -70
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   194,   -70,   -15,   -70,    -3,   -70,   -70,
     162,   -70,   -14,     1,   -58,   -69,   -70,    68,   -70
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      68,    87,    88,    89,    29,   118,    92,    30,    78,    79,
      80,    81,    20,    13,    21,    96,    97,   103,   104,    22,
      23,   119,     1,    33,    82,    83,    36,     4,    45,    67,
     113,   114,   115,   116,   117,    55,    84,    56,    14,    60,
       5,    61,   126,    85,    69,    59,     9,    62,   121,   122,
       6,   128,    22,    23,    10,    60,    70,    61,   132,    63,
      12,   136,    20,    62,    74,    94,    76,    15,   142,    22,
      23,   135,    95,    99,   100,    63,   101,   102,   103,   104,
      16,    18,    19,    99,   100,   105,   101,   102,   103,   104,
      28,    31,    32,    99,   100,   131,   101,   102,   103,   104,
      21,    99,   100,   106,   101,   102,   103,   104,    34,    99,
     100,   107,   101,   102,   103,   104,    35,    99,   100,   112,
     101,   102,   103,   104,    37,    98,    38,   141,    99,   100,
      39,   101,   102,   103,   104,   109,    40,    41,    99,   100,
      47,   101,   102,   103,   104,   134,    42,    43,    99,   100,
      48,   101,   102,   103,   104,   137,    46,    99,   100,    49,
     101,   102,   103,   104,    99,   100,    50,   101,   102,   103,
     104,   100,    54,   101,   102,   103,   104,   101,   102,   103,
     104,    51,    58,    66,    73,    71,    72,    75,    77,    90,
     110,   120,    91,    93,   108,   123,   127,   111,   124,   125,
     104,   129,    11,   137,   130,   144,   140,   143,     0,     0,
       0,     0,     0,     0,     0,    57
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-70)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      58,    70,    71,    72,    19,     6,    75,    21,     3,     4,
       5,     6,     6,    11,     8,    84,    85,    34,    35,    13,
      14,    22,     7,    26,    19,    20,    29,     6,    42,     6,
      99,   100,   101,   102,   103,    50,    31,    51,    36,    16,
       0,    18,   111,    38,    28,     6,    36,    24,   106,   107,
       7,   120,    13,    14,     6,    16,    40,    18,   127,    36,
       8,   130,     6,    24,    63,     6,    65,     9,   137,    13,
      14,   129,    13,    29,    30,    36,    32,    33,    34,    35,
       6,    10,    36,    29,    30,    41,    32,    33,    34,    35,
      23,    40,    37,    29,    30,    41,    32,    33,    34,    35,
       8,    29,    30,    39,    32,    33,    34,    35,     6,    29,
      30,    39,    32,    33,    34,    35,    38,    29,    30,    39,
      32,    33,    34,    35,     6,    26,    41,    39,    29,    30,
      26,    32,    33,    34,    35,    26,    15,    37,    29,    30,
      39,    32,    33,    34,    35,    26,    38,    40,    29,    30,
       6,    32,    33,    34,    35,    27,    41,    29,    30,     6,
      32,    33,    34,    35,    29,    30,    36,    32,    33,    34,
      35,    30,    39,    32,    33,    34,    35,    32,    33,    34,
      35,    27,    36,     6,    35,    38,    38,    12,    37,    25,
      38,    28,    37,    37,    35,    21,    38,    40,    37,    39,
      35,    17,     8,    27,    38,    26,    39,   139,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    43,    44,     6,     0,     7,    45,    46,    36,
       6,    45,     8,    11,    36,     9,     6,    47,    10,    36,
       6,     8,    13,    14,    48,    49,    50,    54,    23,    47,
      54,    40,    37,    49,     6,    38,    49,     6,    41,    26,
      15,    37,    38,    40,    51,    54,    41,    39,     6,     6,
      36,    27,    52,    53,    39,    47,    54,    52,    36,     6,
      16,    18,    24,    36,    55,    56,     6,     6,    56,    28,
      40,    38,    38,    35,    55,    12,    55,    37,     3,     4,
       5,     6,    19,    20,    31,    38,    57,    57,    57,    57,
      25,    37,    57,    37,     6,    13,    57,    57,    26,    29,
      30,    32,    33,    34,    35,    41,    39,    39,    35,    26,
      38,    40,    39,    57,    57,    57,    57,    57,     6,    22,
      28,    56,    56,    21,    37,    39,    57,    38,    57,    17,
      38,    41,    57,    58,    26,    56,    57,    27,    59,    60,
      39,    39,    57,    59,    26
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (mainProgram, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

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
		  Type, Value, Location, mainProgram); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, IProgram* &mainProgram)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, mainProgram)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    IProgram* &mainProgram;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (mainProgram);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, IProgram* &mainProgram)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, mainProgram)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    IProgram* &mainProgram;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, mainProgram);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, IProgram* &mainProgram)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, mainProgram)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    IProgram* &mainProgram;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , mainProgram);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, mainProgram); \
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, IProgram* &mainProgram)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, mainProgram)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    IProgram* &mainProgram;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (mainProgram);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

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
yyparse (IProgram* &mainProgram)
#else
int
yyparse (mainProgram)
    IProgram* &mainProgram;
#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 96 "Parser.y"
    {
		mainProgram = (yyval.Program) = new CProgram((yyloc), (yyvsp[(1) - (2)].MainClassDeclaration), (yyvsp[(2) - (2)].ClassDeclaration));
	}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 101 "Parser.y"
    {
		(yyval.MainClassDeclaration) = new CMainClassDeclaration((yyloc), new CIdentifier((yyvsp[(2) - (17)].string_val)), new CIdentifier((yyvsp[(12) - (17)].string_val)), (yyvsp[(15) - (17)].Statement));
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 106 "Parser.y"
    {
		(yyval.ClassDeclaration) = NULL;
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 109 "Parser.y"
    {
		(yyval.ClassDeclaration) = new CClassDeclarationList((yyloc), (yyvsp[(1) - (2)].ClassDeclaration), (yyvsp[(2) - (2)].ClassDeclaration));
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 114 "Parser.y"
    {
		(yyval.ClassDeclaration) = new CClassDeclaration((yyloc), new CIdentifier((yyvsp[(2) - (6)].string_val)), (yyvsp[(4) - (6)].VariableDeclarationList), (yyvsp[(5) - (6)].MethodDeclaration));
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 117 "Parser.y"
    {
		(yyval.ClassDeclaration) = new CClassExtendsDeclaration((yyloc), new CIdentifier((yyvsp[(2) - (8)].string_val)), new CIdentifier((yyvsp[(4) - (8)].string_val)), (yyvsp[(6) - (8)].VariableDeclarationList), (yyvsp[(7) - (8)].MethodDeclaration));
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 122 "Parser.y"
    {
		(yyval.VariableDeclarationList) = NULL;
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 125 "Parser.y"
    {
		(yyval.VariableDeclarationList) = new CVariableDeclarationList((yyloc), (yyvsp[(2) - (2)].VariableDeclaration), (yyvsp[(1) - (2)].VariableDeclarationList));
	}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 130 "Parser.y"
    {
		(yyval.VariableDeclaration) = new CVariableDeclaration((yyloc), (yyvsp[(1) - (3)].Type), new CIdentifier((yyvsp[(2) - (3)].string_val)));		
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 135 "Parser.y"
    {
		(yyval.MethodDeclaration) = NULL;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 138 "Parser.y"
    {
		(yyval.MethodDeclaration) = new CMethodDeclarationList((yyloc), (yyvsp[(1) - (2)].MethodDeclaration), (yyvsp[(2) - (2)].MethodDeclaration));
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 143 "Parser.y"
    {
		(yyval.MethodDeclaration) = new CMethodDeclaration((yyloc), (yyvsp[(2) - (13)].Type), new CIdentifier((yyvsp[(3) - (13)].string_val)), (yyvsp[(5) - (13)].FormalList), (yyvsp[(8) - (13)].VariableDeclarationList), (yyvsp[(9) - (13)].Statement), (yyvsp[(11) - (13)].Expression));
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 148 "Parser.y"
    {
		(yyval.FormalList) = NULL;
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 151 "Parser.y"
    {
		(yyval.FormalList) = new CFormalRestList((yyloc), new CFormalList((yyloc), (yyvsp[(1) - (3)].Type), new CIdentifier((yyvsp[(2) - (3)].string_val))), (yyvsp[(3) - (3)].FormalList));
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 157 "Parser.y"
    {
		(yyval.FormalList) = NULL;
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 160 "Parser.y"
    {
		(yyval.FormalList) = new CFormalRestList((yyloc), (yyvsp[(1) - (2)].FormalList), (yyvsp[(2) - (2)].FormalList));
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 165 "Parser.y"
    {
		(yyval.FormalList) = new CFormalList((yyloc), (yyvsp[(2) - (3)].Type), new CIdentifier((yyvsp[(3) - (3)].string_val)));
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 170 "Parser.y"
    {
		(yyval.Type) = new CBuiltInType((yyloc), TBuiltInType::BT_INTEGER_ARRAY);
	}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 173 "Parser.y"
    {
		(yyval.Type) = new CBuiltInType((yyloc), TBuiltInType::BT_BOOLEAN);
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 176 "Parser.y"
    {
		(yyval.Type) = new CBuiltInType((yyloc), TBuiltInType::BT_INTEGER);
	}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 179 "Parser.y"
    {
		(yyval.Type) = new CUserType((yyloc), new CIdentifier((yyvsp[(1) - (1)].string_val)));
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 184 "Parser.y"
    {
		(yyval.Statement) = NULL;
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 187 "Parser.y"
    {
		(yyval.Statement) = new CStatementList((yyloc), (yyvsp[(1) - (2)].Statement), (yyvsp[(2) - (2)].Statement));
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 192 "Parser.y"
    {
		(yyval.Statement) = new CStatementBlock((yyloc), (yyvsp[(2) - (3)].Statement));
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 195 "Parser.y"
    {
		(yyval.Statement) = new CIfStatement((yyloc), (yyvsp[(3) - (7)].Expression), (yyvsp[(5) - (7)].Statement), (yyvsp[(7) - (7)].Statement));
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 198 "Parser.y"
    {
		(yyval.Statement) = new CWhileStatement((yyloc), (yyvsp[(3) - (5)].Expression), (yyvsp[(5) - (5)].Statement));
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 201 "Parser.y"
    {
		(yyval.Statement) = new CPrintStatement((yyloc), (yyvsp[(7) - (9)].Expression));
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 204 "Parser.y"
    {
		(yyval.Statement) = new CAssignmentStatement((yyloc), new CIdentifier((yyvsp[(1) - (4)].string_val)), (yyvsp[(3) - (4)].Expression));
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 207 "Parser.y"
    {
		(yyval.Statement) = new CArrayElementAssignmentStatement((yyloc), new CIdentifier((yyvsp[(1) - (7)].string_val)), (yyvsp[(3) - (7)].Expression), (yyvsp[(6) - (7)].Expression));
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 212 "Parser.y"
    {
		(yyval.Expression) = new CBinaryOperatorExpression((yyloc), (yyvsp[(1) - (3)].Expression), (yyvsp[(3) - (3)].Expression), TBinaryOperator::BO_LOGICAL_AND);
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 215 "Parser.y"
    {
		(yyval.Expression) = new CBinaryOperatorExpression((yyloc), (yyvsp[(1) - (3)].Expression), (yyvsp[(3) - (3)].Expression), TBinaryOperator::BO_LESS);
	}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 218 "Parser.y"
    {
		(yyval.Expression) = new CBinaryOperatorExpression((yyloc), (yyvsp[(1) - (3)].Expression), (yyvsp[(3) - (3)].Expression), TBinaryOperator::BO_PLUS);
	}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 221 "Parser.y"
    {
		(yyval.Expression) = new CBinaryOperatorExpression((yyloc), (yyvsp[(1) - (3)].Expression), (yyvsp[(3) - (3)].Expression), TBinaryOperator::BO_MINUS);
	}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 224 "Parser.y"
    {
		(yyval.Expression) = new CBinaryOperatorExpression((yyloc), (yyvsp[(1) - (3)].Expression), (yyvsp[(3) - (3)].Expression), TBinaryOperator::BO_MULTIPLY);
	}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 227 "Parser.y"
    {
		(yyval.Expression) = new CLengthExpression((yyloc), (yyvsp[(1) - (3)].Expression));	
	}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 230 "Parser.y"
    {
		(yyval.Expression) = new CMethodCallExpression((yyloc), (yyvsp[(1) - (6)].Expression), new CIdentifier((yyvsp[(3) - (6)].string_val)), (yyvsp[(5) - (6)].Expression));
	}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 233 "Parser.y"
    {
		(yyval.Expression) = new CIntegerOrBooleanExpression((yyloc), (yyvsp[(1) - (1)].int_val), VT_INTEGER);
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 236 "Parser.y"
    {
		(yyval.Expression) = new CIntegerOrBooleanExpression((yyloc), (yyvsp[(1) - (1)].int_val), VT_BOOLEAN);
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 239 "Parser.y"
    {
		(yyval.Expression) = new CIntegerOrBooleanExpression((yyloc), (yyvsp[(1) - (1)].int_val), VT_BOOLEAN);
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 242 "Parser.y"
    {
		(yyval.Expression) = new CIdentifierExpression((yyloc), new CIdentifier((yyvsp[(1) - (1)].string_val)));
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 245 "Parser.y"
    {
		(yyval.Expression) = new CThisExpression((yyloc));
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 248 "Parser.y"
    {
		(yyval.Expression) = new CNewIntegerArrayExpression((yyloc), (yyvsp[(4) - (5)].Expression));	
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 251 "Parser.y"
    {
		(yyval.Expression) = new CNewObjectExpression((yyloc), new CIdentifier((yyvsp[(2) - (4)].string_val)));	
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 254 "Parser.y"
    {
		(yyval.Expression) = new CNegationExpression((yyloc), (yyvsp[(2) - (2)].Expression));
	}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 257 "Parser.y"
    {
		(yyval.Expression) = new CParenthesesExpression((yyloc), (yyvsp[(2) - (3)].Expression));
	}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 262 "Parser.y"
    {
		(yyval.Expression) = NULL;
	}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 265 "Parser.y"
    {
		(yyval.Expression) = new CExpressionList((yyloc), (yyvsp[(1) - (2)].Expression), (yyvsp[(2) - (2)].Expression));
	}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 270 "Parser.y"
    {
		(yyval.Expression) = NULL;
	}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 273 "Parser.y"
    {
		(yyval.Expression) = new CExpressionList((yyloc), (yyvsp[(1) - (2)].Expression), (yyvsp[(2) - (2)].Expression));
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 278 "Parser.y"
    {
		(yyval.Expression) = (yyvsp[(2) - (2)].Expression);
	}
    break;


/* Line 1792 of yacc.c  */
#line 2073 "Parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (mainProgram, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (mainProgram, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc, mainProgram);
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

  yyerror_range[1] = yylsp[1-yylen];
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
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, mainProgram);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (mainProgram, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, mainProgram);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, mainProgram);
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


/* Line 2055 of yacc.c  */
#line 283 "Parser.y"


extern int yyerror( IProgram* mainProgram, char* msg )
{
    std::cout << "Syntax error at line " << yylloc.first_line << ", column " << yylloc.first_column << ": " << msg << std::endl;
	return -1;
}