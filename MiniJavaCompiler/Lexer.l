%option noyywrap

%{ 
	#include <cstdlib>
	#include "Parser.hpp"
	extern int yyparse();
%}
 
 
LEFT_CURLY_BRACE	"{"
RIGHT_CURLY_BRACE	"}"
LEFT_ROUND_BRACE	"("
RIGHT_ROUND_BRACE	")"
LEFT_SQUARE_BRACE	"["
RIGHT_SQUARE_BRACE	"]"

PLUS				"+"
MINUS				"-"
MULTIPLY			"*"
LESS				"<"
ASSIGN				"="
DOT					"\."
SEMICOLON			";"
COMMA				","
EXCLAMATION_MARK	"!"
BINARY_AND			"&&"
 
INTEGER_NUMBER		[0-9]+
WHITESPACE			[ \r\n\t]*

CLASS_KEYWORD		"class"
PUBLIC_KEYWORD		"public"
STATIC_KEYWORD		"static"
VOID_KEYWORD		"void"
EXTENDS_KEYWORD		"extends"
RETURN_KEYWORD		"return"
INT_KEYWORD			"int"
BOOL_KEYWORD		"bool"
IF_KEYWORD			"if"
WHILE_KEYWORD		"while"
TRUE_KEYWORD		"true"
FALSE_KEYWORD		"false"
THIS_KEYWORD		"this"
NEW_KEYWORD			"new"

IDENTIFIER			[a-zA-Z][_0-9A-Za-z]*
 
%%
 
{WHITESPACE} { 
	/* Skip blanks. */
}

{LEFT_CURLY_BRACE} {
	// printf( "LeftCurlyBrace\n" );
	return LEFT_CURLY_BRACE;
}
{RIGHT_CURLY_BRACE} {
	// printf( "RightCurlyBrace\n" );
	return RIGHT_CURLY_BRACE;
}
{LEFT_ROUND_BRACE} {
	// printf( "LeftRoundBrace\n" );
	return LEFT_ROUND_BRACE;
}
{RIGHT_ROUND_BRACE} {
	// printf( "RightRoundBrace\n" );
	return RIGHT_ROUND_BRACE;
}
{LEFT_SQUARE_BRACE} {
	// printf( "LeftSquareBrace\n" );
	return LEFT_SQUARE_BRACE;
}
{RIGHT_SQUARE_BRACE} {
	//printf( "RightSquareBrace\n" );
	return RIGHT_SQUARE_BRACE;
}

{PLUS} {
	//printf( "Plus\n" );
	return PLUS;
}
{MINUS} {
	//printf( "Minus\n" );
	return MINUS;
}
{MULTIPLY} {
	// printf( "Multiply\n" );
	return MULTIPLY;
}
{LESS} {
	// printf( "Less\n" );
	return LESS;
}
{ASSIGN} {
	// printf( "Assign\n" );
	return ASSIGN;
}
{DOT} {
	// printf( "Dot\n" );
	return DOT;
}
{SEMICOLON} {
	// printf( "Semicolon\n" );
	return SEMICOLON;
}
{COMMA} {
	// printf( "Comma\n" );
	return COMMA;
}
{EXCLAMATION_MARK} {
	// printf( "ExclamationMark\n" );
	return EXCLAMATION_MARK;
}
{BINARY_AND} {
	// printf( "BinaryAnd\n" );
	return BINARY_AND;
}
 
{INTEGER_NUMBER} {
	// printf( "Integer(%s)\n", yytext );
	yylval.int_val = atoi(yytext);
	return INTEGER_NUMBER;
}
{WHITESPACE} {
	/* */
}

{CLASS_KEYWORD} {
	// printf( "classKeyword\n" );
	return CLASS_KEYWORD;
}
{STATIC_KEYWORD} {
	// printf( "staticKeyword\n" );
	return STATIC_KEYWORD;
}
{VOID_KEYWORD} {
	// printf( "voidKeyword\n" );
	return VOID_KEYWORD;
}
{PUBLIC_KEYWORD} {
	// printf( "publicKeyword\n" );
	return PUBLIC_KEYWORD;
}
{EXTENDS_KEYWORD} {
	// printf( "extendsKeyword\n" );
	return EXTENDS_KEYWORD;
}
{RETURN_KEYWORD} {
	// printf( "returnKeyword\n" );
	return RETURN_KEYWORD;
}
{INT_KEYWORD} {
	// printf( "intKeyword\n" );
	return INT_KEYWORD;
}
{BOOL_KEYWORD} {
	// printf( "boolKeyword\n" );
	return BOOL_KEYWORD;
}
{IF_KEYWORD} {
	// printf( "ifKeyword\n" );
	return IF_KEYWORD;
}
{WHILE_KEYWORD} {
	// printf( "whileKeyword\n" );
	return WHILE_KEYWORD;
}
{TRUE_KEYWORD} {
	printf( "trueKeyword\n" );
}
{FALSE_KEYWORD} {
	printf( "falseKeyword\n" );
}
{THIS_KEYWORD} {
	printf( "thisKeyword\n" );
}
{NEW_KEYWORD} {
	printf( "newKeyword\n" );
}

{IDENTIFIER} {
	printf( "Identifier(%s)\n", yytext );
}

. {
	/* */
}
 
%%
 