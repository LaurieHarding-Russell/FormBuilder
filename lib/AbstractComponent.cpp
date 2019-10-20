#include "AbstractComponent.h"


// public 
AbstractFormComponent::AbstractFormComponent() {
    setup("");
}

AbstractFormComponent::AbstractFormComponent(std::string templateCode) {
    setup(templateCode);
}

AbstractFormComponent::AbstractFormComponent(std::string templateCode, std::string style) {
    this->style = style;
    setup(templateCode);
}

AbstractFormComponent::~AbstractFormComponent() {

}

// protected
void AbstractFormComponent::render() {
    
}

// Private 
void AbstractFormComponent::setup(std::string templateCode) {
    if(!(yyin = fopen(this.style, "r"))) {
        perror(argv[1]);
        return (1);
    }
    std::cout << yyparse() << "\n";
    // parsedTemplate.parse(templateCode);
}
