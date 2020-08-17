#ifndef PUMPKIN_SPICE_H
#define PUMPKIN_SPICE_H

#include "rapidxml.hpp"
#include "single_include/nlohmann/json.hpp"
#include "stb_truetype/stb_truetype.h
#include<string>
#include<Array>

using json = nlohmann::json;


#include "AbstractComponent.h"
#include "Input.h"

struct Point {
    int x,y;
}

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
}

class PumpkinSpiceObject {
    public:
    float* mesh;
    colour; 
};

struct PumpkinSpiceInput {
    MouseInput mouseInput;
    KeyboardInput keyboardInput;
    std::Array<AbstractComponent> components;
};

class PumpkinSpiceCompiler {

    public:
    static compileComponents(PumpkinSpiceInput pumpkinSpiceInput);


    static compilePumpkin(string pumkinFile);

    private:
    static createSquareMesh(Point top, Point bottom);

}

#endif