#include <iostream>
#include "gtest/gtest.h"

#include "lib/pumpkinSpiceFlex.h"

extern "C" {
  int yyparse(void);
}

TEST(HelloTest, GetGreet) {
    if(!(yyin = fopen("lib/default.style", "r"))) {
        std::cerr << "Failed to open default.style\n";
        FAIL();
    }

    EXPECT_EQ(yyparse(), 1);
};
