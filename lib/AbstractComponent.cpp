#include "AbstractComponent.h"


// public 
// FIXME, should everything inherit from abstract component even divs etc?
AbstractComponent::AbstractComponent(AbstractComponentInput abstractComponentInput) {

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
    // if (input) {

    // }
}