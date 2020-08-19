#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include<string>
#include<vector>

#include "rapidxml.hpp"
#include "single_include/nlohmann/json.hpp"

using json = nlohmann::json;
using namespace rapidxml;

#include "AbstractComponent.h"
#include "Input.h"

struct Point {
    float x;
    float y;
    Point(){
        this->x = 0.0f;
        this->y = 0.0f;
    }

    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }

    static float* pointsToFloats(Point* points) {
        int arraySize = sizeof(points)/sizeof(points[0]);
        float* verts = new float[arraySize *2];
        for(int i = 0; i != arraySize; i++) {
            verts[0 + i*2] = points[i].x;
            verts[0 + i*2] = points[i].y;
        }
        return verts;
    }
};


// think about this
struct Bitmap {
    char* data;
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
    std::vector<float*> meshes;
    // float textureMap[]={
    //     // triangle 1
    //     0.0f,0.0f,						// bottom left
    //     0.0f,1.0f,						// Top left
    //     1.0f,1.0f,						// top right
    //     // triangle 2
    //     0.0f,0.0f,						// bottom left
    //     1.0f,1.0f,						// top right
    //     1.0f,0.0f						// bottom right
    // };

    int vertexCount;
    std::vector<unsigned char*> textures; 
};

struct PumpkinSpiceInput {
    MouseInput mouseInput;
    KeyboardInput keyboardInput;
    std::vector<AbstractComponent> components;
};


#endif