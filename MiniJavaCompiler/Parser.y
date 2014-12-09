%defines

%{
    #include <iostream>
    #include <cmath>
	#include "GrammaticRules.h"

	extern int yyerror( IProgram* mainProgram, char* msg );
    extern int yylex();
%}
%locations

%code requires {
	#include "GrammaticRules.h"
	#include "GrammaticSymbols.h"
	#include "TerminalSymbols.h"

	#include "PrettyPrinter.h"
}

%parse-param {IProgram* &mainProgram}

%union {
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
}


%token <int_val> INTEGER_NUMBER
%token <int_val> TRUE_KEYWORD
%token <int_val> FALSE_KEYWORD
%token <string_val> IDENTIFIER

%type <Program> Program
%type <MainClassDeclaration> MainClassDeclaration

%type <ClassDeclaration> ClassDeclaration
%type <ClassDeclaration> ClassDeclarationList
%type <Type> Type

%type <VariableDeclaration> VariableDeclaration
%type <VariableDeclarationList> VariableDeclarationList

%type <MethodDeclaration> MethodDeclaration
%type <MethodDeclaration> MethodDeclarationList

%type <Statement> Statement
%type <Statement> StatementList

%type <FormalList> FormalList
%type <FormalList> FormalRestList
%type <FormalList> FormalRest

%type <Expression> Expression
%type <Expression> ExpressionList
%type <Expression> ExpressionRest
%type <Expression> ExpressionRestList

%token CLASS_KEYWORD PUBLIC_KEYWORD STATIC_KEYWORD VOID_KEYWORD EXTENDS_KEYWORD RETURN_KEYWORD INT_KEYWORD BOOLEAN_KEYWORD STRING_KEYWORD IF_KEYWORD ELSE_KEYWORD WHILE_KEYWORD THIS_KEYWORD NEW_KEYWORD PRINTLN_KEYWORD LENGTH_KEYWORD MAIN_KEYWORD SYSTEM_KEYWORD OUT_KEYWORD
%token ';'

%right ','
%right '.'
%right '='
%left BINARY_AND
%left '<'
%left '!'
%left '+' '-'
%left '*'
%token '{' '}' '(' ')' '[' ']'

%start Program

%%

Program:
	MainClassDeclaration ClassDeclarationList {
		mainProgram = $$ = new CProgram($1, $2);
	}

MainClassDeclaration:
	CLASS_KEYWORD IDENTIFIER '{' PUBLIC_KEYWORD STATIC_KEYWORD VOID_KEYWORD MAIN_KEYWORD '(' STRING_KEYWORD '[' ']' IDENTIFIER ')' '{' Statement '}' '}' {
		$$ = new CMainClassDeclaration(new CIdentifier($2), new CIdentifier($12), $15);
	}

ClassDeclarationList:
	/* empty */ {
		$$ = NULL;
	}
	| ClassDeclaration ClassDeclarationList {
		$$ = new CClassDeclarationList($1, $2);
	}

ClassDeclaration:
	CLASS_KEYWORD IDENTIFIER '{'  VariableDeclarationList MethodDeclarationList '}' {
		$$ = new CClassDeclaration(new CIdentifier($2), $4, $5);
	}
	| CLASS_KEYWORD IDENTIFIER EXTENDS_KEYWORD IDENTIFIER '{'  VariableDeclarationList MethodDeclarationList '}' {
		$$ = new CClassExtendsDeclaration(new CIdentifier($2), new CIdentifier($4), $6, $7);
	}

VariableDeclarationList:
	/* empty */ {
		$$ = NULL;
	}
	| VariableDeclarationList VariableDeclaration {
		$$ = new CVariableDeclarationList($2, $1);
	}

VariableDeclaration:
	Type IDENTIFIER ';' {
		$$ = new CVariableDeclaration($1, new CIdentifier($2));		
	}

MethodDeclarationList:
	/* empty */ {
		$$ = NULL;
	}
	| MethodDeclaration MethodDeclarationList {
		$$ = new CMethodDeclarationList($1, $2);
	}

MethodDeclaration:
	PUBLIC_KEYWORD Type IDENTIFIER '(' FormalList ')' '{' VariableDeclarationList StatementList RETURN_KEYWORD Expression ';' '}' {
		$$ = new CMethodDeclaration($2, new CIdentifier($3), $5, $8, $9, $11);
	}

FormalList:
	/* empty */ {
		$$ = NULL;
	}
	| Type IDENTIFIER FormalRestList {
		$$ = new CFormalRestList(new CFormalList($1, new CIdentifier($2)), $3);
	}


