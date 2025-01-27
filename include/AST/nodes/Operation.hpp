#pragma once
#include "Visitor/Visitable.hpp"
#include "AST/AST.hpp"

namespace YANKI
{
  class Operation : public Visitable
  {
  private:
    OpType op;
    Visitable *factor1;
    Visitable *factor2;

  public:
    void accept(Visitor *v) override
    {
      v->visitOperation(this);
    }

    OpType getOp() const
    {
      return op;
    }

    void setOp(OpType operation)
    {
      op = operation;
    }

    Visitable *getFactor1() const
    {
      return factor1;
    }

    void setFactor1(Visitable *fac1)
    {
      factor1 = fac1;
    }

    Visitable *getFactor2() const
    {
      return factor2;
    }

    void setFactor2(Visitable *fac2)
    {
      factor2 = fac2;
    }
  };

}