#include "PumpkinSpice.h"

PumpkinSpice::PumpkinSpice() {
    PumpkinSpice(500,500);
}

PumpkinSpice::PumpkinSpice(const int xResolution, const int yResolution) {
    initializeResolution(xResolution, yResolution);

    PumpkinSpiceCompiledComponent* inputCompiledObject = new PumpkinSpiceCompiledComponent();
    inputCompiledObject->componentFactory = InputComponent::InputComponentFactory;
    inputCompiledObject->componentSpice = json{};
    inputCompiledObject->componentPumpkin = 0;

    PumpkinSpiceCompiledComponent* buttonCompiledObject = new PumpkinSpiceCompiledComponent();
    buttonCompiledObject->componentSpice = json{};
    buttonCompiledObject->componentFactory = ButtonComponent::ButtonComponentFactory;
    inputCompiledObject->componentPumpkin = 0;

    components.insert(ComponentPair("input", inputCompiledObject));
    components.insert(ComponentPair("button", buttonCompiledObject));

    input = new UserInput();
    pumpkinSpiceComponentObject = new PumpkinSpiceComponentObject();
}

PumpkinSpice::~PumpkinSpice() {
    for(AbstractComponent* component: generatedComponents) {
        delete component;
    }
    // delete input;
}

void PumpkinSpice::compileComponents(const PumpkinSpiceInput pumpkinSpiceInput) {

    for (uint i = 0; i != pumpkinSpiceInput.components.size(); i++) {
        // FIXME, nameing, wording fix everywhere :) sorry future self.
        rapidxml::file<char> xmlFile = file<char>(pumpkinSpiceInput.components.at(i).pumkinFileName.c_str());
        rapidxml::xml_document<> pumpkin;
        
        pumpkin.parse<0>(xmlFile.data());
        std::string spiceString = util::loadFileToString(pumpkinSpiceInput.components.at(i).spiceFileName.c_str());

        json spice = json::parse(spiceString);

        PumpkinSpiceCompiledComponent* compiledObject = new PumpkinSpiceCompiledComponent();
        compiledObject->componentFactory = pumpkinSpiceInput.components.at(i).componentFactory;
        compiledObject->componentPumpkin = pumpkin.first_node();
        compiledObject->componentSpice = spice;
        components.insert(ComponentPair(pumpkinSpiceInput.components.at(i).name, compiledObject));
    }
    PumpkinSpiceObject* pumpkinSpiceObject = compilePumpkinSpice(pumpkinSpiceInput.basePumkinFileName, pumpkinSpiceInput.baseSpiceFileName);

    pumpkinSpiceComponentObject->basePumpkinSpiceObjects = pumpkinSpiceObject;
    input->setComponents(generatedComponents);
    // THINK, pumpkinSpiceComponentObject->abstractComponents = generatedComponents plus input->setComponents breaks pumpkinSpiceComponentObject->pumpkinSpiceObjects[0]->meshes.size() if it happens before... don't understand.
    pumpkinSpiceComponentObject->abstractComponents = generatedComponents;
}

AbstractComponent* PumpkinSpice::getComponpentByName(std::string name) {
    // FIXME, should this be a map?
    for(AbstractComponent* component: generatedComponents) {
        if(component->name == name) {
            return component;
        }
    }
    throw std::invalid_argument("Can't find component of name " + name + "\n");
}

