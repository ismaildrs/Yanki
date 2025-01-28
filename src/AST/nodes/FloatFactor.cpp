#include "AST/nodes/FloatFactor.hpp"

namespace YANKI {
  void FloatFactor::accept(Visitor* v) {
      v->visitFloatFactor(this);
  }

  float FloatFactor::getValue() const {
      return value;
  }

  void FloatFactor::setValue(float val) {
      value = val;
  }
}
