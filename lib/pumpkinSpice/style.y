%{
#include <stdio.h>
#include <string.h>

void showError();
%}


%token 

%%

%%

void showError() {
   printf("This isn't pumpkin spice!");
}