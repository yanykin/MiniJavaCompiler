%option noyywrap

%{ 
	#include <cstdlib>
	#include <iostream>
	#include <cstring>
	#include "Parser.hpp"
	extern int yyparse();
	static int line_num = 1;
	static int column_num = 1;
%}
 
INTEGER_NUMBER		[0-9]+
WHITESPACE			[ \r\n\t]*
IDENTIFIER			[a-zA-Z][_0-9A-Za-z]*

%x comment

%%
"/*" {
	column_num += strlen(yytext);
	BEGIN(comment);
}
"//"[^\n]* {
	std::cout << "comment\n";
}

[ \r\t]* {
	column_num += strlen(yytext);
}

'\n' {
	++line_num;
	column_num = 1;
}

"&&" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return BINARY_AND;
}
 
{INTEGER_NUMBER} {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	yylval.int_val = atoi(yytext);
	return INTEGER_NUMBER;
}

"class" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return CLASS_KEYWORD;
}

"static" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return STATIC_KEYWORD;
}

"void" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return VOID_KEYWORD;
}

"public" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return PUBLIC_KEYWORD;
}

"extends" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return EXTENDS_KEYWORD;
}

"return" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return RETURN_KEYWORD;
}

"int" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return INT_KEYWORD;
}

"boolean" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return BOOLEAN_KEYWORD;
}

"String" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return STRING_KEYWORD;
}

"if" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return IF_KEYWORD;
}

"else" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return ELSE_KEYWORD;
}

"while" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return WHILE_KEYWORD;
}

"true" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return TRUE_KEYWORD;
}

"false" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return FALSE_KEYWORD;
}

"this" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return THIS_KEYWORD;
}

"new" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return NEW_KEYWORD;
}

"println" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return PRINTLN_KEYWORD;
}

"length" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return LENGTH_KEYWORD;
}

"main" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return MAIN_KEYWORD;
}

"System" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return SYSTEM_KEYWORD;
}

"out" {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
	return OUT_KEYWORD;
}

{IDENTIFIER} {
	yylloc.first_line = line_num;
	yylloc.first_column = column_num;
	column_num += strlen(yytext);
	yylloc.last_line = line_num;
	yylloc.last_column = column_num;
}

. {
	++column_num;
}

<comment>[^*\n]* {
	column_num += strlen(yytext);
	/* eat anything that's not a '*' */
}

<comment>"*"+[^*/\n]* {
	column_num += strlen(yytext);
	/* eat up '*'s not followed by '/'s */
}

<comment>'\n' {  
	++line_num;
	column_num = 1;
}

<comment>"*"+"/" {
	column_num += strlen(yytext);
	BEGIN(INITIAL);
}
 
%%
 