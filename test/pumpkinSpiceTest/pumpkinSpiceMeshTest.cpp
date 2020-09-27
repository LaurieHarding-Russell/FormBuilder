#include "gtest/gtest.h"
#include "lib/PumpkinSpice.h"


TEST(PumpkinSpice, InputComponentCanSelect) {
  PumpkinSpice pumpkinSpiceCompiler = PumpkinSpice(100, 100);
  PumpkinSpiceInput pumpkinSpiceInput;

  pumpkinSpiceInput.basePumkinFileName = "test/pumpkinSpiceTest/pumpkinSpiceMeshTest.pumpkin";
  pumpkinSpiceInput.baseSpiceFileName = "test/pumpkinSpiceTest/empty.spice";

  pumpkinSpiceCompiler.compileComponents(pumpkinSpiceInput);
  PumpkinSpiceComponentObject* pumpkinSpiceComponentObject = pumpkinSpiceCompiler.getPumpkinSpiceComponentObject();

  // for(std::vector<Point> mesh: pumpkinSpiceComponentObject->basePumpkinSpiceObjects->meshes) {
  //   for (Point point : mesh) {
  //     std::cout << point << "\n";
  //   }
  // }
  
  EXPECT_EQ(pumpkinSpiceComponentObject->basePumpkinSpiceObjects->meshes.size(), 4);  
  EXPECT_EQ(pumpkinSpiceComponentObject->basePumpkinSpiceObjects->textures.size(), 4);  
  EXPECT_EQ(pumpkinSpiceComponentObject->basePumpkinSpiceObjects->textureMap.size(), 6);  
}


GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}