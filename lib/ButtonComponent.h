#ifndef BUTTON_COMPONENT_H
#define BUTTON_COMPONENT_H

#include <functional>
#include "AbstractComponent.h"

class ButtonComponent: AbstractComponent {

    public:
    ButtonComponent(const AbstractComponentInput* abstractComponentInput) : AbstractComponent(abstractComponentInput) {

    }

    std::function<void()> clickCallbackFunction;


    static AbstractComponent* ButtonComponentFactory(const AbstractComponentInput* abstractComponentInput) {
        return new ButtonComponent(abstractComponentInput);
    };

    private:
    void mouseClickUp(const int button) override {
        if (state.hover) {
            if (clickCallbackFunction) {
                clickCallbackFunction();
            }
        }
    }
};

#endif