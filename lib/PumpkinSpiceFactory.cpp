#include "PumpkinSpiceFactory.h"

PumpkinSpiceObject* PumpkinSpiceCompiler::compileComponents(PumpkinSpiceInput pumpkinSpiceInput) {
    return new PumpkinSpiceObject();
}

PumpkinSpiceObject* PumpkinSpiceCompiler::compilePumpkinSpice(std::string pumkinFile, std::string style) {
    // rapidxml::file<> xmlFile(pumkinFile);
    // rapidxml::xml_document<> doc;

    // print(std::cout, doc, 0);
    return new PumpkinSpiceObject();
}

float* PumpkinSpiceCompiler::createSquareMesh(Point topLeft, Point bottomRight) {
    float verts [] = {
        // triangle 1
        topLeft.x, bottomRight.y,
        topLeft.x, topLeft.y,
        bottomRight.x, topLeft.y,
        // triangle 2
        topLeft.x, bottomRight.y,
        bottomRight.x, topLeft.y,
        bottomRight.x, bottomRight.y
    };
}

