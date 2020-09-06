#ifndef INPUT_H
#define INPUT_H

#include <functional>
#include <vector>
#include "CommonTypes.h"

class UserInput {
    public:
    void callbackMousePosition(Point value) {
        for (int i = 0; i != callbackMousePositionFunctions.size(); i++) {
            callbackMousePositionFunctions.at(0)();
        }
    }

    void callbackMouseButtonDownFunctions() {
        for (int i = 0; i != callbackMouseButtonDownFunctions.size(); i++) {
            callbackMouseButtonDownFunctions.at(0)();
        }
    }

    void callbackMouseButtonUpFunctions() {
        for (int i = 0; i != callbackMouseButtonUpFunctions.size(); i++) {
            callbackMouseButtonUpFunctions.at(0)();
        }
    }

    void callbackKeyDown(char value) {
        for (int i = 0; i != callbackKeyDownFunctios.size(); i++) {
            callbackKeyDownFunctios.at(0)();
        }
    }

    void callbackKeyUp(char value) {
        for (int i = 0; i != callbackKeyUpFunctios.size(); i++) {
            callbackKeyUpFunctios.at(0)();
        }
    }



    private:
    std::vector<std::function<void(Point)>> callbackMousePositionFunctions;
    std::vector<std::function<void(bool)>> callbackMouseButtonDownFunctions;
    std::vector<std::function<void(bool)>> callbackMouseButtonUpFunctions;

    std::vector<std::function<void(char)>> callbackKeyDownFunctios;
    std::vector<std::function<void(char)>> callbackKeyUpFunctios;
};

#endif