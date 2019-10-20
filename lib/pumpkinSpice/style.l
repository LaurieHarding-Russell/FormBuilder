%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()

#include "pumpkinSpiceBison.h"

%}

digit       [0-9];
class       .[a-z][a-z0-9]*
tag         [a-z][a-z0-9]*
operator    [+,-,*,/,^]
hexcode     #[a-f0-9][a-f0-9]{6}|#[a-f0-9][a-f0-9]{8}


%%
{hexcode} {
   // yylval.name = strdup(yytext);
   return (HEXCODE);
}
{digit} { 
   // yylval.numdata = atoi(yytext);
   return (DIGIT);
}
   
{operator} {
   return (OPERATOR);
}

"=" {
   return (EQUAL);
}

"{" {
   return (OPEN_BRACKET);
}

"{" {
   return (CLOSING_BRACKET);
}

":" {
   return (COLON);
}

";" { 
   return (SEMIOLON);
}

"display" {
   return (DISPLAY);
}

"background" {
   return (BACKGROUND);
}


{class} { 
   // yylval.name = strdup(yytext);
   return (CLASS);
}

{tag} { 
   // yylval.name = strdup(yytext);
   return (TAG);
}
%%