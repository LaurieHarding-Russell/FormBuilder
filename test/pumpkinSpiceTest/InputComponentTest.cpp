#include "gtest/gtest.h"
#include "lib/PumpkinSpiceFactory.h"


TEST(PumpkinSpice, InputComponent) {
  PumpkinSpiceCompiler pumpkinSpiceCompiler = PumpkinSpiceCompiler(100, 100);
  PumpkinSpiceInput pumpkinSpiceInput;

  pumpkinSpiceInput.basePumkinFileName = "test/pumpkinSpiceTest/InputComponentTest.pumpkin";
  pumpkinSpiceInput.baseSpiceFileName = "test/pumpkinSpiceTest/empty.spice";

  PumpkinSpiceComponentObject* pumpkinSpiceComponentObject = pumpkinSpiceComponentObject = pumpkinSpiceCompiler.compileComponents(pumpkinSpiceInput);

  
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}