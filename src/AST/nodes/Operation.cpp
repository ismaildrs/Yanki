#include "AST/nodes/Operation.hpp"

namespace YANKI {
  void Operation::accept(Visitor* v) {
      v->visitOperation(this);
  }

  OpType Operation::getOp() const {
      return op;
  }

  void Operation::setOp(OpType operation) {
      op = operation;
  }

  Visitable* Operation::getFactor1() const {
      return factor1;
  }

  void Operation::setFactor1(Visitable* fac1) {
      factor1 = fac1;
  }

  Visitable* Operation::getFactor2() const {
      return factor2;
  }

  void Operation::setFactor2(Visitable* fac2) {
      factor2 = fac2;
  }
}