PumpkinSpiceObject* PumpkinSpice::compilePumpkinSpice(const std::string pumkinFile, const std::string styleFileName) {
    rapidxml::file<char> xmlFile = file<char>(pumkinFile.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    std::string jsonString = util::loadFileToString(styleFileName);

    json style = json::parse(jsonString);
    std::vector<std::string> classes = std::vector<std::string>();

    std::vector<std::string>::const_iterator first = classes.begin();
    std::vector<std::string>::const_iterator last = classes.end();
    std::vector<std::string> itterableClasses(first, last);

    PumpkinSpiceObject* pumpkinSpiceObject = new PumpkinSpiceObject();
    xml_node<>* pumpkinXML = doc.first_node("pumpkin");

    if (pumpkinXML == 0) {
        throw std::logic_error("invald xml\n");
    }
    Style styleState = Style();

    IterateNodeState iterateNodeState;
    iterateNodeState.node = pumpkinXML;
    iterateNodeState.pumpkinSpiceObject = pumpkinSpiceObject; 
    iterateNodeState.style = style;
    iterateNodeState.classes = std::vector<std::string>();
    iterateNodeState.parentStyleState = styleState;
    iterateOverNode(iterateNodeState);
    return pumpkinSpiceObject;
}


void PumpkinSpice::addFont(const std::string fontFileName, const std::string fontName) {
    unsigned char* fontBuffer = util::loadFileToUnsignedChar(fontFileName);
    stbtt_fontinfo font;
    stbtt_InitFont(&font, fontBuffer, 0);
    fonts.insert(FontPair(fontName, font));
}

void PumpkinSpice::initializeResolution(const int x, const int y) {
    xResolution = x;
    yResolution = y;
}

UserInput* PumpkinSpice::getInput() {
    return input;
}

PumpkinSpiceComponentObject* PumpkinSpice::getPumpkinSpiceComponentObject() {
    return pumpkinSpiceComponentObject;
}

// FIXME, so many pararms!!
void PumpkinSpice::iterateOverNode(IterateNodeState iterateNodeState) {
    Style styleState = Style(iterateNodeState.parentStyleState);
    // FIXME
    if (iterateNodeState.node == 0) {
        return;
    }

    addCurrentClass(iterateNodeState.node, iterateNodeState.classes);

    styleState.formCursor.z = styleState.formCursor.z + std::numeric_limits<float>::min();
    iterateNodeState.style = getStyleState(iterateNodeState.style, iterateNodeState.classes, styleState);
    // THINK, maybe it should always just be alpha unless class applying background has the colour.
    Texture* newTexture = Texture::createSquareTexture(styleState.xResolution, styleState.yResolution, Colour(0,0.0,0,0.0));

    if (strcmp(iterateNodeState.node->name(),"") == 0) {
        if (styleState.font != "") {        // think about this. default font?
            const stbtt_fontinfo font = fonts[styleState.font];
            Texture::drawText(newTexture, font, styleState.fontSize, iterateNodeState.node->value());
            
        }
    } else {
        newTexture = Texture::createSquareTexture(styleState.xResolution, styleState.yResolution, styleState.backgroundColour);
    }

    glm::vec3 myTopLeft(styleState.formCursor);
    glm::vec3 myBottomRight(styleState.formCursor.x + styleState.width, styleState.formCursor.y - styleState.height, styleState.formCursor.z);

    // styleState.formCursor.x = styleState.formCursor.x + styleState.width;

    iterateNodeState.pumpkinSpiceObject->meshes.push_back(createSquareMesh(myTopLeft, myBottomRight));
    iterateNodeState.pumpkinSpiceObject->textures.push_back(newTexture);

    for (xml_node<> *child = iterateNodeState.node->first_node(); child; child = child->next_sibling()) {
        if (child != 0) {
            std::string tag = child->name();
            if (components.find(tag) != components.end()) {
                std::string name = getElementName(child);

                PumpkinSpiceCompiledComponent* component = components.at(tag);
                // FIXME, shadow peircing.
                IterateNodeState newIterateNodeState(iterateNodeState);
                newIterateNodeState.node = component->componentPumpkin;
                newIterateNodeState.style = component->componentSpice;
                newIterateNodeState.classes = std::vector<std::string>();
                newIterateNodeState.parentStyleState = styleState;
                iterateOverNode(newIterateNodeState);
                AbstractComponentInput* abstractComponentInput = new AbstractComponentInput();
                abstractComponentInput->topLeft = myTopLeft;
                abstractComponentInput->bottomRight = myBottomRight;
                abstractComponentInput->name = name;
                generatedComponents.push_back(component->componentFactory(abstractComponentInput));
                delete abstractComponentInput;
                
                iterateNodeState.style[tag] = components.at(tag)->componentSpice;
            } else{
                IterateNodeState newIterateNodeState(iterateNodeState);
                newIterateNodeState.node = child;
                newIterateNodeState.parentStyleState = styleState;
                iterateOverNode(newIterateNodeState);
            }
        }
        // fixme, check if fits?
        // overflow style?
        // TODO: padding/margin
        // function of style?
        // if (styleState.formCursor.x + styleState.width > BOTTOM_RIGHT.x) {
            // styleState.formCursor.x = TOP_LEFT.x;
            styleState.formCursor.y = styleState.formCursor.y - styleState.height;
        // }
    }
}

void PumpkinSpice::addCurrentClass(xml_node<>* node, std::vector<std::string> classes) {
    xml_attribute<char> * attributeClass = node->first_attribute("class");
    if (attributeClass != 0) {
        std::string elementClasses = attributeClass->value(); // FIXME, split on space add support for multiple
        classes.push_back(elementClasses);
    }
}

std::string PumpkinSpice::getElementName(xml_node<>* node) {
    xml_attribute<char> * attributeName = node->first_attribute("name");
    if (attributeName != 0) {
        return attributeName->value();
    }
    return "";
}