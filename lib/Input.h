#ifndef INPUT_H
#define INPUT_H

#include <functional>

class UserInput {
    public:
    std::function<double()> getMouseX;
    std::function<double()> getMouseY;
    std::function<bool()> getMouseButtonDown;
    std::function<bool()> getMouseButtonUp;

    std::function<int()> getKeyDown;
    std::function<int()> getKeyUp;
};

#endif