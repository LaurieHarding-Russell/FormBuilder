#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include<string>
#include<vector>

#include "rapidxml.hpp"
#include "single_include/nlohmann/json.hpp"

using json = nlohmann::json;
using namespace rapidxml;

#include "Input.h"

const int BYTES_PER_PIXEL = 4; // r,g,b,a

class Point {
    public:
    float x;
    float y;
    float z;

    Point(){
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    }

    Point(float x, float y) {
        this->x = x;
        this->y = y;
        this->z = 0.0f;
    }

    Point(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "POINT{X: " << point.x << ", Y:" << point.y << ", Z:" << point.z <<"}";
        return os;
    }
};

static float* pointsToFloats(std::vector<Point> points) {
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

    Colour() {
        Colour(0.0f, 0.0f, 0.0f, 0.0f);
    }

    Colour(std::vector<float> values) {
        Colour(values[0],
                values[1], 
                values[2], 
                values[3]);
    }

    Colour(float r, float g, float b, float a) {
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

    unsigned char getRedChar() {
        return 255 * this->red;
    }
    unsigned char getGreenChar() {
        return 255 * this->green;
    }
    unsigned char getBlueChar() {
        return 255 * this->blue;
    }
    unsigned char getAlphaChar() {
        return 255 * this->alpha;
    }

    friend std::ostream& operator<<(std::ostream& os, const Colour& colour) {
        os << "COLOUR{r: " << colour.red << ", g:" << colour.green << ", b:" << colour.blue << "alpha:" << colour.alpha << "}";
        return os;
    }
};

struct Texture {
    unsigned char* data;
    int width;
    int height;

    static void flipYAxis(Texture* texture) {
        unsigned char* newData = new unsigned char[texture->width * texture->height];
        int last = texture->height * texture->width * BYTES_PER_PIXEL;

        for (int y = 0; y != texture->height; y++) {
            for (int x = 0; x != texture->width; x++) {
                int numberOfCharacterInWidth = texture->width * BYTES_PER_PIXEL;
                int pixelPosition = y * numberOfCharacterInWidth + x * BYTES_PER_PIXEL;
                
                int oppositelPosition = (texture->height - y) * numberOfCharacterInWidth  + x * BYTES_PER_PIXEL;

                newData[pixelPosition + 0] = texture->data[oppositelPosition + 0];
                newData[pixelPosition + 1] = texture->data[oppositelPosition + 1];
                newData[pixelPosition + 2] = texture->data[oppositelPosition + 2];
                newData[pixelPosition + 3] = texture->data[oppositelPosition + 3];

            }
        }
        texture->data = newData;
    }
};



#endif