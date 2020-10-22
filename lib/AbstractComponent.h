#ifndef AbstractComponent_h
#define AbstractComponent_h

#include "CommonTypes.h"

#include <string>
#include <queue>

#include <iostream>
#include "PumpkinSpiceObject.h"

struct ComponentState {
    bool hover;
    bool selected;
};

class AbstractComponent; // forward declaration so the input can be in the same file.

struct AbstractComponentInput {
    std::vector<AbstractComponent> subComponent;
    glm::vec3 topLeft;
    glm::vec3 bottomRight;
    std::string name;
};

class AbstractComponent {
public:
    AbstractComponent(const AbstractComponentInput* input);
    virtual ~AbstractComponent();

    ComponentState getState();

    virtual void mousePositionChange(glm::vec2 point);
    virtual void mouseClickDown(const int button);
    virtual void mouseClickUp(const int button);
    virtual void keyUp(const char value);
    virtual void keyDown(const char value);

    glm::vec3 getTopLeft();
    glm::vec3 getBottomRight();
    std::string name; // got to make setters getter but I'm lazy.
    
    PumpkinSpiceObject* pumpkinSpiceObject;

    friend std::ostream& operator<<(std::ostream& os, const AbstractComponent& abstractComponent);
protected:
    ComponentState state;

private:
    glm::vec3 topLeft;
    glm::vec3 bottomRight;

    AbstractComponent(AbstractComponent&); // Don't copy initialized Abstractomponents
    AbstractComponent& operator=(const AbstractComponent&);
};
#endif
