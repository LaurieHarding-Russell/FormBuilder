#ifndef BASIC_COMPONENT_H
#define BASIC_COMPONENT_H

#include "lib/AbstractComponent.h"

class BasicComponent: AbstractComponent {

    public:
    BasicComponent(AbstractComponent abstractComponentInput): AbstractComponent(abstractComponentInput) {

    } 

    static AbstractComponent* BasicComponentFactory(AbstractComponentInput abstractComponentInput) {
        return new BasicComponent(abstractComponentInput);
    };
};

#endif