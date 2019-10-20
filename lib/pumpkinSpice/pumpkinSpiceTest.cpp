#include <iostream>
#include "lib/pumpkinSpiceFlex.h"

extern "C" {
  int yyparse(void);
}

int main() {
    if(!(yyin = fopen("lib/default.style", "r"))) {
        std::cerr << "Failed to open default.style\n";
        return (1);
    }

    return yyparse();
}