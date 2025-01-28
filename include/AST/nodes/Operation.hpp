#pragma once
#include "visitor/Visitable.hpp"
#include "AST/AST.hpp"

namespace YANKI {
  class Operation : public Visitable {
  private:
      OpType op;
      Visitable* factor1;
      Visitable* factor2;

  public:
      void accept(Visitor* v) override;
      OpType getOp() const;
      void setOp(OpType operation);
      Visitable* getFactor1() const;
      void setFactor1(Visitable* fac1);
      Visitable* getFactor2() const;
      void setFactor2(Visitable* fac2);
  };
}
