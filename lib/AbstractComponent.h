#ifndef AbstractComponent_h
#define AbstractComponent_h

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
    virtual std::string pumpkinFileName;
    virtual std::string styleFileName;
    std::string knownElements;
    rapidxml::xml_document<> parsedTemplate;

    // bool top = false; // FIXME, think about top component.

private:
    void setup(std::string templateCode);
};

#endif
