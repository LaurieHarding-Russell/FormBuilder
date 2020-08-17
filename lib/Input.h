#ifndef INPUT_H
#define INPUT_H

#include <functional>

class MouseInput {
    public:
    std::function<double()> getMouseX;
    std::function<double()> getMouseY;
};

class KeyboardInput {
    public:
    std::function<int()> keyPressDown;
    std::function<int()> keyPressUp;
};

#endif