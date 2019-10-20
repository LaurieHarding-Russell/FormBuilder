%language "c++"
%define parse.error verbose

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}


%token TAG
%token CLASS
%token HEXCODE
%token DIGIT

%token OPERATOR
%token EQUAL
%token COLON
%token SEMIOLON
%token OPEN_BRACKET
%token CLOSING_BRACKET

%token DISPLAY
%token BACKGROUND

%start definitions

%%
definitions: | definitions statement;
statement: selectorDeclaration OPEN_BRACKET properties CLOSING_BRACKET;
properties: | colourType COLON colourValue SEMIOLON;
colourType: BACKGROUND;
colourValue: HEXCODE;
selectorDeclaration: TAG | CLASS;
digitCalculation: digitCalculation OPERATOR DIGIT | DIGIT OPERATOR DIGIT;

%%

void yyerror(const char* s) {
   fprintf(stderr, "This isn't pumpkin spice! %s\n", s);
   exit(1);
}