#include "AbstractComponent.h"


// public 
// FIXME, should everything inherit from abstract component even divs etc?
AbstractComponent::AbstractComponent(AbstractComponentInput* abstractComponentInput) {
    topLeft = abstractComponentInput->topLeft;
    bottomRight = abstractComponentInput->bottomRight;
    state.selected = false;
    state.hover = false;
    name = abstractComponentInput->name;
}

AbstractComponent::~AbstractComponent() {
    
}

ComponentState AbstractComponent::getState() {
    return state;
}

void AbstractComponent::mousePositionChange(Point point) {
    if(point.x > topLeft.x && point.x < bottomRight.x 
        && point.y > bottomRight.y && point.y  < topLeft.y) 
    {
        state.hover = true;
    } else {
        state.hover = false;
    }
}

void AbstractComponent::mouseClickDown(int button) {
    if (state.hover) {
        state.selected = true;
    }else {
        state.selected = false;
    }
}

void AbstractComponent::mouseClickUp(int button) {

}

void AbstractComponent::keyUp(char value) {

}

void AbstractComponent::keyDown(char value) {

}


Point AbstractComponent::getTopLeft() {
    return topLeft;
}

Point AbstractComponent::getBottomRight() {
    return bottomRight;
}

std::ostream& operator<<(std::ostream& os, const AbstractComponent& abstractComponent) {
    os << "Component { topLeft:: " << abstractComponent.topLeft
        << " bottomRight: " << abstractComponent.bottomRight
        << " name:" << abstractComponent.name << " }";
    return os;
}