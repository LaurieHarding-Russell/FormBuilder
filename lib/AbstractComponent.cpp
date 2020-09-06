#include "AbstractComponent.h"


// public 
// FIXME, should everything inherit from abstract component even divs etc?
AbstractComponent::AbstractComponent(AbstractComponentInput* abstractComponentInput) {
    topLeft = abstractComponentInput->topLeft;
    bottomRight = abstractComponentInput->bottomRight;
}

AbstractComponent::~AbstractComponent() {

}

void AbstractComponent::registerInputFunction(UserInput* input) {
    this->input = input;
}

ComponentState AbstractComponent::getState() {
    return state;
}

void AbstractComponent::mousePositionChange(Point point) {
    if(point.x > topLeft.x && point.x < bottomRight.x 
        && point.y  > topLeft.y && point.y < bottomRight.y) 
    {
        state.hover = true;
    } else {
        state.hover = false;
    }
    if (state.hover && input->getMouseButtonDown) {
        state.selected = true;
    }else {
        state.selected = true;
    }
}

void mouseClickDown() {

}

void mouseClickUp() {

}

void keyUp() {

}

void keyDown() {

}


Point AbstractComponent::getTopLeft() {
    return topLeft;
}

Point AbstractComponent::getBottomRight() {
    return bottomRight;
}