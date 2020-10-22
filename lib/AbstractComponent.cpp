#include "AbstractComponent.h"


// public 
// FIXME, should everything inherit from abstract component even divs etc?
AbstractComponent::AbstractComponent(const AbstractComponentInput* abstractComponentInput) {
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

void AbstractComponent::mousePositionChange(const glm::vec2 point) {
    if(point.x > topLeft.x && point.x < bottomRight.x 
        && point.y > bottomRight.y && point.y  < topLeft.y) 
    {
        state.hover = true;
    } else {
        state.hover = false;
    }
}

void AbstractComponent::mouseClickDown(const int button) {
    if (state.hover) {
        state.selected = true;
    }else {
        state.selected = false;
    }
}

void AbstractComponent::mouseClickUp(const int button) {

}

void AbstractComponent::keyUp(const char value) {

}

void AbstractComponent::keyDown(const char value) {

}


glm::vec3 AbstractComponent::getTopLeft() {
    return topLeft;
}

glm::vec3 AbstractComponent::getBottomRight() {
    return bottomRight;
}

std::ostream& operator<<(std::ostream& os, const AbstractComponent& abstractComponent) {
    os << "Component { "
        << " name:" << abstractComponent.name << " }";
    return os;
}