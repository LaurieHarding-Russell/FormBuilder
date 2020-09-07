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

    void callbackMouseButtonDownFunctions(int button) {
        for(AbstractComponent* component: components) {
            component->mouseClickDown(button);
        }
    }

    void callbackMouseButtonUpFunctions(int button) {
        for(AbstractComponent* component: components) {
            component->mouseClickUp(button);
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