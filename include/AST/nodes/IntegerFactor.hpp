#pragma once
#include "Visitor/Visitable.hpp"

namespace YANKI{
  class IntegerFactor : public Visitable
  {
  private:
    int value;

  public:
    void accept(Visitor* v) override
    {
      v->visitIntegerFactor(this);
    }

    int getValue() const
    {
      return value;
    }

    void setValue(int val)
    {
      value = val;
    }
  };
}