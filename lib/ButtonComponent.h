#ifndef BUTTON_COMPONENT_H
#define BUTTON_COMPONENT_H

#include "AbstractComponent.h"

class ButtonComponent: AbstractComponent {
    public:
    ButtonComponent(AbstractComponentInput* abstractComponentInput) : AbstractComponent(abstractComponentInput) {

    }

    static AbstractComponent* ButtonComponentFactory(AbstractComponentInput* abstractComponentInput) {
        return new ButtonComponent(abstractComponentInput);
    };
};

#endif