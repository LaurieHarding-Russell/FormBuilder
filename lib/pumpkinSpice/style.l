%{
#include <stdio.h>
#include <string.h>

void showError();
%}

digit       [0-9];
class       .[a-z][a-z0-9]*
tag         [a-z][a-z0-9]*
operator    [+,-,*,/,^]


%%
{tag}       { 
      sscanf(yytext. "%s", yylval.name);
      return (TAG);
   }
{class}     { 
      sscanf(yytext. "%s", yylval.name);
      return (CLASS);
   }
{digit}     { 
      yylval.numdata = atoi(yytext);
      return (CLASS);
   }
   
{operator}  {
   return (operator)
   }
"="         {
   return (EQUAL)
   }
":"         {
      return (COLON)
   }
";"         { 
      return (SEMIOLON);
   }
/* keywords */
"display"   {
      return (DISPLAY)
   }
"background"   {
      return (BACKGROUND)
   }


%%

void showError() {
   printf("This isn't pumpkin spice!");
}