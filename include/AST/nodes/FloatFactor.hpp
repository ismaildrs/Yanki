#pragma once
#include "Visitor/Visitable.hpp"

namespace YANKI{
  class FloatFactor : public Visitable
  {
  private:
    float value;

  public:
    void accept(Visitor* v) override
    {
      v->visitFloatFactor(this);
    }

    float getValue() const
    {
      return value;
    }

    void setValue(float val)
    {
      value = val;
    }
  };
}