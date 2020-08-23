#include "gtest/gtest.h"
#include "lib/SpiceFactory.h"
#include <fstream>

std::string loadFile(std::string name);


TEST(Spice, test1) {
    std::string spiceString = loadFile("style.spice");
    json spice = json::parse(spiceString);
    std::vector<std::string> classes;
    Style styleState = Style();


    json leftOver = getStyleState(spice, classes, styleState);

    // EXPECT_EQ(styleState.backgroundColour.red, 0.3);
}


std::string loadFile(std::string name) {
    std::string data = "";
    std::ifstream file (name);

    if (file.is_open()) {
        std::string line;
        while ( getline(file, line) ) {
            data += line + '\n';
        }
        file.close();
    }
    return data;
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}