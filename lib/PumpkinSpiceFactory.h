#ifndef PUMPKIN_SPICE_H
#define PUMPKIN_SPICE_H

#include "CommonTypes.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

class PumpkinSpiceCompiler {

    public:
    PumpkinSpiceObject* compileComponents(PumpkinSpiceInput pumpkinSpiceInput);
    PumpkinSpiceObject* compilePumpkinSpice(std::string pumkinFile, std::string styleFileName);

    private:
    float* createSquareMesh(Point top, Point bottom);
    bool* createFontTexture();
    void getStyleState(json style, std::vector<std::string> classes, Style& styleState);
    void iterateOverNode(xml_node<>* node, PumpkinSpiceObject* pumpkinSpiceObject, json style, std::vector<std::string> classes, Style styleState);
    std::string loadFile(std::string name);
};

#endif