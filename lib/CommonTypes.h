#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include<string>
#include<vector>

#include "rapidxml.hpp"
#include "single_include/nlohmann/json.hpp"
#include "stb_truetype/stb_truetype.h"

using json = nlohmann::json;


#include "AbstractComponent.h"
#include "Input.h"

struct Point {
    int x;
    int y;
};

struct Colour {
    float red;
    float green;
    float blue;
    float alpha; 

    Colour(float r, float g, float b, float a) {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
};

struct Style {
    Point topLeftPosition;
    Point topRightPosition;
    Colour backgroundColour;
    Colour fontColour;
};

class PumpkinSpiceObject {
    public:
    float* mesh;
    float* texture; 
};

struct PumpkinSpiceInput {
    MouseInput mouseInput;
    KeyboardInput keyboardInput;
    std::vector<AbstractComponent> components;
};


#endif