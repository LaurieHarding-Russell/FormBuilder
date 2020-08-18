#include "PumpkinSpiceFactory.h"

PumpkinSpiceObject* PumpkinSpiceCompiler::compileComponents(PumpkinSpiceInput pumpkinSpiceInput) {
    return new PumpkinSpiceObject();
}

PumpkinSpiceObject* PumpkinSpiceCompiler::compilePumpkinSpice(std::string pumkinFile, std::string styleFileName) {

    // std::string xmlString = loadFile(pumkinFile);

    rapidxml::file<char> xmlFile = file<char>(pumkinFile.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    std::string jsonString = loadFile(styleFileName);

    json style = json::parse(jsonString);
    std::vector<std::string> classes = std::vector<std::string>();

    std::vector<std::string>::const_iterator first = classes.begin();
    std::vector<std::string>::const_iterator last = classes.end();
    std::vector<std::string> itterableClasses(first, last);

    PumpkinSpiceObject* pumpkinSpiceObject = new PumpkinSpiceObject();
    xml_node<>* pumpkinXML = doc.first_node("pumpkin");

    if (pumpkinXML == 0) {
        std::cout << "invald xml\n";
    }
    Style styleState = Style();
    getStyleState(style, itterableClasses, styleState);
    iterateOverNode(pumpkinXML, pumpkinSpiceObject, style, std::vector<std::string>(), styleState);

    return pumpkinSpiceObject;
}

std::string PumpkinSpiceCompiler::loadFile(std::string name) {
    std::string jsonString = "";
    std::ifstream styleFile (name);

    if (styleFile.is_open()) {
        std::string line;
        while ( getline(styleFile, line) ) {
            jsonString += line;
        }
        styleFile.close();
    }
    return jsonString;
}

// FIXME, so many pararms!!
void PumpkinSpiceCompiler::iterateOverNode(xml_node<>* node, PumpkinSpiceObject* pumpkinSpiceObject, json style, std::vector<std::string> classes, Style styleState) {
    // std::cout << *node;
    // std::cout << node->name();
    if (node->name() == "") {
        // FIXME, tired need to think about this. probably should pop off the used json. Or maybe an entirely different approach.
        getStyleState(style, classes, styleState);
        // pumpkinSpiceObject->mesh 
        return;
    }
    for (xml_node<> *child = node->first_node(); child; child = child->next_sibling()) {
        if (child != 0) {
            xml_attribute<char> * attribute = child->first_attribute("class");
            if (attribute != 0) {
                std::string elementClasses = attribute->value();
            }
            iterateOverNode(child, pumpkinSpiceObject, style, classes, styleState);
        }
    }
}

float* PumpkinSpiceCompiler::createSquareMesh(Point topLeft, Point bottomRight) {
    float verts[12] = {
        // triangle 1
        topLeft.x, bottomRight.y,
        topLeft.x, topLeft.y,
        bottomRight.x, topLeft.y,
        // triangle 2
        topLeft.x, bottomRight.y,
        bottomRight.x, topLeft.y,
        bottomRight.x, bottomRight.y
    };
    return verts;
}


void PumpkinSpiceCompiler::getStyleState(json style, std::vector<std::string> classes, Style& styleState) {

    styleState.font = style.value("font", styleState.font);

    if(!classes.empty()) {
        std::string className = classes[0];
        classes.erase(classes.begin());
        if(style.contains(className)) {
            json subStyle = style[className];
            getStyleState(subStyle, classes, styleState);
        }
        getStyleState(style, classes, styleState);
    }
}