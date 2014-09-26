%{
 
/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */
 
#include <stdio.h>
 
%}
 
%option outfile="Lexer.cpp"
%option warn nodefault
 
%option noyywrap never-interactive
 
LEFT_CURLY_BRACE      "{"
RIGHT_CURLY_BRACE      "}"
LEFT_ROUND_BRACE "("
RIGHT_ROUND_BRACE ")"
LEFT_SQUARE_BRACE "["
RIGHT_SQUARE_BRACE "]"

PLUS        "+"
MINUS		"-"
MULTIPLY    "*"
LESS		"<"
EQUAL		"="
DOT			"\."
SEMICOLON	";"
COMMA		","
EXCLAMATION_MARK "!"
BINARY_AND	"&&"
 
INTEGER_NUMBER      [0-9]+
WHITESPACE  [ \r\n\t]*

CLASS_KEYWORD "class"
PUBLIC_KEYWORD "public"
STATIC_KEYWORD "static"
VOID_KEYWORD "void"
EXTENDS_KEYWORD "extends"
RETURN_KEYWORD "return"
INT_KEYWORD "int"
BOOL_KEYWORD "bool"
IF_KEYWORD "if"
WHILE_KEYWORD "while"
TRUE_KEYWORD "true"
FALSE_KEYWORD "false"
THIS_KEYWORD "this"
NEW_KEYWORD "new"

IDENTIFIER [a-zA-Z][_0-9A-Za-z]*
 
%%
 
{WHITESPACE}            { /* Skip blanks. */ }

{LEFT_CURLY_BRACE}      { printf("LeftCurlyBrace\n"); }
{RIGHT_CURLY_BRACE}      { printf("RightCurlyBrace\n"); }
{LEFT_ROUND_BRACE} { printf("LeftRoundBrace\n"); }
{RIGHT_ROUND_BRACE} { printf("RightRoundBrace\n"); }
{LEFT_SQUARE_BRACE} { printf("LeftSquareBrace\n"); }
{RIGHT_SQUARE_BRACE} { printf("RightSquareBrace\n"); }

{PLUS}        {printf("Plus\n");}
{MINUS}		{printf("Minus\n");}
{MULTIPLY}    {printf("Multiply\n");}
{LESS}		{printf("Less\n");}
{EQUAL}		{printf("Equal\n");}
{DOT}			{printf("Dot\n");}
{SEMICOLON}	{printf("Semicolon\n");}
{COMMA}		{printf("Comma\n");}
{EXCLAMATION_MARK} {printf("ExclamationMark\n");}
{BINARY_AND}	{printf("BinaryAnd\n");}
 
{INTEGER_NUMBER}      {printf("Integer(%s)\n", yytext);}
{WHITESPACE}  {/* */}

{CLASS_KEYWORD} {printf("classKeyword\n");}
{STATIC_KEYWORD}  {printf("staticKeyword\n");}
{VOID_KEYWORD} {printf("voidKeyword\n");}
{PUBLIC_KEYWORD} {printf("publicKeyword\n");}
{EXTENDS_KEYWORD} {printf("extendsKeyword\n");}
{RETURN_KEYWORD} {printf("returnKeyword\n");}
{INT_KEYWORD} {printf("intKeyword\n");}
{BOOL_KEYWORD} {printf("boolKeyword\n");}
{IF_KEYWORD} {printf("ifKeyword\n");}
{WHILE_KEYWORD} {printf("whileKeyword\n");}
{TRUE_KEYWORD} {printf("trueKeyword\n");}
{FALSE_KEYWORD} {printf("falseKeyword\n");}
{THIS_KEYWORD} {printf("thisKeyword\n");}
{NEW_KEYWORD} {printf("newKeyword\n");}

{IDENTIFIER} {printf("Identifier(%s)\n", yytext);}

.               {  }
 
%%
 
int yyerror(const char *msg) {
    fprintf(stderr,"Error:%s\n",msg); return 0;
}