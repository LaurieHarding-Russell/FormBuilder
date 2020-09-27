#ifndef PUMPKIN_SPICE_OBJECT_H
#define PUMPKIN_SPICE_OBJECT_H

#include<functional>
#include "Texture.h"

class PumpkinSpiceObject {
    public:
    std::vector<std::vector<Point>> meshes;
    // forground background textures?
    std::vector<Point> textureMap {
        // triangle 1
        Point(0.0f,0.0f),						// bottom left
        Point(0.0f,1.0f),						// Top left
        Point(1.0f,1.0f),						// top right
        // triangle 2
        Point(0.0f,0.0f),						// bottom left
        Point(1.0f,1.0f),						// top right
        Point(1.0f,0.0f)						// bottom right
    };

    std::vector<Texture*> textures; 
};
#endif