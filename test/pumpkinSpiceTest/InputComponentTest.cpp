#include "gtest/gtest.h"
#include "lib/PumpkinSpice.h"


TEST(PumpkinSpice, InputComponentCanSelect) {
  PumpkinSpice pumpkinSpiceCompiler = PumpkinSpice(100, 100);
  PumpkinSpiceInput pumpkinSpiceInput;

  pumpkinSpiceInput.basePumkinFileName = "test/pumpkinSpiceTest/InputComponentTest.pumpkin";
  pumpkinSpiceInput.baseSpiceFileName = "test/pumpkinSpiceTest/empty.spice";

  pumpkinSpiceCompiler.compileComponents(pumpkinSpiceInput);
  PumpkinSpiceComponentObject* pumpkinSpiceComponentObject = pumpkinSpiceCompiler.getPumpkinSpiceComponentObject();

  Point point;
  point.x = 0.5;
  point.y = 0.5;
  pumpkinSpiceCompiler.getInput()->callbackMousePosition(point);
  pumpkinSpiceCompiler.getInput()->callbackMouseButtonDownFunctions(0);
  
  EXPECT_TRUE(pumpkinSpiceComponentObject->abstractComponents[0]->getState().selected);  
}

TEST(PumpkinSpice, InputComponentCanUpdateValue) {
  PumpkinSpice pumpkinSpiceCompiler = PumpkinSpice(100, 100);
  PumpkinSpiceInput pumpkinSpiceInput;

  pumpkinSpiceInput.basePumkinFileName = "test/pumpkinSpiceTest/InputComponentTest.pumpkin";
  pumpkinSpiceInput.baseSpiceFileName = "test/pumpkinSpiceTest/empty.spice";

  pumpkinSpiceCompiler.compileComponents(pumpkinSpiceInput);
  PumpkinSpiceComponentObject* pumpkinSpiceComponentObject = pumpkinSpiceCompiler.getPumpkinSpiceComponentObject();

  Point point;
  point.x = 0.5;
  point.y = 0.5;
  pumpkinSpiceCompiler.getInput()->callbackMousePosition(point);
  pumpkinSpiceCompiler.getInput()->callbackMouseButtonDownFunctions(0);  
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('h');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('e');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('l');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('l');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('o');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown(' ');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('w');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('o');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('r');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('l');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('d');

  EXPECT_EQ(((InputComponent*)pumpkinSpiceComponentObject->abstractComponents[0])->returnValue(), "hello world");  
}

TEST(PumpkinSpice, InputComponentCanBackspace) {
  PumpkinSpice pumpkinSpiceCompiler = PumpkinSpice(100, 100);
  PumpkinSpiceInput pumpkinSpiceInput;

  pumpkinSpiceInput.basePumkinFileName = "test/pumpkinSpiceTest/InputComponentTest.pumpkin";
  pumpkinSpiceInput.baseSpiceFileName = "test/pumpkinSpiceTest/empty.spice";

  pumpkinSpiceCompiler.compileComponents(pumpkinSpiceInput);
  PumpkinSpiceComponentObject* pumpkinSpiceComponentObject = pumpkinSpiceCompiler.getPumpkinSpiceComponentObject();

  Point point;
  point.x = 0.5;
  point.y = 0.5;
  pumpkinSpiceCompiler.getInput()->callbackMousePosition(point);
  pumpkinSpiceCompiler.getInput()->callbackMouseButtonDownFunctions(0);  
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('1');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('2');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('3');
  pumpkinSpiceCompiler.getInput()->callbackKeyDown(char(127));
  pumpkinSpiceCompiler.getInput()->callbackKeyDown('4');

  EXPECT_EQ(((InputComponent*)pumpkinSpiceComponentObject->abstractComponents[0])->returnValue(), "124");  
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}