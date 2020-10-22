#ifndef PUMPKIN_FACTORY_H
#define PUMPKIN_FACTORY_H

#include <vector>
#include "CommonTypes.h"

static std::vector<glm::vec3> createSquareMesh(const glm::vec3 topLeft, const glm::vec3 bottomRight) {
    std::vector<glm::vec3> verts {
        // triangle 1
        glm::vec3(bottomRight.x, topLeft.y, topLeft.z),
        glm::vec3(topLeft.x, topLeft.y, topLeft.z),
        glm::vec3(topLeft.x, bottomRight.y, topLeft.z),
        /// triangle 2
        glm::vec3(bottomRight.x, bottomRight.y, topLeft.z),
        glm::vec3(bottomRight.x, topLeft.y, topLeft.z),
        glm::vec3(topLeft.x, bottomRight.y, topLeft.z)
    };
    return verts;
}

#endif