#pragma once
#include "visitor/Visitable.hpp"

namespace YANKI {
  class PrintStatement : public Visitable {
  private:
      Visitable* expression;

  public:
      PrintStatement()=default;
      void accept(Visitor* v) override;
      Visitable* getExpression() const;
      void setExpression(Visitable* );
  };
}
