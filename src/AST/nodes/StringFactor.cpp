#include "AST/nodes/StringFactor.hpp"

namespace YANKI {
  void StringFactor::accept(Visitor* v) {
      v->visitStringFactor(this);
  }

  const std::string& StringFactor::getValue() const {
      return value;
  }

  void StringFactor::setValue(const std::string& val) {
      value = val;
  }
}
