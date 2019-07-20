#include "AbstractComponent.h"


// public 
AbstractFormComponent::AbstractFormComponent() {
    setup("", "");
}

AbstractFormComponent::AbstractFormComponent(std::string templateCode) {
    setup(templateCode, "");
}

AbstractFormComponent::AbstractFormComponent(std::string templateCode, std::string style) {
    setup(templateCode, style);
}

AbstractFormComponent::~AbstractFormComponent() {

}

// protected
void AbstractFormComponent::render() {
    
}

// Private 
void AbstractFormComponent::setup(std::string templateCode, std::string style) {
    // parsedTemplate.parse(templateCode);
}