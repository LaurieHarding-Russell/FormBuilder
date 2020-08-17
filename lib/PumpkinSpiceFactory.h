#ifndef PUMPKIN_SPICE_H
#define PUMPKIN_SPICE_H

#include "CommonTypes.h"

#include <string>

class PumpkinSpiceCompiler {

    public:
    PumpkinSpiceObject* compileComponents(PumpkinSpiceInput pumpkinSpiceInput);


    PumpkinSpiceObject* compilePumpkinSpice(std::string pumkinFile, std::string style);

    private:
    float* createSquareMesh(Point top, Point bottom);
    bool* createFontTexture();

};

#endif