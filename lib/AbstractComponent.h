#ifndef AbstractComponent_h
#define AbstractComponent_h

#include "rapidxml.hpp"
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include<string>

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
    std::string style;
    std::string knownElements;
    rapidxml::xml_document<> parsedTemplate;

    bool top = false;

private:
    void setup(std::string templateCode, std::string style);
};

#endif