FormalRestList:
	/* empty */ {
		$$ = NULL;
	}
	| FormalRest FormalRestList {
		$$ = new CFormalRestList($1, $2);
	}

FormalRest:
	',' Type IDENTIFIER {
		$$ = new CFormalList($2, new CIdentifier($3));
	}

Type:
	INT_KEYWORD '[' ']' {
		$$ = new CBuiltInType(TBuiltInType::BT_INTEGER_ARRAY);
	}
	| BOOLEAN_KEYWORD {
		$$ = new CBuiltInType(TBuiltInType::BT_BOOLEAN);
	}
	| INT_KEYWORD {
		$$ = new CBuiltInType(TBuiltInType::BT_INTEGER);
	}
	| IDENTIFIER {
		$$ = new CUserType(new CIdentifier($1));
	}

StatementList:
	/* empty */ {
		$$ = NULL;
	}
	| Statement StatementList {
		$$ = new CStatementList($1, $2);
	}

Statement:
	'{' StatementList '}' {
		$$ = new CStatementBlock($2);
	}
	| IF_KEYWORD '(' Expression ')' Statement ELSE_KEYWORD Statement {
		$$ = new CIfStatement($3, $5, $7);
	}
	| WHILE_KEYWORD '(' Expression ')' Statement {
		$$ = new CWhileStatement($3, $5);
	}
	| SYSTEM_KEYWORD '.' OUT_KEYWORD '.' PRINTLN_KEYWORD '(' Expression ')' ';' {
		$$ = new CPrintStatement($7);
	}
	| IDENTIFIER '=' Expression ';' {
		$$ = new CAssignmentStatement(new CIdentifier($1), $3);
	}
	| IDENTIFIER '[' Expression ']' '=' Expression ';' {
		$$ = new CArrayElementAssignmentStatement(new CIdentifier($1), $3, $6);
	}

Expression:
	Expression BINARY_AND Expression {
		$$ = new CBinaryOperatorExpression($1, $3, TBinaryOperator::BO_LOGICAL_AND);
	}
	| Expression '<' Expression {
		$$ = new CBinaryOperatorExpression($1, $3, TBinaryOperator::BO_LESS);
	}
	| Expression '+' Expression {
		$$ = new CBinaryOperatorExpression($1, $3, TBinaryOperator::BO_PLUS);
	} 
	| Expression '-' Expression {
		$$ = new CBinaryOperatorExpression($1, $3, TBinaryOperator::BO_MINUS);
	}
	| Expression '*' Expression {
		$$ = new CBinaryOperatorExpression($1, $3, TBinaryOperator::BO_MULTIPLY);
	}
	| Expression '.' LENGTH_KEYWORD {
		$$ = new CLengthExpression($1);	
	}
	| Expression '.' IDENTIFIER '(' ExpressionList ')' {
		$$ = new CMethodCallExpression($1, new CIdentifier($3), $5);
	}
	| INTEGER_NUMBER {
		$$ = new CIntegerOrBooleanExpression($1, VT_INTEGER);
	}
	| TRUE_KEYWORD {
		$$ = new CIntegerOrBooleanExpression($1, VT_BOOLEAN);
	}
	| FALSE_KEYWORD {
		$$ = new CIntegerOrBooleanExpression($1, VT_BOOLEAN);
	}
	| IDENTIFIER {
		$$ = new CIdentifierExpression(new CIdentifier($1));
	}
	| THIS_KEYWORD {
		$$ = new CThisExpression();
	}
	| NEW_KEYWORD INT_KEYWORD '[' Expression ']' {
		$$ = new CNewIntegerArrayExpression($4);	
	}
	| NEW_KEYWORD IDENTIFIER '(' ')' {
		$$ = new CNewObjectExpression(new CIdentifier($2));	
	}
	| '!' Expression  {
		$$ = new CNegationExpression($2);
	}
	| '(' Expression ')' {
		$$ = new CParenthesesExpression($2);
	}

ExpressionList:
	/* empty */ {
		$$ = NULL;
	}
	| Expression ExpressionRestList {
		$$ = new CExpressionList($1, $2);
	}

ExpressionRestList:
	/* empty */ {
		$$ = NULL;
	}
	| ExpressionRest ExpressionRestList {
		$$ = new CExpressionList($1, $2);
	}

ExpressionRest:
	',' Expression {
		$$ = $2;
	}
;

%%

extern int yyerror( IProgram* mainProgram, char* msg )
{
    std::cout << "Syntax error at line " << yylloc.first_line << ", column " << yylloc.first_column << ": " << msg << std::endl;
	return -1;
}