/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2058 of yacc.c  */
#line 13 "Parser.y"

	#include "GrammaticRules.h"
	#include "GrammaticSymbols.h"
	#include "TerminalSymbols.h"

	#include "PrettyPrinter.h"


/* Line 2058 of yacc.c  */
#line 55 "Parser.hpp"

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
/* Line 2058 of yacc.c  */
#line 23 "Parser.y"

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


/* Line 2058 of yacc.c  */
#line 119 "Parser.hpp"
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
