#include "AST/nodes/Identifier.hpp"


namespace YANKI {
  Identifier::Identifier(std::string name) : varname(name){}

  void Identifier::accept(Visitor* v) {
      v->visitIdentifier(this);
  }

  const std::string& Identifier::getVarName() const {
      return varname;
  }

  void Identifier::setVarName(const std::string& name) {
      varname = name;
  }
}
