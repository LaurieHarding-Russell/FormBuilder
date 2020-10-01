#ifndef PUMPKIN_SPICE_H
#define PUMPKIN_SPICE_H

#include "CommonUtils.h"
#include <vector>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>

#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

#include "Input.h"
#include "CommonTypes.h"
#include "Texture.h"
#include "PumpkinSpiceComponentObject.h"
#include "PumpkinSpiceObject.h"
#include <limits>
#include "AbstractComponent.h"
#include "InputComponent.h"
#include "ButtonComponent.h"
#include "PumpkinFactory.h"
#include "SpiceFactory.h"

struct PumpkinSpiceComponentInput {
    std::string name;
    std::string pumkinFileName;
    std::string spiceFileName;
    std::function<AbstractComponent*(AbstractComponentInput*)> componentFactory;
};

struct PumpkinSpiceInput {
    std::vector<PumpkinSpiceComponentInput> components;
    PumpkinSpiceComponentInput pumpkinSpiceComponentInput;
    std::string basePumkinFileName;
    std::string baseSpiceFileName;
};

struct PumpkinSpiceCompiledComponent {
    xml_node<>* componentPumpkin;
    json componentSpice;
    std::function<AbstractComponent*(AbstractComponentInput*)> componentFactory;
};

typedef std::map<std::string, stbtt_fontinfo> FontMap;
typedef std::pair<std::string, stbtt_fontinfo> FontPair;
typedef std::pair<std::string, PumpkinSpiceCompiledComponent*> ComponentPair;

// FIXME, rename
class PumpkinSpice {

    public:
    PumpkinSpice();
    PumpkinSpice(const int x,const  int y);
    ~PumpkinSpice();
    void compileComponents(const PumpkinSpiceInput pumpkinSpiceInput);
    void addFont(const std::string fontFileName, const std::string fontName);
    UserInput* getInput();

    AbstractComponent* getComponpentByName(const std::string name);
    PumpkinSpiceComponentObject* getPumpkinSpiceComponentObject();

    private:
    PumpkinSpiceObject* compilePumpkinSpice(const std::string pumkinFile, const std::string styleFileName);
    void initializeResolution(const int x, const int y);
    void iterateOverNode(xml_node<>* node, PumpkinSpiceObject* pumpkinSpiceObject, json style, std::vector<std::string> classes, const Style styleState);
    void getGeneratedCompponentByName();
    void calculatePosition();
    void addCurrentClass(xml_node<>* node, std::vector<std::string> classes);
    std::string getElementName(xml_node<>* node);

    FontMap fonts;
    int xResolution;
    int yResolution;
    std::vector<AbstractComponent*> generatedComponents;

    PumpkinSpiceComponentObject* pumpkinSpiceComponentObject;

    std::map<std::string, PumpkinSpiceCompiledComponent*> components;

    UserInput* input;
};

#endif