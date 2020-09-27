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
    Point topLeft;
    Point bottomRight;
    std::string name;
};

class AbstractComponent {
public:
    AbstractComponent(AbstractComponentInput* input);
    ~AbstractComponent();

    ComponentState getState();

    virtual void mousePositionChange(Point point);
    virtual void mouseClickDown(int button);
    virtual void mouseClickUp(int button);
    virtual void keyUp(char value);
    virtual void keyDown(char value);

    Point getTopLeft();
    Point getBottomRight();
    std::string name; // got to make setters getter but I'm lazy.
    
    PumpkinSpiceObject* pumpkinSpiceObject;

    friend std::ostream& operator<<(std::ostream& os, const AbstractComponent& abstractComponent);
protected:
    ComponentState state;

private:
    Point topLeft;
    Point bottomRight;
};
#endif
