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
%token DOT
%token CLASS_KEYWORD PUBLIC_KEYWORD STATIC_KEYWORD VOID_KEYWORD EXTENDS_KEYWORD RETURN_KEYWORD INT_KEYWORD BOOL_KEYWORD IF_KEYWORD WHILE_KEYWORD TRUE_KEYWORD FALSE_KEYWORD THIS_KEYWORD NEW_KEYWORD
%token SEMICOLON

%right COMMA
%right ASSIGN
%left BINARY_AND
%left LESS
%left EXCLAMATION_MARK
%left PLUS MINUS
%left MULTIPLY
%token LEFT_CURLY_BRACE RIGHT_CURLY_BRACE LEFT_ROUND_BRACE RIGHT_ROUND_BRACE LEFT_SQUARE_BRACE RIGHT_SQUARE_BRACE

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
        std::cout << @1.first_column << @1.first_line << @1.last_column << @1.last_line << std:: endl;
    }
    | exp PLUS exp {
        $$ = $1 + $3;
    }
    | exp MINUS exp {
        $$ = $1 - $3;
    }
    | exp MULTIPLY exp {
        $$ = $1 * $3;
    }
;

%%

extern void yyerror( char const* msg)
{
    std::cout << "Syntax Error: " << msg << std::endl;
}

/* extern int yylex()
{
    int c;

	while( ( c = getchar() ) == ' ' || c == '\t' )
		++yylloc.last_column;

	yylloc.first_line = yylloc.last_line;
	yylloc.first_column = yylloc.last_column;

	if( isdigit( c ) ) {
		yylval.int_val = c - '0';
		++yylloc.last_column;
		while( isdigit( c = getchar() ) ) {
			++yylloc.last_column;
			yylval.int_val = yylval.int_val * 10 + c - '0';
		}
		ungetc( c, stdin );
		return INTEGER_NUMBER;
	}
	if( c == EOF )
		return 0;

	if( c == '\n' ) {
		++yylloc.last_line;
		yylloc.last_column = 0;
	} else
		++yylloc.last_column;
	return c;
} */
