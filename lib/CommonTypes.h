#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include<string>
#include<vector>

#include "rapidxml.hpp"
#include "single_include/nlohmann/json.hpp"

#include <glm/glm.hpp>
#include<iostream>

using json = nlohmann::json;
using namespace rapidxml;

const int BYTES_PER_PIXEL = 4; // r,g,b,a

static float* pointsToFloats(const std::vector<glm::vec2> points) {
    float* verts = new float[points.size() * 2];
    for(uint i = 0; i != points.size(); i++) {
        verts[0 + i*2] = points[i].x;
        verts[1 + i*2] = points[i].y;
    }
    return verts;
}

static float* pointsToFloats(const std::vector<glm::vec3> points) {
    float* verts = new float[points.size() * 3];
    for(uint i = 0; i != points.size(); i++) {
        verts[0 + i*3] = points[i].x;
        verts[1 + i*3] = points[i].y;
        verts[2 + i*3] = points[i].z;
    }
    return verts;
}

struct Colour {
    float red;
    float green;
    float blue;
    float alpha; 

    void validColourInput(float r, float g, float b, float a) {
        if (r > 1.0 || r < 0.0 ||
            g > 1.0 || g < 0.0 ||
            b > 1.0 || b < 0.0 ||
            a > 1.0 || a < 0.0
        ) {
            throw std::logic_error("Invalid colour value inputed");
        }
    }

    Colour() {
        Colour(0.0f, 0.0f, 0.0f, 0.0f);
    }

    Colour(std::vector<float> values) {
        validColourInput(values[0],
                values[1], 
                values[2], 
                values[3]);
                
        Colour(values[0],
                values[1], 
                values[2], 
                values[3]);
    }

    Colour(float r, float g, float b, float a) {
        validColourInput(r, g, b, a);
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }

    void setColour(std::vector<float> values) {
        this->red = values[0];
        this->green = values[1];
        this->blue =  values[2];
        this->alpha = values[3];
    }

    unsigned char getRedChar() const {
        return 255 * this->red;
    }
    unsigned char getGreenChar() const {
        return 255 * this->green;
    }
    unsigned char getBlueChar() const {
        return 255 * this->blue;
    }
    unsigned char getAlphaChar() const {
        return 255 * this->alpha;
    }

    friend std::ostream& operator<<(std::ostream& os, const Colour& colour) {
        os << "COLOUR{r: " << colour.red << ", g:" << colour.green << ", b:" << colour.blue << "alpha:" << colour.alpha << "}";
        return os;
    }
};


#endif