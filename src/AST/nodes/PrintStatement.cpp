#include "AST/nodes/PrintStatement.hpp"


namespace YANKI {
  void PrintStatement::accept(Visitor* v) {
      v->visitPrintStatement(this);
  }

  Visitable* PrintStatement::getExpression() const {
      return expression;
  }

  void PrintStatement::setExpression(Visitable* exp) {
      expression = exp;
  }
}
