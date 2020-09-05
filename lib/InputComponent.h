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

    void update() {
        AbstractComponent::update();

        if (state.selected) {
            KeyboardEvent keyboardEvent = getKeyboardEvent();
            if (keyboardEvent.type == KeyboardEventType::KEYBOARD_DOWN) {
                if (keyboardEvent.value == 127 || keyboardEvent.value == 8) {
                    value = value.substr(0, value.size() - 1);
                } else {
                    value.push_back(keyboardEvent.value);
                }
            }
        }
    }

    static AbstractComponent* InputComponentFactory(AbstractComponentInput* abstractComponentInput) {
        return new InputComponent(abstractComponentInput);
    };

};

#endif