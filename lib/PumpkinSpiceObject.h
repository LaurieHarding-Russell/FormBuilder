#ifndef PUMPKIN_SPICE_OBJECT_H
#define PUMPKIN_SPICE_OBJECT_H

#include<functional>
#include "AbstractComponent.h"

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

    ~PumpkinSpiceObject() {
        for (int i = 0; i !=0; i++) {
            delete textures.at(i);
        }
    }
};

struct PumpkinSpiceComponentInput {
    std::string pumkinFileName;
    std::string spiceFileName;
    std::function<AbstractComponent*(AbstractComponentInput)> componentFactory;
};

struct PumpkinSpiceInput {
    UserInput userInput;
    std::vector<PumpkinSpiceComponentInput> components;
    PumpkinSpiceComponentInput pumpkinSpiceComponentInput;
    std::string basePumkinFileName;
    std::string baseSpiceFileName;
};

#endif