#ifndef PUMPKIN_SPICE_COMPONENT_OBJECT_H
#define PUMPKIN_SPICE_COMPONENT_OBJECT_H

#include "AbstractComponent.h"
#include "PumpkinSpiceObject.h"
#include <vector>

// FIXME, rename
class PumpkinSpiceComponentObject {
    public: 
    std::vector<AbstractComponent*> abstractComponents;
    std::vector<PumpkinSpiceObject*> pumpkinSpiceObjects;
};

#endif