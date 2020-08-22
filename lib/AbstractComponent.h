#ifndef AbstractComponent_h
#define AbstractComponent_h

#include<string>
#include "Input.h"
#include "CommonTypes.h"
#include <functional>

enum ComponentState {
    ACTIVE,
    INACTIVE,
    HOVER
};

class AbstractComponent; // forward declaration so the input can be in the same file.

struct AbstractComponentInput {
    Point topLeft;
    Point bottomRight;
    UserInput* input;
    std::vector<AbstractComponent> subComponent;
};

class AbstractComponent {
public:
    AbstractComponent(AbstractComponentInput input);
    ~AbstractComponent();

    virtual void update();
    ComponentState getState();

    void registerInputFunction(UserInput* input);

protected:
    

private:
    void updateMouseLocation();
    void updateKeyboardEvents();
    UserInput* input;
    ComponentState state;
};

#endif
