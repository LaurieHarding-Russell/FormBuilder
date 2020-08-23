#include "gtest/gtest.h"
#include "lib/SpiceFactory.h"
#include <fstream>

#include <iostream>

std::string loadFile(std::string name);


TEST(Spice, get_Base) {
    std::string spiceString = loadFile("test/Spice/style.spice");
    json spice = json::parse(spiceString);
    std::vector<std::string> classes;
    Style styleState = Style();


    json leftOver = getStyleState(spice, classes, styleState);

    EXPECT_EQ(styleState.backgroundColour.red, 0.1f);
}

TEST(Spice, firstLevel) {
    std::string spiceString = loadFile("test/Spice/style.spice");
    json spice = json::parse(spiceString);
    std::vector<std::string> classes;
    classes.push_back("class1");
    Style styleState = Style();

    json leftOver = getStyleState(spice, classes, styleState);

    EXPECT_EQ(styleState.backgroundColour.red, 0.2f);
}

TEST(Spice, secondLevel) {
    std::string spiceString = loadFile("test/Spice/style.spice");
    json spice = json::parse(spiceString);
    std::vector<std::string> classes;
    classes.push_back("class1");
    classes.push_back("class2");
    Style styleState = Style();

    json leftOver = getStyleState(spice, classes, styleState);
    

    EXPECT_EQ(styleState.backgroundColour.red, 0.3f);
}

TEST(Spice, measurment) {
    std::string spiceString = loadFile("test/Spice/measurmentStyle.spice");
    json spice = json::parse(spiceString);
    std::vector<std::string> classes;
    classes.push_back("class1");

    Style styleState = Style();

    json leftOver = getStyleState(spice, classes, styleState);

    EXPECT_EQ(styleState.height , 1);
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