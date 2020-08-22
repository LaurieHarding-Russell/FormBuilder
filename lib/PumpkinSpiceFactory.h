#ifndef PUMPKIN_SPICE_H
#define PUMPKIN_SPICE_H

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include "stb_truetype.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>

#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"


#include "CommonTypes.h"
#include "PumpkinSpiceComponentObject.h"
#include "PumpkinSpiceObject.h"
#include <limits>
#include "AbstractComponent.h"
#include "InputComponent.h"
#include "ButtonComponent.h"

typedef std::map<std::string, stbtt_fontinfo> FontMap;
typedef std::pair<std::string, stbtt_fontinfo> FontPair;
typedef std::pair<std::string, std::function<AbstractComponent*(AbstractComponentInput)>> ComponentPair;


class PumpkinSpiceCompiler {

    public:
    PumpkinSpiceCompiler();
    PumpkinSpiceCompiler(int x, int y);
    ~PumpkinSpiceCompiler();
    PumpkinSpiceComponentObject* compileComponents(PumpkinSpiceInput pumpkinSpiceInput);
    PumpkinSpiceObject* compilePumpkinSpice(std::string pumkinFile, std::string styleFileName);
    void updatePumpkinSpice();
    void addFont(std::string fontFileName, std::string fontName);
    void setInput(UserInput* input);


    private:
    void initializeResolution(int x, int y);
    std::vector<Point> createSquareMesh(Point top, Point bottom, float z);
    unsigned char* createSquareTexture(int width, int height, Colour colour);
    void getStyleState(json style, std::vector<std::string> classes, Style& styleState);
    void iterateOverNode(xml_node<>* node, PumpkinSpiceObject* pumpkinSpiceObject, json style, std::vector<std::string> classes, Style styleState);
    std::string loadFile(std::string name);
    void drawText(Texture* newTexture, const stbtt_fontinfo font, int fontSize, std::string text);
    FontMap fonts;

    int xResolution;
    int yResolution;

    std::map<std::string, std::function<AbstractComponent*(AbstractComponentInput)>> componentFactorys;
    UserInput* input;
};

#endif