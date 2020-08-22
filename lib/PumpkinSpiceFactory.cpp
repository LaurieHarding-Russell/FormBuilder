#include "PumpkinSpiceFactory.h"

PumpkinSpiceObject* PumpkinSpiceCompiler::compileComponents(PumpkinSpiceInput pumpkinSpiceInput) {
    return new PumpkinSpiceObject();
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

PumpkinSpiceCompiler::PumpkinSpiceCompiler() {
    initializeResolution(500, 500);
}

PumpkinSpiceCompiler::PumpkinSpiceCompiler(int x, int y) {
    initializeResolution(x, y);
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
    xml_attribute<char> * attribute = node->first_attribute("class");
    if (attribute != 0) {
        std::string elementClasses = attribute->value(); // FIXME, split on space add support for multiple
        classes.push_back(elementClasses);
    }

    styleState.zPosition = std::numeric_limits<float>::min();
    
    getStyleState(style, classes, styleState);
    Texture* newTexture = new Texture();
    newTexture->height = styleState.xResolution; // FIXME, calculate resolution.
    newTexture->width = styleState.yResolution;
    
    if (strcmp(node->name(),"") == 0) {
        newTexture->data = createSquareTexture(500, 500, Colour(0,0,0,0));
        // FIXME, tired need to think about this. probably should pop off the used json. Or maybe an entirely different approach.
        if (styleState.font != "") {        //     // think about this.
            const stbtt_fontinfo font = fonts["Bangers-Regular"]; //styleState.font];
            // FIXME, width height
            drawText(newTexture, font, 100, node->value());
        }
    } else {
        newTexture->data = createSquareTexture(500, 500, styleState.backgroundColour);
    }
    // hm
    Point topLeft(-1.0f, 1.0f);
    Point topRight(1.0f, -1.0f);
    pumpkinSpiceObject->meshes.push_back(createSquareMesh(topLeft, topRight, styleState.zPosition));
    pumpkinSpiceObject->textures.push_back(newTexture);

    for (xml_node<> *child = node->first_node(); child; child = child->next_sibling()) {
        if (child != 0) {
            iterateOverNode(child, pumpkinSpiceObject, style, classes, styleState);
        }
    }
}

std::vector<Point> PumpkinSpiceCompiler::createSquareMesh(Point topLeft, Point bottomRight, float zPosition) {
    std::vector<Point> verts {
        // triangle 1
        Point(topLeft.x, bottomRight.y, zPosition),
        Point(topLeft.x, topLeft.y, zPosition),
        Point(bottomRight.x, topLeft.y, zPosition),
        /// triangle 2
        Point(topLeft.x, bottomRight.y, zPosition),
        Point(bottomRight.x, topLeft.y, zPosition),
        Point(bottomRight.x, bottomRight.y, zPosition)
    };
    return verts;
}

unsigned char* PumpkinSpiceCompiler::createSquareTexture(int width, int height, Colour colour) {
    unsigned char* bitmap = new unsigned char[width * height * BYTES_PER_PIXEL];

    for (int y = 0; y != height; y++) {
        for (int x = 0; x != width; x++) {
            int numberOfCharacterInWidth = width * BYTES_PER_PIXEL;
            int pixelPosition = y * numberOfCharacterInWidth + x * BYTES_PER_PIXEL;
            bitmap[pixelPosition + 0] = colour.getRedChar();
            bitmap[pixelPosition + 1] = colour.getGreenChar();
            bitmap[pixelPosition + 2] = colour.getBlueChar();
            bitmap[pixelPosition + 3] = colour.getAlphaChar();
        }
    }
    return bitmap;
}


void PumpkinSpiceCompiler::getStyleState(json style, std::vector<std::string> originalClasses, Style& styleState) {

    std::vector<std::string> classes;
    copy(originalClasses.begin(), originalClasses.end(), back_inserter(classes));
        
    if (style.contains("background")) {
        styleState.backgroundColour.setColour(style.at("background"));    
    }

    styleState.display = style.value("display", styleState.display);
    styleState.font = style.value("font", styleState.font);

    if(!classes.empty()) {
        std::string className = classes[0];
        classes.erase(classes.begin());
        if(style.contains(className)) {
            json subStyle = style[className];
            getStyleState(subStyle, classes, styleState);
        } else {
            getStyleState(style, classes, styleState);
        }
    }
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

    Texture::flipYAxis(newTexture);
}