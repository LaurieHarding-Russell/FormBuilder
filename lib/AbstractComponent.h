#ifndef AbstractComponent_h
#define AbstractComponent_h

#include "rapidxml.hpp"
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include<string>
#include "pumpkinSpice.h"

class AbstractFormComponent {
public:
    AbstractFormComponent();
    AbstractFormComponent(bool isTop);
    AbstractFormComponent(std::string templateCode);
    AbstractFormComponent(std::string templateCode, std::string style);

    virtual void render();

    ~AbstractFormComponent();

protected:
    std::string templateCode;
    std::string style = "default.style";
    std::string knownElements;
    rapidxml::xml_document<> parsedTemplate;

    // bool top = false; // FIXME, think about top component.

private:
    void setup(std::string templateCode);
};

#endif
