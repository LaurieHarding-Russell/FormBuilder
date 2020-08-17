#include "PumpkinSpiceFactory.cpp"

static PumpkinSpiceCompiler::compileComponents(PumpkinSpiceInput pumpkinSpiceInput) {

}

static PumpkinSpiceCompiler::compilePumpkinSpice(string pumkinFile, string style) {
    rapidxml::file<> xmlFile(pumkinFile);
    rapidxml::xml_document<> doc;

    print(std::cout, doc, 0);
}

static float* PumpkinSpiceCompiler::createSquareMesh(Point topLeft, Point bottomRight) {
    Float verts* = new Float* {
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

