#include "AST/nodes/Statement.hpp"

namespace YANKI {
  void Statement::accept(Visitor* v) {
      v->visitStatement(this);
  }

  const std::vector<Visitable*>& Statement::getChildren() const {
      return children;
  }

  void Statement::addChild(Visitable* child) {
      children.push_back(child);
  }
}
