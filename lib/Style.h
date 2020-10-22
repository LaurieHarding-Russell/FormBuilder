#ifndef STYLE_H
#define STYLE_H

#include "CommonTypes.h"

// FIXME, inherted from openGL. Think about this as a default coordinate system. Also naming
const glm::vec3 TOP_LEFT(-1.0f, 1.0f, 0.0f);
const glm::vec3 BOTTOM_RIGHT(1.0f, -1.0f, 0.0f);

enum StyleDisplay {
    INLINE,
    BLOCK,
    GRID,
    FLEX
};

enum Position {
    ABSOLUTE,
    RELATIVE
};

struct Style {
    Position position;
    StyleDisplay display;
    float topOffset;
    float leftOffset;
    float bottomOffset;
    float rightOffset;
    std::string font;
    int fontSize;
    Colour backgroundColour;
    Colour fontColour;
    float zPosition;
    float width;
    float height;
    int xResolution;
    int yResolution;
    glm::vec3 formCursor;

    Style() {
        this->display = BLOCK;
        this->topOffset = 0;
        this->leftOffset = 0;
        this->bottomOffset = 0;
        this->rightOffset = 0;
        this->font = "";
        this->fontSize = 25;
        this->backgroundColour = Colour(1.0f, 1.0f, 1.0f, 1.0f);
        this->fontColour = Colour(0.0f, 0.0f, 0.0f, 1.0f);
        this->xResolution = 500;
        this->yResolution = 500;
        this->width = 2.0f;
        this->height = 2.0f;
        this->formCursor = TOP_LEFT;
    }

    Style(const Style& style) {
        this->display = style.display;
        this->topOffset = style.topOffset;
        this->leftOffset = style.leftOffset;
        this->bottomOffset = style.bottomOffset;
        this->rightOffset = style.rightOffset;
        this->font = style.font;
        this->fontSize = style.fontSize;
        this->backgroundColour = style.backgroundColour;
        this->fontColour = style.fontColour;
        this->xResolution = style.xResolution;
        this->yResolution = style.yResolution;
        this->width = style.width;
        this->height = style.height;
        this->formCursor = style.formCursor;
    }

    friend std::ostream& operator<<(std::ostream& os, const Style& style) {
        os << "Style{ \n" 
            << "display " << style.display << "\n"
            << "topOffset " << style.topOffset << "\n"
            << "leftOffset " << style.leftOffset << "\n"
            << "bottomOffset " << style.bottomOffset << "\n"
            << "rightOffset " << style.rightOffset << "\n"
            << "font " << style.font << "\n"
            << "backgroundColour " << style.backgroundColour << "\n"
            << "fontColour " << style.fontColour << "\n"
            << "zPosition" << style.zPosition << "\n"
            << "}\n";
        return os;
    }
};

#endif