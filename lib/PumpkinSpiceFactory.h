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

typedef std::map<std::string, stbtt_fontinfo> FontMap;
typedef std::pair<std::string, stbtt_fontinfo> FontPair;

const int BYTES_PER_PIXEL = 4; // r,g,b,a

class PumpkinSpiceCompiler {

    public:
    PumpkinSpiceObject* compileComponents(PumpkinSpiceInput pumpkinSpiceInput);
    PumpkinSpiceObject* compilePumpkinSpice(std::string pumkinFile, std::string styleFileName);
    void addFont(std::string fontFileName, std::string fontName);

    private:
    std::vector<Point> createSquareMesh(Point top, Point bottom);
    unsigned char* createSquareTexture(int width, int height, Colour colour);
    bool* createFontTexture();
    void getStyleState(json style, std::vector<std::string> classes, Style& styleState);
    void iterateOverNode(xml_node<>* node, PumpkinSpiceObject* pumpkinSpiceObject, json style, std::vector<std::string> classes, Style styleState);
    std::string loadFile(std::string name);
    unsigned char* drawText(const stbtt_fontinfo font, int fontSize, std::string text, int width, int height);
    FontMap fonts;

};

#endif