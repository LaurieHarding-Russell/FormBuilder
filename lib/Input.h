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
    UserInput() {

    }
    
    ~UserInput() {

    }

    void callbackMousePosition(const Point value) {
        for(AbstractComponent* component: components) {
            component->mousePositionChange(value);
        }
    }

    void callbackMouseButtonDownFunctions(const int button) {
        for(AbstractComponent* component: components) {
            component->mouseClickDown(button);
        }
    }

    void callbackMouseButtonUpFunctions(const int button) {
        for(AbstractComponent* component: components) {
            component->mouseClickUp(button);
        }
    }

    void callbackKeyDown(const char value) {
        for(AbstractComponent* component: components) {
            component->keyDown(value);
        }
    }

    void callbackKeyUp(const char value) {
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