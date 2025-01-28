#pragma once
#include "visitor/Visitable.hpp"

namespace YANKI {
  class IntegerFactor : public Visitable {
  private:
      int value;

  public:
      IntegerFactor(int val){value=val;};
      void accept(Visitor* v) override;
      int getValue() const;
      void setValue(int val);
  };
}
