#ifndef PUMPKIN_FACTORY_H
#define PUMPKIN_FACTORY_H

#include <vector>
#include "CommonTypes.h"

static std::vector<Point> createSquareMesh(const Point topLeft, const Point bottomRight) {
    std::vector<Point> verts {
        // triangle 1
        Point(topLeft.x, bottomRight.y, topLeft.z),
        Point(topLeft.x, topLeft.y, topLeft.z),
        Point(bottomRight.x, topLeft.y, topLeft.z),
        /// triangle 2
        Point(topLeft.x, bottomRight.y, topLeft.z),
        Point(bottomRight.x, topLeft.y, topLeft.z),
        Point(bottomRight.x, bottomRight.y, topLeft.z)
    };
    return verts;
}

#endif