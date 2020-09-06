#include "PumpkinSpiceFactory.h"

PumpkinSpiceCompiler::PumpkinSpiceCompiler() {
    PumpkinSpiceCompiler(500,500);
}

PumpkinSpiceCompiler::PumpkinSpiceCompiler(int xResolution, int yResolution) {
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
}

PumpkinSpiceComponentObject* PumpkinSpiceCompiler::compileComponents(PumpkinSpiceInput pumpkinSpiceInput) {
    PumpkinSpiceComponentObject* pumpkinSpiceComponentObject = new PumpkinSpiceComponentObject();

    for (uint i = 0; i != pumpkinSpiceInput.components.size(); i++) {
        // FIXME, nameing, wording fix everywhere :) sorry future self.
        rapidxml::file<char> xmlFile = file<char>(pumpkinSpiceInput.components.at(i).pumkinFileName.c_str());
        rapidxml::xml_document<> pumpkin;
        
        pumpkin.parse<0>(xmlFile.data());
        std::string spiceString = loadFile(pumpkinSpiceInput.components.at(i).spiceFileName.c_str());

        json spice = json::parse(spiceString);

        PumpkinSpiceCompiledComponent* compiledObject = new PumpkinSpiceCompiledComponent();
        compiledObject->componentFactory = pumpkinSpiceInput.components.at(i).componentFactory;
        compiledObject->componentPumpkin = pumpkin.first_node();
        compiledObject->componentSpice = spice;
        components.insert(ComponentPair(pumpkinSpiceInput.components.at(i).name, compiledObject));
    }
    PumpkinSpiceObject* pumpkinSpiceObject = compilePumpkinSpice(pumpkinSpiceInput.basePumkinFileName, pumpkinSpiceInput.baseSpiceFileName);

    // FIXME, should we even send this back? Or should interaction be threw the factory? might need to rename the factory.
    pumpkinSpiceComponentObject->abstractComponents = generatedComponents;
    pumpkinSpiceComponentObject->pumpkinSpiceObjects.push_back(pumpkinSpiceObject);
    return pumpkinSpiceComponentObject;
}

void PumpkinSpiceCompiler::updatePumpkinSpice() {

}

PumpkinSpiceObject* PumpkinSpiceCompiler::compilePumpkinSpice(std::string pumkinFile, std::string styleFileName) {
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

    iterateOverNode(pumpkinXML, pumpkinSpiceObject, style, std::vector<std::string>(), styleState);

    return pumpkinSpiceObject;
}

void PumpkinSpiceCompiler::addFont(std::string fontFileName, std::string fontName) {
    unsigned char* fontBuffer;

    std::ifstream file(fontFileName, std::ios::binary);
	if (!file.is_open()) {
        exit(1);
    }
    file.seekg(0, std::ios::end);
    unsigned long int fontBufferSize = (unsigned long int)file.tellg();
    file.close();
    fontBuffer = new unsigned char[fontBufferSize];
    fread(fontBuffer, 1, 1<<25, fopen(fontFileName.c_str(), "rb"));
    stbtt_fontinfo font;
    stbtt_InitFont(&font, fontBuffer, 0);
    fonts.insert(FontPair(fontName, font));
}

void PumpkinSpiceCompiler::setInput(UserInput* input) {
    this->input = input;
}

PumpkinSpiceCompiler::~PumpkinSpiceCompiler() {

}

void PumpkinSpiceCompiler::initializeResolution(int x, int y) {
    xResolution = x;
    yResolution = y;
}

std::string PumpkinSpiceCompiler::loadFile(std::string name) {
    std::string data = "";
    std::ifstream file (name);

    if (file.is_open()) {
        std::string line;
        while ( getline(file, line) ) {
            data += line + '\n';
        }
        file.close();
    }
    return data;
}

