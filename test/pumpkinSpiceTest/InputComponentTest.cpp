#include "gtest/gtest.h"
#include "lib/PumpkinSpiceFactory.h"


TEST(PumpkinSpice, InputComponent) {
  PumpkinSpiceCompiler pumpkinSpiceCompiler = PumpkinSpiceCompiler(100, 100);
  PumpkinSpiceInput pumpkinSpiceInput;

  pumpkinSpiceInput.basePumkinFileName = "test/pumpkinSpiceTest/InputComponentTest.pumpkin";
  pumpkinSpiceInput.baseSpiceFileName = "test/pumpkinSpiceTest/empty.spice";

  PumpkinSpiceComponentObject* pumpkinSpiceComponentObject = pumpkinSpiceCompiler.compileComponents(pumpkinSpiceInput);

  Point point;
  point.x = 0.5;
  point.y = 0.5;
  pumpkinSpiceCompiler.getInput()->callbackMousePosition(point);
  pumpkinSpiceCompiler.getInput()->callbackMouseButtonDownFunctions();
  
  EXPECT_TRUE(pumpkinSpiceComponentObject->abstractComponents[0]->getState().selected);  
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}