#ifndef AbstractComponent_h
#define AbstractComponent_h

#include<string>
#include "Input.h"
#include "CommonTypes.h"
#include <functional>
#include <queue>

enum MouseEvent {
    MOUSE_UP,
    MOUSE_DOWN,
    MOUSE_NONE
};

enum KeyboardEventType {
    KEYBOARD_UP,
    KEYBOARD_DOWN,
    KEYBOARD_NONE
};

struct KeyboardEvent {
    KeyboardEventType type;
    char value;
};

struct ComponentState {
    bool hover;
    bool selected;
};

class AbstractComponent; // forward declaration so the input can be in the same file.

struct AbstractComponentInput {
    UserInput* input;
    std::vector<AbstractComponent> subComponent;
    Point topLeft;
    Point bottomRight;
};

class AbstractComponent {
public:
    AbstractComponent(AbstractComponentInput* input);
    ~AbstractComponent();

    virtual void update();
    ComponentState getState();

    void mousePositionChange(Point point);
    void mouseClickDown();
    void mouseClickUp();
    void keyUp();
    void keyDown();
    

    ComponentState state;

    Point getTopLeft();
    Point getBottomRight();
protected:
    UserInput* input;
    
private:
    Point topLeft;
    Point bottomRight;
};

#endif
