#ifndef INPUT_H
#define INPUT_H

#include <functional>
#include <vector>
#include "CommonTypes.h"

class UserInput {
    public:
    void callbackMousePosition(Point value) {
        for (int i = 0; i != components.size(); i++) {
            callbackMousePositionFunctions.at(0)();
        }
    }

    void callbackMouseButtonDownFunctions() {
        for (int i = 0; i != components.size(); i++) {
            callbackMouseButtonDownFunctions.at(0)();
        }
    }

    void callbackMouseButtonUpFunctions() {
        for (int i = 0; i != components.size(); i++) {
            callbackMouseButtonUpFunctions.at(0)();
        }
    }

    void callbackKeyDown(char value) {
        for (int i = 0; i != components.size(); i++) {
            callbackKeyDownFunctios.at(0)();
        }
    }

    void callbackKeyUp(char value) {
        for (int i = 0; i != components.size(); i++) {
            callbackKeyUpFunctios.at(0)();
        }
    }



    private:
    std::vector<AbstractComponent> components;
};

#endif