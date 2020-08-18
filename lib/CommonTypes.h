#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include<string>
#include<vector>

#include "rapidxml.hpp"
#include "single_include/nlohmann/json.hpp"
#include "stb_truetype/stb_truetype.h"

using json = nlohmann::json;
using namespace rapidxml;

#include "AbstractComponent.h"
#include "Input.h"

struct Point {
    float x;
    float y;
};

struct Colour {
    float red;
    float green;
    float blue;
    float alpha; 

    Colour() {
        Colour(0.0f, 0.0f, 0.0f, 0.0f);
    }

    Colour(float r, float g, float b, float a) {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
};

enum StyleDisplay {
    INLINE,
    BLOCK,
    GRID,
    FLEX
};

struct Style {
    StyleDisplay display;
    float topOffset;
    float leftOffset;
    float bottomOffset;
    float rightOffset;
    std::string font;
    Colour backgroundColour;
    Colour fontColour;

    Style() {
        this->display = BLOCK;
        this->topOffset = 0;
        this->leftOffset = 0;
        this->bottomOffset = 0;
        this->rightOffset = 0;
        this->font = "";
        this->backgroundColour = Colour(1.0f, 1.0f, 1.0f, 1.0f);
        this->fontColour = Colour(0.0f, 0.0f, 0.0f, 1.0f);
    }
};


class PumpkinSpiceObject {
    public:
    std::vector<float> mesh;
    int vertexCount;
    std::vector<float> texture; 
};

struct PumpkinSpiceInput {
    MouseInput mouseInput;
    KeyboardInput keyboardInput;
    std::vector<AbstractComponent> components;
};


#endif