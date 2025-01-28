#include "AST/nodes/Program.hpp"

namespace YANKI {
  void Program::accept(Visitor* v) {
      v->visitProgram(this);
  }

  const std::vector<Visitable*> Program::getChildren() const {
      return children;
  }

  void Program::addChild(Visitable* child) {
      children.push_back(child);
  }
}
