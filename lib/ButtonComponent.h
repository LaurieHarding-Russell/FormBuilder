#ifndef BUTTON_COMPONENT_H
#define BUTTON_COMPONENT_H

#include <functional>
#include "AbstractComponent.h"

class ButtonComponent: AbstractComponent {

    public:
    ButtonComponent(AbstractComponentInput* abstractComponentInput) : AbstractComponent(abstractComponentInput) {

    }

    std::function<void()> clickCallbackFunction;


    static AbstractComponent* ButtonComponentFactory(AbstractComponentInput* abstractComponentInput) {
        return new ButtonComponent(abstractComponentInput);
    };

    private:
    void mouseClickUp(int button) override {
        if (clickCallbackFunction) {
            clickCallbackFunction();
        }
    }
};

#endif