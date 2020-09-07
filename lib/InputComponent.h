#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "AbstractComponent.h"
#include <string>

class InputComponent: AbstractComponent {
    private:
    std::string value;
    
    public:
    InputComponent(AbstractComponentInput* abstractComponentInput) : AbstractComponent(abstractComponentInput) {

    }

    std::string returnValue() {
        return value;
    }

    void setValue() {

    }

    void keyDown(char keyValue) {
        AbstractComponent::keyDown(keyValue);
        if (state.selected) {
            if ((int)(keyValue) == 127 || (int)(keyValue) == 8) {
                // TODO, cursor support
                value = value.substr(0, value.size() - 1);
            } else {
                value.push_back(keyValue);
            }
        }
    }

    static AbstractComponent* InputComponentFactory(AbstractComponentInput* abstractComponentInput) {
        return new InputComponent(abstractComponentInput);
    };

};

#endif