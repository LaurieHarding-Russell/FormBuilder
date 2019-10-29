%language "c++"
%define parse.error verbose

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "pumpkinSpice/pumpkinSpice.h"
// #include <glm/vec4.hpp>

struct PumpkinSpice {
    char* display;
   // glm::vec4 backgroundColour;
    char* backgroundColour;
};

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
   char* stringVal;
   double numVal;
}

%token <stringVal> TAG
%token <stringVal> CLASS
%token <stringVal> HEXCODE

%token <numVal> DIGIT

%token <stringVal> OPERATOR
%token <stringVal> EQUAL
%token <stringVal> COLON
%token <stringVal> SEMICOLON
%token <stringVal> OPEN_BRACKET
%token <stringVal> CLOSING_BRACKET

%token <stringVal> DISPLAY
%token <stringVal> BACKGROUND

%type<stringVal> definitions
%type<stringVal> statement
%type<stringVal> colourType

%start definitions

%%
definitions: %empty | definitions statement;
statement: selectorDeclaration OPEN_BRACKET properties CLOSING_BRACKET;
properties: %empty | properties property SEMICOLON;
property: BACKGROUND COLON HEXCODE {
   fprintf(stdout, "test 3 %s", $3);
}
selectorDeclaration: TAG | CLASS {
   fprintf(stdout, "test 3 %s", $1);
}
digitCalculation: digitCalculation OPERATOR DIGIT | DIGIT OPERATOR DIGIT;

%%

void yyerror(const char* s) {
   fprintf(stderr, "This isn't pumpkin spice! %s\n", s);
   exit(1);
}