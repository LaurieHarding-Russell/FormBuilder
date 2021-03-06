#include "gtest/gtest.h"
#include "lib/PumpkinSpice.h"

std::string BEFORE_CLICK = "Goodbye World!";
std::string AFTER_CLICK = "Hello World!";

TEST(ComponentFunctionTest, test_function_linking) {
  PumpkinSpice pumpkinSpiceCompiler = PumpkinSpice(100, 100);
  PumpkinSpiceInput pumpkinSpiceInput;

  pumpkinSpiceInput.basePumkinFileName = "test/ComponentFunctionTest/FunctionTest.pumpkin";
  pumpkinSpiceInput.baseSpiceFileName = "test/ComponentFunctionTest/empty.spice";

  pumpkinSpiceCompiler.compileComponents(pumpkinSpiceInput);
  PumpkinSpiceComponentObject* pumpkinSpiceComponentObject = pumpkinSpiceCompiler.getPumpkinSpiceComponentObject();

  ButtonComponent* button = (ButtonComponent*)pumpkinSpiceCompiler.getComponpentByName("helloButton");
  EXPECT_TRUE(button != NULL);

  std::string helloVariable = BEFORE_CLICK;

  button->clickCallbackFunction = { [&]() { helloVariable = AFTER_CLICK; } };

  EXPECT_EQ(BEFORE_CLICK, helloVariable);

  glm::vec2 point;
  point.x = 0.5;
  point.y = 0.5;
  pumpkinSpiceCompiler.getInput()->callbackMousePosition(point);
  pumpkinSpiceCompiler.getInput()->callbackMouseButtonDownFunctions(0);
  pumpkinSpiceCompiler.getInput()->callbackMouseButtonUpFunctions(0);

  EXPECT_EQ(AFTER_CLICK, helloVariable);
  EXPECT_TRUE(pumpkinSpiceComponentObject->abstractComponents[0]->getState().selected);
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}