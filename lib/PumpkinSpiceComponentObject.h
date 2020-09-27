#ifndef PUMPKIN_SPICE_COMPONENT_OBJECT_H
#define PUMPKIN_SPICE_COMPONENT_OBJECT_H

#include "AbstractComponent.h"
#include "PumpkinSpiceObject.h"
#include <vector>

class PumpkinSpiceComponentObject {
    public: 
    std::vector<PumpkinSpiceObject*> getPumpkinSpiceRenderObjects() {
        std::vector<PumpkinSpiceObject*> pumpkinSpiceObject;
        pumpkinSpiceObject.push_back(basePumpkinSpiceObjects);
        return pumpkinSpiceObject;
    }
    
    std::vector<AbstractComponent*> abstractComponents;
    PumpkinSpiceObject* basePumpkinSpiceObjects;

};

#endif