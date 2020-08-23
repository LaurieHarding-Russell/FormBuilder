#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "AbstractComponent.h"

class InputComponent: AbstractComponent {
    public:
    InputComponent(AbstractComponentInput* abstractComponentInput) : AbstractComponent(abstractComponentInput) {

    }


    static AbstractComponent* InputComponentFactory(AbstractComponentInput* abstractComponentInput) {
        return new InputComponent(abstractComponentInput);
    };
};

#endif