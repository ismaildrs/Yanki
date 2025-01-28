#include "AST/nodes/IntegerFactor.hpp"

namespace YANKI {
  void IntegerFactor::accept(Visitor* v) {
      v->visitIntegerFactor(this);
  }

  int IntegerFactor::getValue() const {
      return value;
  }

  void IntegerFactor::setValue(int val) {
      value = val;
  }
}
