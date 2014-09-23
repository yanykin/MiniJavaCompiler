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
 
LPAREN      "("
RPAREN      ")"
PLUS        "+"
MULTIPLY    "*"
 
NUMBER      [0-9]+
WS          [ \r\n\t]*
 
%%
 
{WS}            { /* Skip blanks. */ }
{NUMBER}        { printf("%s", yytext); }
 
{MULTIPLY}      { printf("%s", yytext); }
{PLUS}          { printf("%s", yytext); }
{LPAREN}        { printf("%s", yytext); }
{RPAREN}        { printf("%s", yytext); }
.               {  }
 
%%
 
int yyerror(const char *msg) {
    fprintf(stderr,"Error:%s\n",msg); return 0;
}