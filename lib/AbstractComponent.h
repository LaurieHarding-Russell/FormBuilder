#ifndef AbstractComponent_h
#define AbstractComponent_h

#include "CommonTypes.h"

#include<string>
#include <queue>

#include <iostream>

struct ComponentState {
    bool hover;
    bool selected;
};

class AbstractComponent; // forward declaration so the input can be in the same file.

struct AbstractComponentInput {
    std::vector<AbstractComponent> subComponent;
    Point topLeft;
    Point bottomRight;
};

class AbstractComponent {
public:
    AbstractComponent(AbstractComponentInput* input);
    ~AbstractComponent();

    ComponentState getState();

    void mousePositionChange(Point point);
    void mouseClickDown();
    void mouseClickUp();
    void keyUp(char value);
    void keyDown(char value);

    Point getTopLeft();
    Point getBottomRight();
protected:
    ComponentState state;

private:
    Point topLeft;
    Point bottomRight;
};

#endif
