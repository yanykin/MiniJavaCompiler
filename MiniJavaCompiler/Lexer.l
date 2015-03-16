%option noyywrap

%{ 
	#include <cstdlib>
	#include <iostream>
	#include <cstring>
	#include "Parser.hpp"

	#include "GrammaticRules.h"

	extern int yyparse();
	static int line_num = 1;
	static int column_num = 1;

	void update_location() {
		yylloc.first_line = line_num;
		yylloc.first_column = column_num;
		column_num += strlen(yytext);
		yylloc.last_line = line_num;
		yylloc.last_column = column_num;
	}
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
	
}

[ \r\t]* {
	column_num += strlen(yytext);
}

"\n" {
	++line_num;
	column_num = 1;
}

"&&" {
	update_location();
	return BINARY_AND;
}
 
{INTEGER_NUMBER} {
	update_location();
	yylval.int_val = atoi(yytext);
	return INTEGER_NUMBER;
}

"class" {
	update_location();
	return CLASS_KEYWORD;
}

"static" {
	update_location();
	return STATIC_KEYWORD;
}

"void" {
	update_location();
	return VOID_KEYWORD;
}

"public" {
	update_location();
	return PUBLIC_KEYWORD;
}

"extends" {
	update_location();
	return EXTENDS_KEYWORD;
}

"return" {
	update_location();
	return RETURN_KEYWORD;
}

"int" {
	update_location();
	return INT_KEYWORD;
}

"boolean" {
	update_location();
	return BOOLEAN_KEYWORD;
}

"String" {
	update_location();
	return STRING_KEYWORD;
}

"if" {
	update_location();
	return IF_KEYWORD;
}

"else" {
	update_location();
	return ELSE_KEYWORD;
}

"while" {
	update_location();
	return WHILE_KEYWORD;
}

"true" {
	update_location();
	return TRUE_KEYWORD;
}

"false" {
	update_location();
	return FALSE_KEYWORD;
}

"this" {
	update_location();
	return THIS_KEYWORD;
}

"new" {
	update_location();
	return NEW_KEYWORD;
}

"println" {
	update_location();
	return PRINTLN_KEYWORD;
}

"length" {
	update_location();
	return LENGTH_KEYWORD;
}

"main" {
	update_location();
	return MAIN_KEYWORD;
}

"System" {
	update_location();
	return SYSTEM_KEYWORD;
}

"out" {
	update_location();
	return OUT_KEYWORD;
}

{IDENTIFIER} {
	update_location();
	int len = strlen(yytext);
	yylval.string_val = new char[len + 1];
	strncpy_s(yylval.string_val, len + 1, yytext, len);
	yylval.string_val[len] = '\0';
	return IDENTIFIER;
}

. {
	update_location();
	return yytext[0];
}

<comment>[^*\n]* {
	column_num += strlen(yytext);
	/* eat anything that's not a '*' */
}

<comment>"*"+[^*/\n]* {
	column_num += strlen(yytext);
	/* eat up '*'s not followed by '/'s */
}

<comment>"\n" {  
	++line_num;
	column_num = 1;
}

<comment>"*"+"/" {
	column_num += strlen(yytext);
	BEGIN(INITIAL);
}
 
%%
 