#ifndef INPUT_H
#define INPUT_H

#include <functional>
#include <vector>
#include "AbstractComponent.h"

#include <iostream>

class UserInput {
    private:
    std::vector<AbstractComponent*> components;

    public:

    void callbackMousePosition(Point value) {
        for(AbstractComponent* component: components) {
            component->mousePositionChange(value);
        }
    }

    void callbackMouseButtonDownFunctions() {
        for(AbstractComponent* component: components) {
            component->mouseClickDown();
        }
    }

    void callbackMouseButtonUpFunctions() {
        for(AbstractComponent* component: components) {
            component->mouseClickUp();
        }
    }

    void callbackKeyDown(char value) {
        for(AbstractComponent* component: components) {
            component->keyDown(value);
        }
    }

    void callbackKeyUp(char value) {
        for(AbstractComponent* component: components) {
            component->keyUp(value);
        }
    }

// THINK, maybe I shouldn't have state in this class. Make it utility only.
    void setComponents(std::vector<AbstractComponent*> components) {
        this->components = components;
    }
};

#endif