// FIXME, so many pararms!!
void PumpkinSpiceCompiler::iterateOverNode(xml_node<>* node, PumpkinSpiceObject* pumpkinSpiceObject, json style, std::vector<std::string> classes, Style styleState) {
    // FIXME
    if (node == 0) {
        return;
    }
    xml_attribute<char> * attribute = node->first_attribute("class");
    if (attribute != 0) {
        std::string elementClasses = attribute->value(); // FIXME, split on space add support for multiple
        classes.push_back(elementClasses);
    }

    styleState.formCursor.z = styleState.formCursor.z + std::numeric_limits<float>::min();
    style = getStyleState(style, classes, styleState);
    Texture* newTexture = Texture::createSquareTexture(styleState.xResolution, styleState.yResolution, Colour(0,0,0,0));

    if (strcmp(node->name(),"") == 0) {
        // FIXME, tired need to think about this. probably should pop off the used json. Or maybe an entirely different approach.
        if (styleState.font != "") {        //     // think about this.
            const stbtt_fontinfo font = fonts[styleState.font]; //styleState.font];
            // FIXME, width height
            drawText(newTexture, font, styleState.fontSize, node->value());
        }
    } else {
        std::cout << "styleState.backgroundColour:" << styleState.backgroundColour << '\n';
        newTexture = Texture::createSquareTexture(styleState.xResolution, styleState.yResolution, styleState.backgroundColour);
    }

    // fixme, check if fits?
    // overflow style?
    // TODO: padding/margin
    // function of style?
    if (styleState.formCursor.x + styleState.width > BOTTOM_RIGHT.x) {
        styleState.formCursor.x = TOP_LEFT.x;
        styleState.formCursor.y = styleState.formCursor.y - styleState.height;
    }

    Point myTopLeft(styleState.formCursor.x, styleState.formCursor.y, styleState.formCursor.z);
    Point myBottomRight(styleState.formCursor.x + styleState.width, styleState.formCursor.y - styleState.height, styleState.formCursor.z);

    styleState.formCursor.x = styleState.formCursor.x + styleState.width;

    // std::cout << myTopLeft << '\n';
    // std::cout << myBottomRight << "\n\n";

    pumpkinSpiceObject->meshes.push_back(createSquareMesh(myTopLeft, myBottomRight));
    pumpkinSpiceObject->textures.push_back(newTexture);

    for (xml_node<> *child = node->first_node(); child; child = child->next_sibling()) {
        if (child != 0) {
            std::string tag = child->name();
            if (components.find(tag) != components.end()) {
                PumpkinSpiceCompiledComponent* component = components.at(tag);
                // FIXME, shadow peircing.
                Style subStyleState = Style();
                subStyleState.width = styleState.width;
                subStyleState.height = styleState.height;
                subStyleState.formCursor = styleState.formCursor;
                iterateOverNode(component->componentPumpkin, pumpkinSpiceObject, component->componentSpice, std::vector<std::string>(), subStyleState);
                AbstractComponentInput* abstractComponentInput = new AbstractComponentInput();
                abstractComponentInput->topLeft = myTopLeft;
                abstractComponentInput->bottomRight = myBottomRight;
                generatedComponents.push_back(component->componentFactory(abstractComponentInput));
                delete abstractComponentInput;
                
                style[tag] = components.at(tag)->componentSpice;
            } else{
                iterateOverNode(child, pumpkinSpiceObject, style, classes, styleState);
            }
        }
    }
}

std::vector<Point> PumpkinSpiceCompiler::createSquareMesh(Point topLeft, Point bottomRight) {
    std::vector<Point> verts {
        // triangle 1
        Point(topLeft.x, bottomRight.y, topLeft.z),
        Point(topLeft.x, topLeft.y, topLeft.z),
        Point(bottomRight.x, topLeft.y, topLeft.z),
        /// triangle 2
        Point(topLeft.x, bottomRight.y, topLeft.z),
        Point(bottomRight.x, topLeft.y, topLeft.z),
        Point(bottomRight.x, bottomRight.y, topLeft.z)
    };
    return verts;
}

// FIXME, need to really think about this. Probably want to check out how browser did it.
Point calculatePosition(Style styleState) {
    // switch(styleState.display) {

    // }
    
    // switch(styleState.display) {
    //     case StyleDisplay.INLINE:
    //     break;
    //     case StyleDisplay.:
    // }
}

void PumpkinSpiceCompiler::drawText(Texture* newTexture, const stbtt_fontinfo font, int fontSize, std::string text) {
    unsigned char* bitmap = newTexture->data;

    int height = newTexture->height;
    int width = newTexture->width;
    float scale = stbtt_ScaleForPixelHeight(&font, fontSize);
    int ascent = 0;
    int decent = 0;
    int lineGap = 0;

    stbtt_GetFontVMetrics(&font, &ascent, &decent, &lineGap);
    int totalHeight = ascent + decent + lineGap; // ascent hight of character above 'baseline' decent hieght of character below. lineGap = space between lines. 

    int fullLength; 
    int baseline = ascent*scale;

    int xCursor = 0;
    for (int i = 0; i != text.size(); i++) {
        int advance; // width of character including font padding. Yup font are pretentious. 
        int leftSideBearing; // left margin essentially.
        int x0, y0; // top left corner? 
        int x1, y1; // bottom right corner?

        stbtt_GetCodepointHMetrics(&font, text[i], &advance, &leftSideBearing);
        stbtt_GetCodepointBitmapBox(&font, text[i], scale, scale, &x0, &y0, &x1, &y1);

        int y = ascent + y1;
        int byteOffset = xCursor + x0 + (y * width);

        stbtt_MakeCodepointBitmap(&font,
                                    bitmap + byteOffset,
                                    BYTES_PER_PIXEL*(x1-x0),
                                    BYTES_PER_PIXEL*(y1-y0),
                                    width*BYTES_PER_PIXEL,
                                    2*scale, 
                                    scale,
                                    text[i]);

        xCursor += (advance * scale) + x1;
    }
    // FIXME, weird hacky stuff is happening because of this.
    Texture::flipYAxis(newTexture);
}