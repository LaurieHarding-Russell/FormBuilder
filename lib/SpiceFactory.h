#ifndef SPICE_FACTORY_H
#define SPICE_FACTORY_H

#include "CommonTypes.h"
#include "Style.h"

#include <iostream>

// FIXME, enum
static float calculateMeasurment(const float measurment,const std::string measurmentStyle) {
    std::string unit = measurmentStyle.substr(measurmentStyle.length() - 1, measurmentStyle.length() - 1);
    float value = stof(measurmentStyle.substr(0, measurmentStyle.length() - 1));

    float newMeasurment = 0;
    if (unit == "%") {
        newMeasurment = measurment * (0.01 * value);
    } else {
        newMeasurment = measurment;
    }

    return newMeasurment;
}

static json getStyleState(const json style, std::vector<std::string> originalClasses, Style& styleState) {
    json untouchedStyle = style;
    std::vector<std::string> classes;
    copy(originalClasses.begin(), originalClasses.end(), back_inserter(classes));
        
    if (style.contains("background")) {
        styleState.backgroundColour.setColour(style.at("background"));
    }

    styleState.display = style.value("display", styleState.display);
    styleState.font = style.value("font", styleState.font);
    styleState.fontSize = style.value("fontSize", styleState.fontSize);
    if (style.contains("width")) {
        std::string widthStyle = style["width"];
        float newWidth = calculateMeasurment(styleState.width, widthStyle);
        // styleState.xResolution = (newWidth / styleState.width) * styleState.xResolution;
        styleState.width = newWidth;
    }
    if (style.contains("height")) {
        std::string heightStyle = style["height"];
        float newHeight = calculateMeasurment(styleState.width, heightStyle);
        styleState.yResolution = (newHeight / styleState.height) * styleState.yResolution;
        styleState.height = newHeight;
    }

    if(!classes.empty()) {
        std::string className = classes[0];
        classes.erase(classes.begin());
        if(style.contains(className)) {
            json subStyle = style[className];
            untouchedStyle = getStyleState(subStyle, classes, styleState);
        } else {
            getStyleState(style, classes, styleState);
        }
    }
    return untouchedStyle;
}

#endif