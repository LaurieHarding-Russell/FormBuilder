#ifndef PUMPKIN_SPICE_OBJECT_H
#define PUMPKIN_SPICE_OBJECT_H

#include<functional>
#include "Texture.h"
#include <glm/glm.hpp>

class PumpkinSpiceObject {
    public:
    std::vector<std::vector<glm::vec3>> meshes;
    // forground background textures?
    std::vector<glm::vec2> textureMap {
        // triangle 1
        glm::vec2(0.0f,0.0f),						// bottom left
        glm::vec2(0.0f,1.0f),						// Top left
        glm::vec2(1.0f,1.0f),						// top right
        // triangle 2
        glm::vec2(0.0f,0.0f),						// bottom left
        glm::vec2(1.0f,1.0f),						// top right
        glm::vec2(1.0f,0.0f)						// bottom right
    };

    std::vector<Texture*> textures; 
};
#endif