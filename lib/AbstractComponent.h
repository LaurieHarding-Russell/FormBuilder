#ifndef AbstractComponent_h
#define AbstractComponent_h

#include<string>
#include "Input.h"
#include "CommonTypes.h"

class AbstractComponent {
public:
    AbstractComponent(Point topLeft, Point bottomRight);
    ~AbstractComponent();

    void getClickEvent();
    void getState();

    std::string registerInputFunction() {

    }

protected:
    

private:
    void updateMouseLocation();
    void updateKeyboardEvents();
};

#endif
