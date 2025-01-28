#pragma once
#include "visitor/Visitable.hpp"

namespace YANKI {
  class FloatFactor : public Visitable {
  private:
      float value;

  public:
      void accept(Visitor* v) override;
      float getValue() const;
      void setValue(float val);
  };
}
