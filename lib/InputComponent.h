#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "AbstractComponent.h"
#include <string>

class InputComponent: AbstractComponent {
    private:
    std::string value;
    
    public:
    InputComponent(const AbstractComponentInput* abstractComponentInput) : AbstractComponent(abstractComponentInput) {

    }

    std::string returnValue() {
        return value;
    }

    void setValue(const std::string value) {
        this->value = value;
    }

    void keyDown(const char keyValue) override {
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

    static AbstractComponent* InputComponentFactory(const AbstractComponentInput* abstractComponentInput) {
        return new InputComponent(abstractComponentInput);
    };

};

#endif