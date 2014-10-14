%defines

%{
    #include <iostream>
    #include <cmath>


	extern void yyerror( char const* msg);
    extern int yylex();
%}
%locations


%union {
	int int_val;
}


%token <int_val> INTEGER_NUMBER
%type <int_val> exp
%token IDENTIFIER
%token CLASS_KEYWORD PUBLIC_KEYWORD STATIC_KEYWORD VOID_KEYWORD EXTENDS_KEYWORD RETURN_KEYWORD INT_KEYWORD BOOL_KEYWORD IF_KEYWORD WHILE_KEYWORD TRUE_KEYWORD FALSE_KEYWORD THIS_KEYWORD NEW_KEYWORD
%token ';'

%right ','
%right '='
%left BINARY_AND
%left '<'
%left '!'
%left '+' '-'
%left '*'
%token '{' '}' '(' ')' '[' ']'

%start program

%%

program:
    /* empty */
    | program exp '\n' {
        std::cout << $2 << std::endl;
    }

exp:
    INTEGER_NUMBER {
        $$ = $1;
        std::cout << @1.first_column << ' ' << @1.first_line << ' ' << @1.last_column << ' ' << @1.last_line << std:: endl;
    }
    | exp '+' exp {
        $$ = $1 + $3;
    }
    | exp '-' exp {
        $$ = $1 - $3;
    }
    | exp '*' exp {
        $$ = $1 * $3;
    }
;

%%

extern void yyerror( char const* msg)
{
    std::cout << "Syntax Error: " << msg << std::endl;
}
