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

void AbstractComponent::update() {
    if (input) {
        if(input->getMouseX() > topLeft.x && input->getMouseY() < bottomRight.x) {
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
}

// FIXME, think about this. To much abstraction? Is it worth it?
MouseEvent AbstractComponent::getMouseEvent() {
    if (input->getMouseButtonDown()) {
        return MouseEvent::MOUSE_DOWN;
    }
    if (input->getMouseButtonUp()) {
        return MouseEvent::MOUSE_UP;
    }
    return MouseEvent::MOUSE_NONE;
}

KeyboardEvent AbstractComponent::getKeyboardEvent() {
    KeyboardEvent event;
    if (input->getKeyDown() != 0) {
        event.type = KeyboardEventType::KEYBOARD_DOWN;
        event.value = (char) input->getKeyDown();
        return event;
    }
    if (input->getKeyUp() != 0) {
        event.type = KeyboardEventType::KEYBOARD_UP;
        event.value = (char) input->getKeyUp();
        return event;
    }
    event.type = KeyboardEventType::KEYBOARD_NONE;
    return event;
}


Point AbstractComponent::getTopLeft() {
    return topLeft;
}

Point AbstractComponent::getBottomRight() {
    return bottomRight;
}