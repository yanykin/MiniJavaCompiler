%defines

%{
    #include <iostream>
    #include <cmath>

	extern int yyerror( char* msg );
    extern int yylex();
%}
%locations


%union {
	int int_val;
}


%token <int_val> INTEGER_NUMBER
%type <int_val> Expression
%token IDENTIFIER
%token CLASS_KEYWORD PUBLIC_KEYWORD STATIC_KEYWORD VOID_KEYWORD EXTENDS_KEYWORD RETURN_KEYWORD INT_KEYWORD BOOLEAN_KEYWORD STRING_KEYWORD IF_KEYWORD ELSE_KEYWORD WHILE_KEYWORD TRUE_KEYWORD FALSE_KEYWORD THIS_KEYWORD NEW_KEYWORD PRINTLN_KEYWORD LENGTH_KEYWORD MAIN_KEYWORD SYSTEM_KEYWORD OUT_KEYWORD
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
	MainClassDeclaration ClassDeclarationList

MainClassDeclaration:
	CLASS_KEYWORD IDENTIFIER '{' PUBLIC_KEYWORD STATIC_KEYWORD VOID_KEYWORD MAIN_KEYWORD '(' STRING_KEYWORD '[' ']' IDENTIFIER ')' '{' Statement '}' '}'

ClassDeclarationList:
	/* empty */
	| ClassDeclaration ClassDeclarationList

ClassExtends:
	/* empty */
	| EXTENDS_KEYWORD IDENTIFIER

ClassDeclaration:
	CLASS_KEYWORD IDENTIFIER ClassExtends '{'  VariableDeclarationList MethodDeclarationList '}'

VariableDeclarationList:
	/* empty */
	| VariableDeclarationList VariableDeclaration

VariableDeclaration:
	Type IDENTIFIER ';'

MethodDeclarationList:
	/* empty */
	| MethodDeclarationList MethodDeclaration

MethodDeclaration:
	PUBLIC_KEYWORD Type IDENTIFIER '(' FormalList ')' '{' VariableDeclarationList StatementList RETURN_KEYWORD Expression ';' '}'

FormalList:
	/* empty */
	| Type IDENTIFIER FormalRestList

FormalRestList:
	/* empty */
	| FormalRestList FormalRest

FormalRest:
	',' Type IDENTIFIER

Type:
	INT_KEYWORD '[' ']'
	| BOOLEAN_KEYWORD
	| INT_KEYWORD
	| IDENTIFIER

StatementList:
	/* empty */
	| Statement StatementList

Statement:
	'{' StatementList '}'
	| IF_KEYWORD '(' Expression ')' Statement ELSE_KEYWORD Statement
	| WHILE_KEYWORD '(' Expression ')' Statement
	| SYSTEM_KEYWORD '.' OUT_KEYWORD '.' PRINTLN_KEYWORD '(' Expression ')' ';'
	| IDENTIFIER '=' Expression ';'
	| IDENTIFIER '[' Expression ']' '=' Expression ';'

Expression:
	Expression BINARY_AND Expression
	| Expression '<' Expression
	| Expression '+' Expression
	| Expression '-' Expression
	| Expression '*' Expression
	| Expression MethodExpression
	| INTEGER_NUMBER
	| TRUE_KEYWORD
	| FALSE_KEYWORD
	| IDENTIFIER
	| THIS_KEYWORD
	| NEW_KEYWORD INT_KEYWORD '[' Expression ']'
	| NEW_KEYWORD IDENTIFIER '(' ')'
	| '!' Expression
	| '(' Expression ')'

MethodExpression:
	'.' LENGTH_KEYWORD
	| '.' IDENTIFIER '(' ExpressionList ')'

ExpressionList:
	/* empty */
	| Expression ExpressionRestList

ExpressionRestList:
	/* empty */
	| ExpressionRest ExpressionRestList

ExpressionRest:
	',' Expression
;

%%

extern int yyerror( char* msg )
{
    std::cout << "Syntax error at line " << yylloc.first_line << ", column " << yylloc.first_column << ": " << msg << std::endl;
	return -1;
}
