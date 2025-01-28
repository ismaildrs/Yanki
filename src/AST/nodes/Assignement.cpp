#include "AST/nodes/Assignement.hpp"

namespace YANKI {

// Implementation of accept method
void Assignement::accept(Visitor* v) {
    if (v) v->visitAssignement(this);
}

// Getter for identifier
Visitable* Assignement::getIdentifier() const {
    return identifier;
}

// Getter for expression
Visitable* Assignement::getExpression() const {
    return expression;
}

// Setter for identifier
void Assignement::setIdentifier(Visitable* id) {
    if (identifier != id) {
        delete identifier;
        identifier = id;
    }
}

// Setter for expression
void Assignement::setExpression(Visitable* expr) {
    if (expression != expr) {
        delete expression;
        expression = expr;
    }
}

} // namespace YANKI
