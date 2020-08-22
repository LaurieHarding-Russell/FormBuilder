#ifndef INPUT_H
#define INPUT_H

#include <functional>

class UserInput {
    public:
    std::function<double()> getMouseX;
    std::function<double()> getMouseY;
    std::function<bool()> getMouseButtonDown;
    std::function<bool()> getMouseButtonUp;

    std::function<int()> keyPressDown;
    std::function<int()> keyPressUp;
};

#endif